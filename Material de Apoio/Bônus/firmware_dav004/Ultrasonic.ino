/***********************************************
 *   COMPONENTE A.V.
 *   SENSOR ULTRASONICO

 ***********************************************/

#define _NULL                                      -1

#define ULTRASONIC_1                                0
#define ULTRASONIC_2                                1

const byte ULTRASONIC_TRIGGER[]                     = {8,8};
const byte ULTRASONIC_ECHO[]                        = {6,7};
#define SIZEOF_ULTRASONIC                           sizeof(ULTRASONIC_ECHO)/sizeof(byte)

#define ULTRASONIC_VALIDATION                       3  // quantidade de leituras para validar
byte count_read_ultrasonic[SIZEOF_ULTRASONIC];
int  last_read_ultrasonic[SIZEOF_ULTRASONIC];

int limitDistanceUltrasonic[]                       ={8,16};

unsigned long futureTimeUltrasonicLedOff[SIZEOF_ULTRASONIC];
int delayTimeFuture                                 = 3000;



/*
 * Inicializando e preparando o componente
*/
void prepareUltrasonic(){
      for(byte x=0; x < SIZEOF_ULTRASONIC; x++){
         pinMode(ULTRASONIC_TRIGGER[x],OUTPUT);
         pinMode(ULTRASONIC_ECHO[x],INPUT); 
         count_read_ultrasonic[x] = 0;
         last_read_ultrasonic[x] = -1; 
         futureTimeUltrasonicLedOff[x] = 0;         
      }
}


/*
 * Retorna qual posição faz referência 
 * para o sensor Ultrassônico 1
 * dentro da Array
 */
byte getUltrasonic_1(){
    return ULTRASONIC_1;
}


/*
 * Retorna qual posição faz referência 
 * para o sensor Ultrassônico 2
 * dentro da Array
 */
byte getUltrasonic_2(){
    return ULTRASONIC_2;
}


/*
 * Função Responsável por disparar o Sinal
*/
unsigned long shootUltrasonic(byte pos){
    digitalWrite(ULTRASONIC_TRIGGER[pos],LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIGGER[pos],HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER[pos],LOW);
    return pulseIn(ULTRASONIC_ECHO[pos],HIGH);
}


/*
 * Retorna a distancia capturada pelo Sensor Ultrassônico
 * (343,5 m/s * 100 cm)/(1.000.000) = 0,3435
 *  0,3435 / 2 = 0,017175
*/
int convertUltrasonic(byte pos){
  return shootUltrasonic(pos) * 0.017175;
}


/*
 * Verifica a aproximação do sensor pela distancia informada
*/
boolean approachUltrasonic(byte pos, int *centimeters){
  int conv = convertUltrasonic(pos);
 // Serial.println(conv);
  if(conv != last_read_ultrasonic[pos]){
    last_read_ultrasonic[pos] = conv;
    count_read_ultrasonic[pos] = 0;
  }else{
    count_read_ultrasonic[pos] ++;
  }
  if(count_read_ultrasonic[pos] < ULTRASONIC_VALIDATION){
     if(conv < (*centimeters)){
        return true;
     }
     count_read_ultrasonic[pos] = 0;
  }
  return false;
}


/*
 * Retorna a valor da aproximação atual
 * após X leituras iguais
 */
int distanceUltrasonic(byte pos){
  int conv = convertUltrasonic(pos);
   if(conv != last_read_ultrasonic[pos]){
    last_read_ultrasonic[pos] = conv;
    count_read_ultrasonic[pos] = 0;
  }else{
    count_read_ultrasonic[pos] ++;
  }
  if(count_read_ultrasonic[pos] < ULTRASONIC_VALIDATION || conv < limitDistanceUltrasonic[1]){
     return conv;
  }
  
  return _NULL;
}


/*
 * Informe as Regas para monitoramento do Sensor
 * Monitoramento se a distância em cm está menor que o valor informado
 * 
*/
void monitoringUltrasonic(){
 
    int distance = distanceUltrasonic(ULTRASONIC_1);
    // Serial.println(distance);
    if(distance != _NULL){
        if(distance < limitDistanceUltrasonic[0]){
            futureTimeUltrasonicLedOff[ULTRASONIC_1] = millis() + delayTimeFuture;
            setLed1(true);
            setLed2(false);
        }else if(distance < limitDistanceUltrasonic[1]){
            futureTimeUltrasonicLedOff[ULTRASONIC_1] = millis() + delayTimeFuture;
            setLed1(false);
            setLed2(true);
        }
    }
    delay(100);
 
    
    distance = distanceUltrasonic(ULTRASONIC_2);
    //Serial.println(distance);
    if(distance != _NULL){
        if(distance < limitDistanceUltrasonic[0]){
            futureTimeUltrasonicLedOff[ULTRASONIC_2] = millis() + delayTimeFuture;
            setLed3(true);
            setLed4(false);
        }else if(distance < limitDistanceUltrasonic[1]){
            futureTimeUltrasonicLedOff[ULTRASONIC_2] = millis() + delayTimeFuture;
            setLed3(false);
            setLed4(true);
        }
    }
    delay(100);
}


/*
 * Monitora o desligamento dos Led
 * conforme tempo configurado
*/
void monitoringTurnOffUltrasonic(){
     for(byte x = 0; x < SIZEOF_ULTRASONIC; x++){
         if(timing(futureTimeUltrasonicLedOff[x])){
            turnAllOff(x);
         }         
      }
}
