/*
 * LCD 16x2        -> PORT ( 12, 11, 6, 5, 4, 3 )
 * Sensor óptico   -> PORT ( 2 )
 * Push Button     -> PORT ( A0, A1 )
 * Buzzer          -> PORT ( 9 )
*/

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando...");
  prepareLcd();
  prepareBuzzer();
  prepareMemory();
  prepareMultiButton();
  prepareOptical(); 
}

void loop() {

  monitoringEngine();

}
