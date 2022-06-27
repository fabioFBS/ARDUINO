
#define PORT_SWITCH       A3
boolean pressed           = false;
boolean flagStartSystem   = true;  // Incia Sistema Ativo

void prepareSwitch(){
  pinMode(PORT_SWITCH,INPUT_PULLUP);
}

void setStartSystem(boolean status){
  flagStartSystem = status;
}

boolean getStartSystem(){
  return  flagStartSystem;
}

/*
 * Monitora a porta para Ativar e Desativar Sistema
*/
void monitoringSwitch(){
     if(digitalRead(PORT_SWITCH) == LOW && !pressed){
      delay(100);
        if(digitalRead(PORT_SWITCH) == LOW){
           Serial.println(F("Pulso Pressionado"));
           pressed = true;
           actionPressedSwitch();
        }
     }else{
         if(digitalRead(PORT_SWITCH) == HIGH && pressed){
            Serial.println(F("Pulso Liberado"));
            pressed = false;
         }
     }
}

/*
 * Execução acão após pressionado o Buttom
*/
void actionPressedSwitch(){
      if( getStartSystem() ){
          toneAlertOFF();
      }else{
          setTimeActivateAlarm();
          toneAlertON();
          setLedPower(HIGH);          
      }

      setStartSystem(!getStartSystem());
      createSMSStatus(getStartSystem());

      setMessageSentBlackout(false);
      setMessageSentPIR(false);
      clearTimeNextSMS();
      
      setBuzzer(false);
      setFlagPIR(false);
      setRele(OFF);
      setLedViolated(LOW);
      setFlagBlackout(false);
      setLedBlackout(LOW);
}
