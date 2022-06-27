/*
 *  COMPONENTE LEVEL SENSOR
*/

const byte PORT_LEVEL_SENSOR[] = {2,3,4,5};
#define SIZEOF_LEVEL_SENSOR  sizeof(PORT_LEVEL_SENSOR)/sizeof(byte)
boolean statusLevelSensor[SIZEOF_LEVEL_SENSOR];

unsigned long futureLevelSensor[SIZEOF_LEVEL_SENSOR]; 

#define DELAY_TIME  3000


/*
 * 
*/
void prepareLevelSensor(){
  for(byte x = 0; x < SIZEOF_LEVEL_SENSOR; x++){
      pinMode(PORT_LEVEL_SENSOR[x],INPUT);
      futureLevelSensor[x] = 0;
  }
}

int getLevelSensor(byte pos){
  if(timeOver(futureLevelSensor[pos])){
    futureLevelSensor[pos] = 0;
    return statusLevelSensor[pos];
  }
  return _NULL;
}

/*
 * 
*/
void monitoringLevelSensor(){
   for(byte x = 0; x < SIZEOF_LEVEL_SENSOR; x++){
      if(digitalRead(PORT_LEVEL_SENSOR[x]) == NIVEL_ATINGIDO 
            && statusLevelSensor[x] == false){
                delay(50);
                if(digitalRead(PORT_LEVEL_SENSOR[x]) == NIVEL_ATINGIDO){
                  statusLevelSensor[x] = true;
                  futureLevelSensor[x] = millis() + DELAY_TIME;
                }
      }else{
        
        if(digitalRead(PORT_LEVEL_SENSOR[x]) == NIVEL_NAO_ATINGIDO 
            && statusLevelSensor[x] == true){
            statusLevelSensor[x] = false;
            futureLevelSensor[x] = millis() + DELAY_TIME;
        }
      }  
   }
}
