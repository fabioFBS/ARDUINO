/*
 *  Vídeo aula DAV002
 *  Sensor de Pressão Arduino
*/


void setup() {
  Serial.begin (9600);
  Serial.println("Inicializando...");  
  prepareRele();
  preparePressureSensor();
  
}

void loop() {
   monitoringPressureSensor();
}
