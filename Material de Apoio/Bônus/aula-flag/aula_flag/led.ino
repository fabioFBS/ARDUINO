
#define PORT_LED  12


/*
 *  Inicializando e preparando o LED ou a carga
*/
void prepareLed(){
  pinMode(PORT_LED,OUTPUT);
}

void setLed(boolean status){
  digitalWrite(PORT_LED,status);
}
