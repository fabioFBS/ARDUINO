
const byte PORT_PIR[]             = {A0,A1,A2};

boolean flagPIR                   = false;  // Ativado quando os sensores estiverem violados

unsigned long tAtivatedAlarm      = 0;      // Tempo corrido para ativar o alarme
int  tDelayAtivatedAlarm          = 10000;  // Tempo em milissegundos para ativar o alarme

boolean messageSentPIR            = false;

void preparePIR(){
  for(byte x = 0; x < sizeof(PORT_PIR)/sizeof(byte); x++){
      pinMode(PORT_PIR[x],INPUT_PULLUP);
  }
}

void setFlagPIR(boolean status){
    flagPIR = status;
}

boolean getFlagPIR(){
    return flagPIR;
}

void setMessageSentPIR(boolean status){
    messageSentPIR = status;
}

boolean getMessageSentPIR(){
  return messageSentPIR;
}

void setTimeActivateAlarm(){
  tAtivatedAlarm = millis() + tDelayAtivatedAlarm;
}

boolean getTimeActivateAlarm(){
  return waiting(tAtivatedAlarm);
}


boolean isViolated(){
    if(monitoringPIR){
      isCheckedPIR();
      return getFlagPIR();
    }
    return false;
}

void isCheckedPIR(){
  for(byte x = 0; x < sizeof(PORT_PIR)/sizeof(byte); x++){
       if(digitalRead(PORT_PIR[x]) == PIR_VIOLATED ){
        delay(100);
          if(digitalRead(PORT_PIR[x]) == PIR_VIOLATED){
              setFlagPIR(true);
          }
       }
  }
}

boolean startActionPIR(){
  setBuzzer(true);
  setLedViolated(HIGH);
  if(activedEmergencyInPIR) setRele(ON);
  return false;
} 
