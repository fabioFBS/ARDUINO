
   
void setup(){  
 Serial.begin(9600);
 Serial.println("Inicializando...");
 prepareOptical();
}  
   
void loop(){
  monitoringOptical();
  
}
