/*
 *  COMPONENTE ENGINE
*/

#define PORT_ENGINE 10

/*
 * 
*/
void prepareEngine(){
    pinMode(PORT_ENGINE,OUTPUT);
}


/*
 *  Liga ou Desliga o Motor.
*/
void setStartEngine(boolean status){
    digitalWrite(PORT_ENGINE,status);
}

/*
 * 
*/
void monitoringEngine(){
  
  if(getLevelSensor(NIVEL_EMERGENCY) == NIVEL_NAO_ATINGIDO){
    setStartEngine(OFF);
    Serial.println("ALERTA - CAIXA MOTOR SEM AGUA");
  }else{
        if(getLevelSensor(NIVEL_100) == NIVEL_ATINGIDO
            && getLevelSensor(NIVEL_50) == NIVEL_ATINGIDO
              && getLevelSensor(NIVEL_15) == NIVEL_ATINGIDO){
            setStartEngine(OFF);
            Serial.println("DESLIGOU MOTOR");
            
        }else if(getLevelSensor(NIVEL_100) == NIVEL_NAO_ATINGIDO
            && getLevelSensor(NIVEL_50) == NIVEL_NAO_ATINGIDO
              && getLevelSensor(NIVEL_15) == NIVEL_NAO_ATINGIDO
                && getLevelSensor(NIVEL_EMERGENCY) == NIVEL_ATINGIDO){
          
            setStartEngine(ON);
            Serial.println("LIGOU MOTOR");
        }
  }
}
