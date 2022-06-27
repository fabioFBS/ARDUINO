/*
 * Componente Engine
*/

#define MODE_NORMAL          0
#define MODE_ECONOMIC        1
#define MODE_INTELLIGENT     2

byte mode                 = MODE_NORMAL;
byte flagLastMode         = mode;

unsigned long futureModeStart       = 0;
#define TIME_PAUSE_MODE              5000 // 30 segundos


void prepareEngine(){}


/*
 * Altera para o modo Normal
*/
void setModeNormal(){
    mode = MODE_NORMAL;
}


/*
 * Altera para o modo Economico
*/
void setModeEconomic(){
    mode = MODE_ECONOMIC;  
}


/*
 * Altera para o modo Inteligente
*/
void setModeIntelligent(){
    mode = MODE_INTELLIGENT;
}

/*
 * Retorna qual o modo atual
*/
byte getMode(){
    return mode;
}


/*
 *  Retorna se o Modo atual é o Modo Inteligente
*/
boolean isModeNormal(){
    return (getMode() == MODE_NORMAL) ? true : false;
}


/*
 *  Retorna se o Modo atual é o Modo Inteligente
*/
boolean isModeEconomic(){
    return (getMode() == MODE_ECONOMIC) ? true : false;
}


/*
 *  Retorna se o Modo atual é o Modo Inteligente
*/
boolean isModeIntelligent(){
    return (getMode() == MODE_INTELLIGENT) ? true : false;
}


/*
 * Atualiza o tempo de mudança dos modos
*/
void setFutureModeStart(){
    futureModeStart = millis() + TIME_PAUSE_MODE;
}


/*
 * Altera o Modo atual do sistema a cada chamada
 * Loop de modos
*/
void chargeMode(boolean automatic){

    ledModoEcoOff();
    ledModoIntOff();
    
    if( isModeNormal() ){
      if(automatic){
        setModeEconomic();
        ledModoEcoOn();
        Serial.println("Entrando no modo Economico");
      }else{
        setModeNormal();
        Serial.println("Entrando no modo Normal");
      }
      
     
    }else if(isModeEconomic() ){
      if(automatic){
          setModeIntelligent();
          ledModoIntOn();
          Serial.println("Entrando no modo Inteligente");
      }else{
          ledModoEcoOn();
          Serial.println("Entrando no modo Economico");
      }
      
    }else if( isModeIntelligent() ){
       if(automatic){
          Serial.println("Entrando no modo normal");
          setModeNormal();
       }else{
          setModeIntelligent();
          ledModoIntOn();
          Serial.println("Entrando no modo Inteligente");
       }
    }

    setFutureModeStart();
   
}


/*
 *  Execita as ações de inteligencia do sistema
 *  conforme o modo selecionado
*/
void monitoringEngine(){

  if(!timeIsOver(futureModeStart)){
    return;
  }

      switch(getMode()){
        case MODE_NORMAL:

             flagLastMode = MODE_NORMAL;
        break;
        case MODE_ECONOMIC:
             if(flagLastMode != mode){
                 // Desliga 50% dos pontos dos ambiente
                 turnOffSecondary();
                 flagLastMode = MODE_ECONOMIC;
             }

             monitoringPir();
             
        break;
        case MODE_INTELLIGENT:
              if(flagLastMode != mode){
                 // Atualizar a variavel que controla o tempo mínimo para desligamento dos pontos
                 setTimeFuture();
                 flagLastMode = MODE_INTELLIGENT;
             }
             
              monitoringPir();    
        break;
        
      }

      showPir();
      showLdr();
  
 }



 
