/*
 *   COMPONENTE BUZZER
 *   Utiliza o componente timeOver
*/

#define PORT_BUZZER               9
#define TONE_DO                  262 // Frequencia 
#define TONE_RE                  294 // Frequencia 
#define TONE_MI                  330 // Frequencia 
#define TONE_FA                  350 // Frequencia 
#define TONE_SOL                 393 // Frequencia 
#define TONE_LA                  441 // Frequencia 
#define TONE_SI                  495 // Frequencia 


boolean flagTone                  = false;
unsigned long futureTimeBuzzer    = 0;
int delayTimeBuzzer               = 1000;

boolean flagBuzzer                = false;


/*
 * 
*/
void prepareBuzzer(){
  toneStart();
}

/*
 * 
*/
void toneON(){
  pinMode(PORT_BUZZER,OUTPUT);
}

/*
 * 
*/
void toneOFF(){
  pinMode(PORT_BUZZER,INPUT);
}

/*
 *  Ativa e Destativa o Buzzer Emergency
*/
void setFlagTone(boolean status){
  flagTone = status;
}

/*
 * Retorna o status atual do Buzzer Emergency
*/
boolean getFlagTone(){
  return flagTone;
}

/*
 *  Ativa e Destativa o Buzzer
*/
void setFlagBuzzer(boolean status){
  flagBuzzer = status;
}

/*
 * Retorna o status atual do Buzzer
*/
boolean getFlagBuzzer(){
  return flagBuzzer;
}


/*
 * 
*/
void toneStart(){
      toneON();
      tone(PORT_BUZZER,TONE_DO);
      delay(100);
      toneOFF();
      delay(100);
      tone(PORT_BUZZER,TONE_FA);
      delay(100);
      toneOFF();
      delay(100);
      tone(PORT_BUZZER,TONE_LA);
      delay(100);
      toneOFF();
}

/*
 * 
*/
void toneEnd(){
    toneON();
    tone(PORT_BUZZER,TONE_LA);
    delay(100);
    toneOFF();
    delay(100);
    tone(PORT_BUZZER,TONE_FA);
    delay(100);
    toneOFF();
    delay(100);
    tone(PORT_BUZZER,TONE_DO);
    delay(100);
    toneOFF();
}

/*
 * Gera o aviso sonoro de Ativado/Desativado
*/
void toneEmergency(){
  if(getFlagTone()){
    toneON();
    tone(PORT_BUZZER,TONE_LA);
  }else{
    toneOFF();
  }

   setFlagTone(!getFlagTone());
  //flagTone = !flagTone;
}

/*
 * Gera o aviso sonoro de Ativado/Desativado
*/
void soundBuzzer(){
  if(timeIsOver(futureTimeBuzzer)){
    toneEmergency();
    futureTimeBuzzer = millis() + delayTimeBuzzer;
  }
}

void monitoringBuzzer(){

}
