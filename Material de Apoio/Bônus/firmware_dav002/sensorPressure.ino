/*
 * COMPONENTE PRESSURE SENSOR
 * 
*/

#define PORT_SENSOR_PRESSURE    A0
#define LIMIT_PRESSURE_SENSOR   100 // valor máximo da pressão

// Tempo de Espera para confirmar pressão acima do limite
#define TIME_WAIT_PRESSURE      2000 

// Tempo de esperar para ligar motor após pressão baixa ( 1h = 3600000)
#define TIME_WAIT_ENGINE_ON     20000  // 20000 = 20 segundos (para testar)

boolean flagStartPressure             = false;
unsigned long futurePressureSensor    = 0;


/*
 * 
*/
void preparePressureSensor(){
    pinMode(PORT_SENSOR_PRESSURE, INPUT);//sensor de pressao
}

/*
 * Leitura atual do sensor de pressão
*/
float readyPressureSensor(){
  return (analogRead(A0) * 5.00/1023) * 100;
}


/*
 * 
*/
void monitoringPressureSensor(){

  if(readyPressureSensor() > LIMIT_PRESSURE_SENSOR){
    if(flagStartPressure == false){
       Serial.println("Pressao alta - Contagem regressiva");
       futurePressureSensor = millis() + TIME_WAIT_PRESSURE;
       flagStartPressure = true;
    }
    if(timeIsOver(futurePressureSensor)){
       Serial.println("Desligando o Motor");
       setReleOFF();
       futurePressureSensor = millis() + TIME_WAIT_ENGINE_ON;
    }    
  }else{
    if(timeIsOver(futurePressureSensor)){
       Serial.println("Ligando o Motor");
       setReleON();
       flagStartPressure = false;
    } 
  }
    
}
