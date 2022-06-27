
#define PORT_LED_POWER        4  // Led que mostra o sistema iniciado
#define PORT_LED_BLACKOUT    10  // Led que mostra que houve queda de energia
#define PORT_LED_VIOLATED    11  // Led que mostra que o Sensor de Presença foi violado
#define PORT_LED_EMERGENCY   12  // Led que mostra que a saída de emergência está ligada
#define PORT_LED_SMS         13  // Led que mostra o envio de SMS


unsigned long tLed      = 0;     // tempo corrido LED Standby
int tDelayLed           = 1000;  // Tempo que o Led Piscará


unsigned long tLedConfig      = 0;     // tempo delay necessário para configuração


void prepareLed(){
      pinMode(PORT_LED_POWER,OUTPUT);
      pinMode(PORT_LED_BLACKOUT,OUTPUT);
      pinMode(PORT_LED_VIOLATED,OUTPUT);
      pinMode(PORT_LED_EMERGENCY,OUTPUT);
      pinMode(PORT_LED_SMS,OUTPUT);

      boolean aux = HIGH;
      for(int x = 0; x < 6; x ++){
          setLedPower(aux);
          delay(50);
          setLedBlackout(aux);
          delay(50);
          setLedViolated(aux);
          delay(50);
          setLedEmergency(aux);
          delay(50);
          setLedSMS(aux);
          delay(50);
          aux = !aux;
      }
      setLedPower(HIGH);    
}

/*
 *  Alterando o Status do LED
 *  @param status  HIGH | LOW
 */
void setLedPower(boolean status){
    digitalWrite(PORT_LED_POWER,status);
}

/*
 *  Retorna o estado atual do LED
 *  return true | false
 */
boolean getLedPower(){
  return digitalRead(PORT_LED_POWER);
}

/*
 *  Alterando o Status do LED
 *  @param status  HIGH | LOW
 */
void setLedBlackout(boolean status){
    digitalWrite(PORT_LED_BLACKOUT,status);
}

/*
 *  Retorna o estado atual do LED
 *  return true | false
 */
boolean getLedBlackout(){
  return digitalRead(PORT_LED_BLACKOUT);
}


/*
 *  Alterando o Status do LED
 *  @param status  HIGH | LOW
 */
void setLedViolated(boolean status){
    digitalWrite(PORT_LED_VIOLATED,status);
}

/*
 *  Retorna o estado atual do LED
 *  return true | false
 */
boolean getLedViolated(){
  return digitalRead(PORT_LED_VIOLATED);
}



/*
 *  Alterando o Status do LED
 *  @param status  HIGH | LOW
 */
void setLedEmergency(boolean status){
    digitalWrite(PORT_LED_EMERGENCY,status);
}

/*
 *  Retorna o estado atual do LED
 *  return true | false
 */
boolean getLedEmergency(){
  return digitalRead(PORT_LED_EMERGENCY);
}


/*
 *  Alterando o Status do LED
 *  @param status  HIGH | LOW
 */
void setLedSMS(boolean status){
    digitalWrite(PORT_LED_SMS,status);
}

/*
 *  Retorna o estado atual do LED
 *  return true | false
 */
boolean getLedSMS(){
  return digitalRead(PORT_LED_SMS);
}

void standby(){
  if( waiting(tLed) ){
    setLedPower(!getLedPower());
    tLed = millis() + tDelayLed;
  }
}

void ledSMSConfig(){
  if( waiting(tLedConfig) ){
       setLedSMS(!getLedSMS());
       tLedConfig = millis() + 100;       
  }
}


void delayWithLed(unsigned long time){
  unsigned long tTime = millis() + time;
  while(!waiting(tTime)){
     ledSMSConfig();
  }

  setLedSMS(LOW);
}
