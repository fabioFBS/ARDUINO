
#define PORT_BLACKOUT           3           // Porta que identificada energia rede eletrica

boolean flagBlackout            = false;    // Ativado quando existir queda de energia

unsigned long tBlackout         = 0;        // recebe o valor atual do temporizador do Blackout
int tDelayBlackout              = 5000;     // tempo que aguardará voltar a energia até que seja enviado SMS


boolean messageSentBlackout     = false;  // Controla se já foi enviada a mensagem

void prepareBlackout(){
    pinMode(PORT_BLACKOUT, INPUT_PULLUP);
}

void setFlagBlackout(boolean status){
    flagBlackout = status;
}

boolean getFlagBlackout(){
  return flagBlackout;
}

void setMessageSentBlackout(boolean status){
    messageSentBlackout = status;
}

boolean getMessageSentBlackout(){
  return messageSentBlackout;
}

boolean isBlackout(){
    if(monitoringBlackout){
       if(digitalRead(PORT_BLACKOUT) == HIGH ){
        delay(100);
          if(digitalRead(PORT_BLACKOUT) == HIGH){
              if(!getFlagBlackout()){ setTimeBlackout(); Serial.println(F("[BLACKOUT] - contagem de 5 segundos"));}
              setFlagBlackout(true);
              return true;
          }
       }
    }

    if(getFlagBlackout()){
       Serial.println(F("Energia Reestabilizada - Enviando Mensagem SMS"));
       clearTimeNextSMS();
       setFlagBlackout(false);
       createSMSMessage();
       clearTimeNextSMS();
       setLedBlackout(LOW);
       setRele(OFF);
    }
    
    setFlagBlackout(false);
    return false;
}

void setTimeBlackout(){
  tBlackout = millis() + tDelayBlackout;
}

boolean getTimeBlackout(){
  return waiting(tBlackout);
}

void startActionBlackout(){
    setBuzzer(true);
    setLedBlackout(HIGH);
    if(activedEmergencyInBlackout) setRele(ON);
}
