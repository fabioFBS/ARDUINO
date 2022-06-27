
#define PORT_BUZZER                5 // Buzzer Sinal Sonoro
#define TONE_DO                  262 // Frequencia 
#define TONE_RE                  294 // Frequencia 
#define TONE_MI                  330 // Frequencia 
#define TONE_FA                  350 // Frequencia 
#define TONE_SOL                 393 // Frequencia 
#define TONE_LA                  441 // Frequencia 
#define TONE_SI                  495 // Frequencia 


boolean flagBuzzer              = false; // Ligar e Desligar Buzzer
unsigned long tBuzzer           = 0;     // Temporiza Sirene entre On/Off
int tDelayBuzzer                = 2000;  // Tempo entre ON/OFF Sirene
boolean flagTone                = false; // Controla o Sinal On/OFF da Sirene



void prepareBuzzer(){
    toneStart();
}

void toneON(){
  pinMode(PORT_BUZZER,OUTPUT);
}

void toneOFF(){
  pinMode(PORT_BUZZER,INPUT);
}


/*
 *  Alterando o estado do Buzzer
 *  @param status  HIGH | LOW
 */
void setBuzzer(boolean status){
    flagBuzzer = status;
}

/*
 *  Retorna o estado atual do Buzzer
 *  @param true | false
 */
boolean getBuzzer(){
  return flagBuzzer;
}


void toneStart(){
    toneON();  
    tone(PORT_BUZZER,TONE_DO);
    delay(100);
    toneOFF();
    delay(100);
    toneON();  
    tone(PORT_BUZZER,TONE_LA);
    delay(100);
    toneOFF();
}

void toneAlertON(){
      toneON();
      tone(PORT_BUZZER,TONE_LA); 
      delay(100);
      toneOFF();
      
      delay(100);
      toneON();
      tone(PORT_BUZZER,TONE_LA); 
      delay(100);
      toneOFF();
      
      delay(100);
      toneON();
      tone(PORT_BUZZER,TONE_LA); 
      delay(100);
      toneOFF();
}

void toneAlertOFF(){
      toneON();
      tone(PORT_BUZZER,TONE_LA); 
      delay(100);
      toneOFF();
      
      delay(100);
      toneON();
      tone(PORT_BUZZER,TONE_LA); 
      delay(100);
      toneOFF();
      
      delay(100);
      toneON();
      tone(PORT_BUZZER,TONE_LA); 
      delay(100);
      toneOFF();
      
      delay(100);
      toneON();
      tone(PORT_BUZZER,TONE_DO); 
      delay(500);
      toneOFF();
      
}

void toneEmergency(){
  if(flagTone){
    toneON();
    tone(PORT_BUZZER,TONE_LA); 
  }else{
    toneOFF();
  }

  flagTone = !flagTone;
}

/*
 * Aciona Sirene Fazendo efeito ON/OFF
*/
void soundBuzzer(){
  if( waiting(tBuzzer) ){
     toneEmergency();
     tBuzzer = millis() + tDelayBuzzer;
  }
}
