/*
    Componente de Conexão
*/


EthernetClient client;
EthernetServer server(_PORTA);

void prepareConnection(){
      
      Ethernet.begin(mac,ip);
      server.begin();   
}

IPAddress getIP(){
    return Ethernet.localIP();
}


void monitoringConnection(){
    client = server.available();

    if(client){ 
       while(client.available()){
           char c = client.read();
           //Serial.print(c);
         
              if(c == getEnd()){
                _record  = false;

                httpRequest();
                interpreter(&_buffer);
                client.flush();
                client.stop();  
                break;
             }

             if(_record){
               _buffer += c;
             }
            
             if(c == getStart()){
                  _buffer = "";
                  _record = true;
             }       
       }
    }
  
}

void httpRequest(){

    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: text/html"));
    client.println(F("Access-Control-Allow-Origin: *"));
    client.println(F("connection:close"));
   //client.println();
   //client.println(F("<link rel=\"shortcut icon\" type=\"image/png\" href=\"https://automacaonaveia.cemf.com.br/shared/images/favicon/favicon_32x32.png\"/>"));
    client.println();
}


/*
 *  Retorna para WEB o status do sistema
 * {
 *   'mode' : 'JCMI8-ECO,
 *   versao : """
 *   ip : """
 * }
*/
void httpResumeStatus(){

    String json = "{";

    json += "\"MODELO\":\"";
    json += _MODEL;
    json += "\",\"VERSAO\":\"";
    json += _VERSION;
    json += "\",\"SAIDAS\":\"";

     for(byte x = 0; x < getSizeRele() ; x++){
          json += "R";
          json += x+1;
          json += "[";
          json += ((getRele(x) == ON) ? "ON" : "OFF");
          json += "] ";
      }

    json += "\"}";
    
    client.println(json);
    
}

/*
 * Protocolo padrao de resposta para appweb
 * {"status":"R00000000L40D30"}
*/

void httpResponse(){

  String json = "{\"status\":\"";
  json  += SWITCH;

  for(byte x = 0; x < getSizeRele(); x++){
        json  += (getRele(x) == ON) ? "1" : "0";
  }

  json += LDR;
  
  int aux = getLdr(0);

  if(aux < 10){
    json += "0";
  }

  json += aux;

  json += TRIGGER;
  aux = getTriggerLdr();

  if(aux < 10){
    json += "0";
  }
  
  json += aux;
  json += "\"}";
  
  client.println(json);
}
