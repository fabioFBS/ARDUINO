
/*
 *   JORNADA AUTOMAÇÃO NA VEIA
 *   PARA QUE SERVE  E QUANDO UTILIZAR AS FLAGS
 *   
*/



void setup() {
    Serial.begin(9600);
    Serial.println("Inicializando...");

    prepareButton();
    prepareLDR();
    prepareUltrasonic();
    prepareLed();
  
    
}

void loop() {
    
    monitoringButton();
    monitoringLDR(20);
    monitoringUltrasonic(10);
    monitoringFlag();

}
