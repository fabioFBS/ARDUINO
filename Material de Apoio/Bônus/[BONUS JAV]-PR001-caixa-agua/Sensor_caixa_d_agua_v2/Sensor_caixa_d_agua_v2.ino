/*
 *  JORNADA AUTOMAÇÃO NA VEIA (JAV)
 *  PROJETO PARA MONITORAMENTO DE SENSORES DE NÍVEIS 
 *  Autor: Carlos Freitas
 *  #PR001
*/

#define NIVEL_100           0
#define NIVEL_50            1
#define NIVEL_15            2
#define NIVEL_EMERGENCY     3

#define ON    HIGH
#define OFF   !ON

#define _NULL  -1
#define NIVEL_ATINGIDO 1
#define NIVEL_NAO_ATINGIDO 0

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando...");
  
  prepareEngine();
  prepareLevelSensor();
  prepareLed();
  
}

void loop() {
    monitoringLevelSensor();
    monitoringEngine();
    monitoringLed();
    
}
