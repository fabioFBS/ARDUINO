/*
 * COMPONENTE SERIAL
*/


#define START_SERIAL                    '@'
#define END_SERIAL                      '>'




/*
 * Inicializando a Serial
*/
void prepareSerial(){
   Serial.begin(9600);
   Serial.println("Inicializando...");
   menu();
}


/*
 *  Monitora o recebimento de dados pela serial e executa a ação programada
 *  @STATUS>
 *  
*/
void monitoringSerial(){
    
    if(Serial.available() > 0){
      delay(50);
       
       while(Serial.available() > 0){
           char c = toupper(Serial.read());
             
             if(c == END_SERIAL){
                _record  = false;
                // Interpretador do comando
                interpreterSerial(&_buffer);
                _buffer = "";
                break;
             }

             if(_record){
               _buffer += c;
             }
            
             if(c == START_SERIAL){
                  _buffer = "";
                  _record = true;
             }
       }
    }
}


/*
 * Informa o Status e os comandos possíveis para controlar a central
*/
void menu(){
      Serial.println(F("******************************************************"));
      Serial.println(F("************ COMANDOS SERIAIS ************************"));
      Serial.println(F("******************************************************"));
      Serial.println(F("@STATUS>         Mostra o Status do sistema"));
      Serial.println(F("@ECONOMICO>      Ativa o modo economico"));
      Serial.println(F("@INTELIGENTE>    Ativa o modo inteligente"));
      Serial.println(F("@NORMAL>         Ativa o modo normal"));
      Serial.println(F("@PIR>            Mostra informacoes do PIR"));
      Serial.println(F("@LDR>            Mostrar informacores do LDR"));
      Serial.println(F("@CENAS>          Executa uma Cena programada, adicionar numero da cena"));
      Serial.println(F("@ONR>            Ligar um saida de Rele, adicionar numero da saida"));
      Serial.println(F("@OFFR>           Desligar uma saida de Rele, adicionar numero saida "));
      Serial.println(F("*******************************************************"));
      
}


/*
 * Verificar se é um comando válido e executa a ação
*/
void interpreterSerial(String *buff){
    Serial.println(*buff);

    if( (*buff).startsWith("STATUS") ){
      
      Serial.println(F("******************************************************"));
      Serial.println(F("************ STATUS DO MODULO ************************"));
      Serial.println(F("******************************************************"));
      Serial.print(F("MODELO        : ")); Serial.println(_MODEL);
      Serial.print(F("VERSAO        : ")); Serial.println(_VERSION);
      Serial.print(F("IP            : ")); Serial.println(getIP());
      Serial.print(F("PORTA         : ")); Serial.println(_PORTA);
      Serial.print(F("SAIDAS        : "));
      for(byte x = 0; x < getSizeRele() ; x++){
          Serial.print(F("R"));
          Serial.print(x+1);
          Serial.print(F("["));
          Serial.print((getRele(x) == ON) ? "ON" : "OFF");
          Serial.print(F("] "));
      }
      Serial.println();
      Serial.print(F("PULSADOR      : "));
      for(byte x = 0; x < getSizePulsador() ; x++){
          Serial.print(F("P"));
          Serial.print(x+1);
          Serial.print(F("["));
          Serial.print(getPulsador(x) ? "OFF" : "CLICK");
          Serial.print(F("] "));
      }
      Serial.println();
      Serial.print(F("PRESSOLD      : "));Serial.println(PRESS_OLD ? "ATIVADO": "DESATIVADO");
      Serial.print(F("T_PRESSED     : "));Serial.print(TIME_PRESSED);Serial.println(F("segundos"));
      
      Serial.print(F("[SENSORES LDR - DISPARO ( "));
      Serial.print(getTriggerLdr());
      Serial.println(F("% ) ]"));
      
      for(byte x = 0; x < getSizeLdr() ; x++){
        Serial.print(F("  LDR "));
        Serial.print(x+1);
        Serial.print(F(" ["));
        Serial.print(isSensor(x) ? "ON " : "OFF");
        Serial.print(F("] (%) : "));
        if(isSensor(x)){
          Serial.println(getLdr(x));
        }else{
          Serial.println();
        }
      }

      Serial.println(F("[SENSORES PIR] "));
      for(byte x = 0; x < getSizePir() ; x++){
        Serial.print(F("  PIR "));
        Serial.print(x+1);
        Serial.print(F(" ["));
        Serial.print(isSensor(x) ? "ON " : "OFF");
        Serial.print(F("]     : "));
        if(isSensor(x)){
          Serial.println(getPir(x) ? "VIOLADO": "NORMAL");
        }else{
          Serial.println();
        }
      }
      
      
      
      //Serial.println(F());
      //Serial.println(F());
      //Serial.println(F());

      
    
    }else if( (*buff).startsWith("ECONOMICO") ){
      
        setModeEconomic();
        chargeMode(false);
    
    }else if( (*buff).startsWith("INTELIGENTE") ){
       
        setModeIntelligent();
        chargeMode(false);
    
    }else if( (*buff).startsWith("NORMAL") ){
      
        setModeNormal();
        chargeMode(false);
    }else if( (*buff).startsWith("PIR") ){
          setShowPir();
    
    }else if( (*buff).startsWith("LDR") ){
          setShowLdr();
          
    }else if( (*buff).startsWith("CENAS") ){
          showScenes();
    
    }else if( (*buff).startsWith("ON") ){

          if( (*buff).length() >= 4 ){
            byte pos = convertCharToInt('0',(*buff)[4]);
            if(pos >= 1 && pos <= 8){
                setRele(pos - 1,ON);
            }else{
                Serial.println("**** Informe a saida correta, valor precisa estar entre R01 a R08");
            }    
          }else{
              Serial.println("**** Faltou informar a porta para controle, ex: @ONR01>");
          }
        
      
    }else if( (*buff).startsWith("OFF") ){

         if( (*buff).length() >= 5 ){
            byte pos = convertCharToInt('0',(*buff)[5]);
            if(pos >= 1 && pos <= 8){
                setRele(pos - 1,OFF);
            }else{
                Serial.println("**** Informe a saida correta, valor precisa estar entre R01 a R08");
            }    
          }else{
              Serial.println("**** Faltou informar a porta para controle, ex: @OFFR01>");
          }
    
    }

}


/*
 * Recebe um caracter e retorna o seu inteiro
*/
int convertCharToInt(char a ,char b){
  char aux[2];
     aux[0] = a;
     aux[1] = b;
   
  return atoi(aux);
}
