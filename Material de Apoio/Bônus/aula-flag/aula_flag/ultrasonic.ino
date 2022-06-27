/***********************************************
 *   COMPONENTE A.V.
 *   SENSOR ULTRASONICO

 ***********************************************/

#define ULTRASONIC_TRIGGER   2
#define ULTRASONIC_ECHO      3

#define ULTRASONIC_VALIDATION   3  // quantidade de leituras para validar
byte count_read_ultrasonic = 0;
int  last_read_ultrasonic = -1;


/*
 * Inicializando e preparando o componente
*/
void prepareUltrasonic(){
    pinMode(ULTRASONIC_TRIGGER,OUTPUT);
    pinMode(ULTRASONIC_ECHO,INPUT);
}

/*
 * Função Responsável por disparar o Sinal
*/
unsigned long shootUltrasonic(){
    digitalWrite(ULTRASONIC_TRIGGER,LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIGGER,HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER,LOW);
    return pulseIn(ULTRASONIC_ECHO,HIGH);
}

/*
 * (343,5 m/s * 100 cm)/(1.000.000) = 0,3435
 *  0,3435 / 2 = 0,017175
*/
int convertUltrasonic(){
  return shootUltrasonic() * 0.017175;
}

/*
 * Verifica a aproximação do sensor pela distancia informada
*/
boolean approachUltrasonic(int *centimeters){
  int conv = convertUltrasonic();
  if(conv != last_read_ultrasonic){
    last_read_ultrasonic = conv;
    count_read_ultrasonic = 0;
  }else{
    count_read_ultrasonic ++;
  }
  if(count_read_ultrasonic > ULTRASONIC_VALIDATION){
     if(conv < (*centimeters)){
        return true;
     }
     count_read_ultrasonic = 0;
  }
  return false;
}


/*
 * Informe as Regas para monitoramento do Sensor
 * Monitoramento se a distancia em cm está menor que o valor informado
 * 
*/
void monitoringUltrasonic(int centimeters){
  if(approachUltrasonic(&centimeters)){
    //acão a ser executada
    setFlag(true);
    Serial.print(" Esta menos de ");
    Serial.print(centimeters);
    Serial.println(" cm de distancia ");
    delay(100);
  }
}

/*
 * Quando nenhum valor de distancia(cm) é informado
*/
void monitoringUltrasonic(){
  monitoringUltrasonic(30);
}
