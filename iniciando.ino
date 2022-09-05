void void_teste_inicial (){
  pinMode(pinoButton, INPUT_PULLUP);
}

void teste_inicial(){
if(digitalRead(pinoButton)){
  Serial.println("iniciou teste");
  reading_sensor();
}
}