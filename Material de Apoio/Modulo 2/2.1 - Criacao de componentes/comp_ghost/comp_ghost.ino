
void setup() {
    Serial.begin(9600);
    //setGhost();
    prepareGhost();
    Serial.println("Inicializando...");   
    
}

void loop() {
    monitoringGhost();
    Serial.println("Codigo Liberado");
}
