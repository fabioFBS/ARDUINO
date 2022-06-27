/*
 *   JORNADA AUTOMAÇÃO NA VEIA
 *   PARA QUE SERVE  E QUANDO UTILIZAR AS FLAGS
 *   
 *   Curso Automação na Veia
 *   https://www.automacaonaveia.com.br/
*/



void setup() {
    Serial.begin(9600);
    Serial.println("#DAV004 - JornadaAV");
    Serial.println("Inicializando...");
    prepareButton();
    prepareLDR();
    prepareUltrasonic();
    prepareLed();
}

void loop() {
     monitoringButton();
     if(monitoringLDR(20)){
        monitoringUltrasonic();
     }
     monitoringTurnOffUltrasonic();
}
