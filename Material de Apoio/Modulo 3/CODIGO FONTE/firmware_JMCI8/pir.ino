/*
 * Componente PIR
 * 
*/


const byte PORT_PIR[]                         = {A8,A10,A12};
#define SIZE_PIR                              sizeof(PORT_PIR)/sizeof(byte)
                                 
//#define _DISABLED                           0
//#define _PRINCIPAL                          1
//#define _SECONDARY                          2


#define SIZE_OUTPUT_PIR                       8
//byte groupPir[SIZE_PIR][SIZE_OUTPUT_PIR] = {
//                                  {_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED},
//                                  {_PRINCIPAL,_DISABLED,_DISABLED,_SECONDARY,_SECONDARY,_SECONDARY,_DISABLED,_DISABLED},
//                                  {_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED}
//                                };

                        
// 0 = desativada  1 = automatico  2 = modificado pelo pulsador
  byte sensorOutputsPir[SIZE_OUTPUT_PIR]      = {
                                                MODE_AUTOMATIC,
                                                MODE_AUTOMATIC,
                                                MODE_AUTOMATIC,
                                                MODE_AUTOMATIC,
                                                MODE_AUTOMATIC,
                                                MODE_AUTOMATIC,
                                                MODE_AUTOMATIC,
                                                MODE_AUTOMATIC
                                               };
                                            

#define PIR_NORMAL                            0
#define PIR_VIOLATED                          1 

boolean flagViolatedSensorPir[SIZE_PIR]       = {PIR_NORMAL,PIR_NORMAL,PIR_NORMAL};
unsigned long futureTimePir[SIZE_PIR]         = {0,0,0};




boolean flagShowPir                           = false;
unsigned long futureTimeShowPir               = 0;
#define TIME_PAUSE_SHOW_PIR                   2000


/*
 * Inicialização do sensor PIR
*/
void preparePir(){
  for(byte x = 0; x < SIZE_PIR; x++){
      pinMode(PORT_PIR[x],INPUT);
  } 
}


/*
 * Ativa/Desativa o monitoramento pelo Serial do Sensor PIR
*/
void setShowPir(){
  flagShowPir = !flagShowPir;
  Serial.print("Monitoramento do sensor PIR ");
  Serial.println( (flagShowPir) ? "ATIVADO" : "DESATIVADO" );
}


/*
 * Retorna a Quantidade de sensores PIR do modulo
*/
byte getSizePir(){
  return SIZE_PIR;
}


/*
 *  Atualizar tempo mínimo para inico do modo inteligente
*/
void setTimeFuture(){
  for(byte x = 0; x < SIZE_PIR; x++){
      futureTimePir[x] = millis() + TIME_PAUSE_STEP1;
  } 
}


/*
 * Retorna o estado do sensor PIR
*/
boolean getPir(byte pos){
  return digitalRead(PORT_PIR[pos]);
}


/*
 * Marca o sensor informado como violado
*/
void setViolatedPir(byte pos){
  flagViolatedSensorPir[pos] = PIR_VIOLATED;
}


/*
 * Marca o sensor informado como normal
*/
void setNormalPir(byte pos){
  flagViolatedSensorPir[pos] = PIR_NORMAL;
}


/*
 * Retorna se um sensor específico está violado
*/
boolean isViolatedPir(byte pos){
    return flagViolatedSensorPir[pos];
}


/*
 * Define a saída como desativada temporariamente
*/
void modifyOutputPir(byte pos){
  if(sensorOutputsPir[pos] == MODE_AUTOMATIC)
       sensorOutputsPir[pos] = MODE_MODIFIED;
}


/*
 * Retorna true se algum sensor está violado
*/
boolean verifyAllViolatedPir(){
    for(byte x = 0; x < SIZE_PIR; x++){
      if(isViolatedPir(x))
        return true;
    }
    return false;
}


/*
 * Monitora o sensor PIR identificando a violação
*/
void monitoringPir(){

    for(byte x = 0; x < SIZE_PIR; x++){     
       if(isSensor(x)){ 

          if(getPir(x)){
            setViolatedPir(x);
            actionAfterViolated(x);
                      
            futureTimePir[x] = millis() + TIME_PAUSE_STEP1;
          }else{
            setNormalPir(x);
            actionAfterNormal(x);
          } 
       }  
    }

    if(verifyAllViolatedPir()){
      ledPirOn();
    }else{
      ledPirOff();
    }

    
}


/*
 * Ação a ser executada após a violação do sensor PIR
*/
void actionAfterViolated(byte x){
  if(!isModeIntelligent()){
      return;
  }
  
  for(byte y = 0; y < SIZE_OUTPUT_PIR; y++){  
      if(groupPir[x][y] == _PRINCIPAL && sensorOutputsPir[y] == MODE_AUTOMATIC){
          // ligar a iluminaçao
          // Verificar se a ilumincação do ambiente já é suficiente
          if(isViolatedLdr(x)){
            setRele(y,ON);
          }
      }
  }
}


/*
 * 
*/
void actionAfterNormal(byte x){
   if(isModeNormal()){
      return;
    }
    
    if(isSensor(x)  && timeIsOver(futureTimePir[x])){
      Serial.print("Comecar a desligar o ponto R:");
      Serial.println(x);
      byte type = -1;
      if(isOutputOn(x,_PRINCIPAL)){
          type = _PRINCIPAL;
          futureTimePir[x] = millis() + TIME_PAUSE_STEP2;
          
      }else if(isOutputOn(x,_SECONDARY)){
          type = _SECONDARY;
          futureTimePir[x] = millis() + TIME_PAUSE_STEP3;
          
      }

      boolean flagAux = false;
      
      for(byte y = 0; y < SIZE_OUTPUT_PIR; y++){
        if(flagAux == false && groupPir[x][y] == type && getRele(y) == ON){
            
            setRele(y,OFF);
            flagAux = true;
 
        }
        if(groupPir[x][y] != _DISABLED){
          sensorOutputsPir[y] = MODE_AUTOMATIC;
        }
      }
    }
}


/*
 * Retorna se existe o tipo informado e se o rele está ligado
*/
boolean isOutputOn(byte x, byte type){
  for(byte y = 0; y < SIZE_OUTPUT_PIR; y++){
        if(groupPir[x][y] == type && getRele(y) == ON){
            return true;
        }
  }

  return false;
}


/*
 *  Percorre todos os grupos dos sensores e desliga 
 *  os pontos secundários.
*/
void turnOffSecondary(){
   for(byte x = 0; x < SIZE_PIR; x++){  
      for(byte y = 0; y < SIZE_OUTPUT_PIR; y++){
          if(groupPir[x][y] == _SECONDARY){    
                  setRele(y,OFF);  
          }
      }
      futureTimePir[x] = millis() + TIME_PAUSE_STEP1;
   }
   
}


/*
 * Mostra em Tempo-Real as informações do sensor PIR
*/

void showPir(){
    if(!flagShowPir)
        return;

    if(timeIsOver(futureTimeShowPir)){
  
     Serial.println(F("*********************************"));
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

      Serial.println();

      futureTimeShowPir = millis() + TIME_PAUSE_SHOW_PIR;    
    }    
}





 
