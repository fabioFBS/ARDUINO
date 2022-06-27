/*
 * Componente Led
*/

#define LED_LIGADO                  0
#define LED_RELE                    1
#define LED_PULSO                   2
#define LED_PIR                     3
#define LED_CENA                    4
#define LED_MODO_INT                5
#define LED_MODO_ECO                6
#define LED_REDE                    7


const byte PORT_LED[]               = {13,12,11,9,8,7,6,5};
#define SIZE_LED                    sizeof(PORT_LED)/sizeof(byte)


/*
 * Preparandos as portas de saída dos Leds
*/
void prepareLed(){
    for(byte x = 0; x < SIZE_LED; x++){
      pinMode(PORT_LED[x],OUTPUT);     
    }  
    digitalWrite(PORT_LED[LED_LIGADO],HIGH);
}


//  Acionamento LED RELE
void ledReleOn(){
  digitalWrite(PORT_LED[LED_RELE],HIGH);  
}


void ledReleOff(){
  digitalWrite(PORT_LED[LED_RELE],LOW);  
}


//  Acionamento LED PULSO
void ledPulsoOn(){
  digitalWrite(PORT_LED[LED_PULSO],HIGH);  
}


void ledPulsoOff(){
  digitalWrite(PORT_LED[LED_PULSO],LOW);  
}


//  Acionamento LED PULSO
void ledPirOn(){
  digitalWrite(PORT_LED[LED_PIR],HIGH);  
}


void ledPirOff(){
  digitalWrite(PORT_LED[LED_PIR],LOW);  
}


//  Acionamento LED CENA
void ledCenaOn(){
  digitalWrite(PORT_LED[LED_CENA],HIGH);  
}


void ledCenaOff(){
  digitalWrite(PORT_LED[LED_CENA],LOW);  
}


//  Acionamento LED MODO INTELIGENTE
void ledModoIntOn(){
  digitalWrite(PORT_LED[LED_MODO_INT],HIGH);  
}


void ledModoIntOff(){
  digitalWrite(PORT_LED[LED_MODO_INT],LOW);  
}


//  Acionamento LED MODO ECONOMICO
void ledModoEcoOn(){
  digitalWrite(PORT_LED[LED_MODO_ECO],HIGH);  
}


void ledModoEcoOff(){
  digitalWrite(PORT_LED[LED_MODO_ECO],LOW);  
}


//  Acionamento LED REDE (Comandos On-line)
void ledRedeOn(){
  digitalWrite(PORT_LED[LED_REDE],HIGH);  
}


void ledRedeOff(){
  digitalWrite(PORT_LED[LED_REDE],LOW);  
}


void monitoringLed(){}
