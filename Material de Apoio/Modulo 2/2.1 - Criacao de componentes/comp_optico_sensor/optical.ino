/*
 *  COMPONENTE OPTICAL
 *  Precisa do componente TimeOver para funcionamento correto
*/


#define PORT_LED        8
#define PORT_OPTICAL    2

volatile boolean passou     = false;

// GIROS
int count                   = 0;
int pulsoPorGiro            = 5;
int media = 0;


// RPM
long countRpm               = 0;
long rpm                    = 0;
unsigned long timeRpm       = 0;


// TEMPO GIRO
unsigned long timePlay      = 0;


/*
 * 
*/
void prepareOptical(){
  attachInterrupt(digitalPinToInterrupt(PORT_OPTICAL),captureOptical, FALLING);
}


/*
 * 
*/
void captureOptical(){
  passou = true;
}

/*
 * 
*/
void setMedia(int _media){
  media = (_media / pulsoPorGiro);
}

/*
 * 
*/
int getMedia(){
  return media;
}

/*
 * Atualiza a Rotação por Minuto
*/
void setRpm(int _rpm){
  rpm = _rpm;
}

/*
 * Retorn a Rotação por Minuto Gerada
*/
int getRpm(){
  return rpm;
}


/*
 * 
*/
boolean countPulsoSensor(){
  if(passou){
      //detachInterrupt(digitalPinToInterrupt(PORT_OPTICAL));
      count++;
      countRpm++;
      //Serial.println(count);
      setMedia(count);
      //prepareOptical();
      passou = false;
      return true;
  }
  
  return false;
}

/*
 *  Captura a Rotação Por Minuto do componente
*/
int monitoringRpm(){
  if(timeIsOver(timeRpm)){
    int auxRpm = (countRpm / pulsoPorGiro) * 30;
    countRpm = 0;
    timeRpm = millis() + 2000;
    return auxRpm;
  }
  return -1;
}


/*
 * 
*/
void monitoringOptical(){
  
  setRpm(monitoringRpm());
  countPulsoSensor();
  
  if(getRpm() > 0){
    Serial.print("Giros : ");
    Serial.print(getMedia());
    Serial.print("  RPM : ");
    Serial.println(getRpm());
  }
    
}
