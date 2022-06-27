/**********************************************************************************
      CURSO AUTOMAÇÃO NA VEIA
      Projeto Blackout | Monitoramento de Queda de Energia e Violação de Sensores de Presença
      Autor : Carlos Freitas

      Hardwares :   Arduino Uno + Shield SIM900

*************************************************************************************/

#include <SoftwareSerial.h>
#include <String.h>

#define VIOLADO  "VIOLADO"
#define NORMAL   "NORMAL"
#define BLACKOUT "BLACKOUT"




void setup() {
      prepareSerial();
      prepareLed();
      prepareSwitch();
      prepareBuzzer();
      prepareReles();
      preparePIR();
      prepareBlackout();
      prepareSim();


}

void loop() {
      
     monitoringSwitch();

    if(getStartSystem()){
          
          /*  BLACKOUT
           * 
           */
          if(isBlackout() && getTimeBlackout()){
              startActionBlackout();
              if(!getMessageSentBlackout()){
                  setMessageSentBlackout(true) ;
                  clearTimeNextSMS();
              }
              createSMSMessage();
                       
          }
           
           
          /* PIR
           * Verificando se os Sensore sPIR forma violados
           */
          if(getTimeActivateAlarm() && isViolated()){
              startActionPIR();
              if(!getMessageSentPIR()){
                  setMessageSentPIR(true) ;
                  clearTimeNextSMS();
              }
              createSMSMessage();
          }
          
    }else{
        /*
         * Sistema em modo standBy
         * Sistema de Blackout e Sensores de Presença não funcionam
        */
        standby();
      
    }

  /*
   *  BUZZER
   *  Se algum dos alarmes forem violados dispara o Aviso Sonoro
   */
     if(getBuzzer()){
        soundBuzzer();
     }


  /*
   *  Monitorando o recebimento de mensagens de texto e chamadas
  */
    monitoringSIM();
    getReceivementCall();
    getReceivementSMS();
  
}
