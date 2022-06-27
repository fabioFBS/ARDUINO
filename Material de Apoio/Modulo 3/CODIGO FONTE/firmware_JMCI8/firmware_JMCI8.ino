/*
 *   JORNADA MINHA CASA INTELIGENTE
 *   Autor: Carlos Freitas
 *   Versão : 2.0
 * 
*/

#include <SPI.h>
#include <Ethernet.h>


#define _MODEL                          "JMCI8-ECO"
#define _VERSION                        "2.0"

#define ON  LOW
#define OFF !ON

#define MODE_DISABLED           0
#define MODE_AUTOMATIC          1
#define MODE_MODIFIED           2

#define SWITCH                  'R'
#define PULSE                   'P'
#define TRIGGER                 'D'
#define MULTI_COMMAND           "E"
#define LIMITER                 '.'

#define LDR                     'L'




String  _buffer                     = "";
boolean _record                     = false;

void setup() {

   prepareSerial();
   prepareLed();
   preparePulsador();
   prepareMultiCena();
   prepareRele();
   preparePir();
   prepareLdr();
   prepareConnection();

   prepareMultiCommands();
  
}

void loop() {

   monitoringPulsador();
   monitoringMultiCena();
   monitoringLdr(); 
   monitoringEngine();
   monitoringScene();
   monitoringSerial();

   monitoringConnection();
   
   monitoringMultiCommands();

}
