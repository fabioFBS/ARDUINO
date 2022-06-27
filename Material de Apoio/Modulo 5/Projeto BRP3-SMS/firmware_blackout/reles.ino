
#define PORT_EMERGENCY      2 // Rele de Emergência

void prepareReles(){
   pinMode(PORT_EMERGENCY,OUTPUT);
   digitalWrite(PORT_EMERGENCY,OFF);
}

void setRele(boolean status){
  digitalWrite(PORT_EMERGENCY,status);
  setLedEmergency( (status == ON) ? HIGH : LOW );
}

boolean getRele(){
  return digitalRead(PORT_EMERGENCY);
}
