/*
 *  COMPONENTE LED
*/

const byte PORT_LED[] = {6,7,8,9};
#define SIZEOF_LED  sizeof(PORT_LED)/sizeof(byte)

/*
 * 
*/
void prepareLed(){
   for(byte x = 0; x < SIZEOF_LED; x++){
      pinMode(PORT_LED[x],OUTPUT);
  }
}


/*
 *  Liga ou Desliga o Motor.
*/
void setLed(byte pos, boolean status){
    digitalWrite(PORT_LED[pos],status);
}


/*
 * 
*/
void monitoringLed(){
   for(byte x = 0; x < SIZEOF_LED; x++){
    if(getLevelSensor(x) != _NULL){
        if(x == NIVEL_EMERGENCY){
          setLed(x,!getLevelSensor(x));
        }else{
          setLed(x,getLevelSensor(x));
        }
    }
  }
}
