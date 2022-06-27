
void setup() {
   Serial.begin(9600);
   Serial.println("Inicializando");
   prepareMultiButton();

}
void loop() {
    customMultiButton();
}
