
 
void setup(){
   Serial.begin(9600);
   Serial.println("Inicializando...");
   prepareMultiButton();
   prepareLcd();
}
 
void loop(){
   customMultiButton();
   monitoringLcd();
}
