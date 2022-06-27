

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando...");
  prepareTimeOver();
  
  
}

void loop() {
  if(monitoringTimeOver()){
    Serial.println("Tempo Atingido !!");
  }
  
}
