/*
 * COMPONENTE LED
*/


const byte PORT_LED[] = {9,10,11,12};
#define SIZEOF_LED    sizeof(PORT_LED)/sizeof(byte)

#define ON      HIGH
#define OFF     !ON


/*
 *  Inicializando e preparando o LED ou a carga
*/
void prepareLed(){
  for(byte x=0; x < SIZEOF_LED; x++){
     pinMode(PORT_LED[x],OUTPUT);  
  }
}


/*
 *  Altera o Status atual da saída
 *  conforme parâmetro status
*/
void setLed(byte pos,boolean status){
  digitalWrite(PORT_LED[pos],(status)? ON : OFF);
}


/*
 * Alterar Status do Led1
 * conforme parâmetro status
*/
void setLed1(byte status){
    setLed(0,status);
}


/*
 * Alterar Status do Led2
 * conforme parâmetro status
*/
void setLed2(byte status){
    setLed(1,status);
}


/*
 * Alterar Status do Led3
 * conforme parâmetro status
*/
void setLed3(byte status){
    setLed(2,status);
}


/*
 * Alterar Status do Led4
 * conforme parâmetro status
*/
void setLed4(byte status){
    setLed(3,status);
}


void monitoringLed(){}


/*
 * Testa o funcionamento dos LEDS
*/
void testLed(){
  byte status = ON;
  for(byte x=0; x < SIZEOF_LED; x++){
    setLed(x,status);
    delay(1000);
  }
  
  for(int x = (SIZEOF_LED - 1); x >= 0; x--){
    setLed(x,!status);
    delay(1000);
  }
}


/*
 * Desliga os Leds da posição Informada
*/
void turnAllOff(byte pos){
  if(pos == 0){
    setLed1(OFF);
    setLed2(OFF);
  }else if(pos == 1){
    setLed3(OFF);
    setLed4(OFF);
  }
}
