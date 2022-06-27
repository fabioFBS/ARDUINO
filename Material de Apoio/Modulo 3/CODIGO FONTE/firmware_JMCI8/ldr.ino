/*
 * Componente LDR
*/


const byte PORT_LDR[]                         = {A9,A11,A13};
#define SIZE_LDR                            sizeof(PORT_LDR)/sizeof(byte)

//
//boolean groupLdr[SIZE_LDR][8]   = {
  //                                  {0,0,0,0,0,0,0,0},
  //                                  {1,0,0,1,1,1,0,0},
  //                                  {0,0,0,0,0,0,0,0}
  //                                };

//#define MODE_DISABLED                     0
//#define MODE_AUTOMATIC                    1
//#define MODE_MODIFIED                     2
                        
// 0 = desativada  1 = ativada
byte sensorOutputs[]                           = {
                                                MODE_DISABLED,
                                                MODE_DISABLED,
                                                MODE_DISABLED,
                                                MODE_DISABLED,
                                                MODE_DISABLED,
                                                MODE_DISABLED,
                                                MODE_DISABLED,
                                                MODE_DISABLED
                                               };
                                 
#define SIZE_OUTPUT_LDR                       sizeof(sensorOutputs)/sizeof(byte)

boolean lastStateLdr[SIZE_LDR]                = {false,false,false};

unsigned long  futureTimeLdr[SIZE_LDR]        = {0,0,0};
#define TIME_PAUSE_LDR                        300000  // 1000 * 60 * 5 tempo para próxima leitura, após alterado o sensor LDR



boolean flagShowLdr                           = false;
unsigned long futureTimeShowLdr               = 0;
#define TIME_PAUSE_SHOW_LDR                   2000


/*
 * Preparando a Entrada do Sensor LDR
*/
void prepareLdr(){
  for(byte x = 0; x < SIZE_LDR; x++){
      pinMode(PORT_LDR[x],INPUT);
  }
  //setControllerLdr(2,2,true);
}


/*
 * Ativa/Desativa o monitoramento pelo Serial do Sensor LDR
*/
void setShowLdr(){
  flagShowLdr = !flagShowLdr;
  Serial.print("Monitoramento do sensor LDR ");
  Serial.println( (flagShowLdr) ? "ATIVADO" : "DESATIVADO" );
}


/*
 * Retorna a Quantidade de sensores LDR do modulo
*/
byte getSizeLdr(){
  return SIZE_LDR;
}


/*
 * Altera qual dos sensores contra a saída informada
*/
void setControllerLdr(byte sensor, byte output, boolean status){
    for(byte x = 0; x < SIZE_LDR; x++){
        groupLdr[x][output] = 0;
    }
    groupLdr[sensor][output] = status;
}


/*
 * Artiva uma saída para ser controlada pelo LDR
*/
void activeOutputLdr(byte pos){
  sensorOutputs[pos] = MODE_AUTOMATIC;
}


/*
 * Desativa uma saida a ser controlado pelo LDR
*/
void disableOutputLdr(byte pos){
  sensorOutputs[pos] = MODE_DISABLED;
}


/*
 * Define a saída como desativada temporariamente
*/
void modifyOutputLdr(byte pos){
  if(sensorOutputs[pos] == MODE_AUTOMATIC)
       sensorOutputs[pos] = MODE_MODIFIED;
}


/*
 * Retorna o valor do Sensor passado no parametro
 * na escala de 0 a 100%
 * map(leitura, 0, 1023, 0 ,100);
*/
int getLdr(byte pos){
  return  map(analogRead(PORT_LDR[pos]), 0 ,1023 , 0 , 100);
}


/*
 * Retorna o valor de disparo do LDR
*/
byte getTriggerLdr(){
    return triggerLdr;
}


/*
 *  Retorna true se o valor de disparo foi atingido pelo sensor.
 *  
*/
boolean isViolatedLdr(byte pos){
  return (getLdr(pos) <= triggerLdr) ? true : false;
}


/*
 * Monitorando o sensor e disparando as ações 
*/
void monitoringLdr(){
  for(byte x = 0; x < SIZE_LDR; x++){
    if(isSensor(x)){      
        if(timeIsOver(futureTimeLdr[x])){
            for(byte y = 0; y < SIZE_OUTPUT_LDR; y++){
                if(groupLdr[x][y]){
                    if(sensorOutputs[y] == MODE_AUTOMATIC || (sensorOutputs[y] == MODE_MODIFIED && lastStateLdr[x] != isViolatedLdr(x))){
                        setRele(y,isViolatedLdr(x) ? ON : OFF);
                    }
                }
            }
        
            if(lastStateLdr[x] != isViolatedLdr(x)){
                lastStateLdr[x] = isViolatedLdr(x);
                futureTimeLdr[x] = millis() + TIME_PAUSE_LDR;
            }
            
        }
    }
  }
}


/*
 * Mostra em Tempo-Real as informações do sensor PIR
*/
void showLdr(){
    if(!flagShowLdr)
        return;

    if(timeIsOver(futureTimeShowLdr)){
  
     Serial.println(F("*********************************"));
      Serial.println(F("[SENSORES LDR] "));
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

      Serial.println();
      futureTimeShowLdr = millis() + TIME_PAUSE_SHOW_LDR;
     
    }      
}
