/*
 * Componente Pulsadores
*/

const byte PORT_PULSADOR[]                  = {23,25,27,29,31,33,35,37};  
#define SIZE_PULSADOR                       sizeof(PORT_PULSADOR)/sizeof(byte)

boolean flag_pressed[SIZE_PULSADOR];

unsigned long futureTimePressed;
boolean flagPressedScene                    = false;



/*
 * Prepadando as porta de Entrada Pulsadores
*/
void preparePulsador(){
   for(byte x = 0; x < SIZE_PULSADOR; x++){
      pinMode(PORT_PULSADOR[x],INPUT_PULLUP);
    
    } 
}


/*
 * Retorna o tamanho do Array Pulsador
*/
byte getSizePulsador(){
  return SIZE_PULSADOR;
}


/*
 * Retorna o Status do Pulsador
*/
boolean getPulsador(byte pos){
  return (digitalRead(PORT_PULSADOR[pos]));
}


/*
 * Monitorando as portas de entrada para identificar os cliques
 * e executar as ações configuradas
*/
void monitoringPulsador(){
    for(byte x = 0; x < SIZE_PULSADOR; x++){
      if(digitalRead(PORT_PULSADOR[x]) == LOW && flag_pressed[x] == false){
         delay(60);
         if(digitalRead(PORT_PULSADOR[x]) == LOW){
            
            flag_pressed[x] = true; 
            
            Serial.print("Clicou na Porta (P");
            Serial.print(x+1);
            Serial.println(")"); 
            ledPulsoOn();  
            modifyOutputLdr(x);

            if(isModeIntelligent()){
                  modifyOutputPir(x);
            }

            if(!PRESS_OLD){
              setRele(x,!getRele(x)); 
            }
            futureTimePressed = millis() + (TIME_PRESSED * 1000);
                  
                             
         }
      }else{
        if(digitalRead(PORT_PULSADOR[x]) == HIGH && flag_pressed[x] == true){
          flag_pressed[x] = false;
          ledPulsoOff();
          modifyOutputLdr(x);

            if(flagPressedScene){
              // Criar funcao para executar a cena
              //executeScene(x);
              flagPressedScene = false;
              
            }else{
              setRele(x,!getRele(x)); 
              printValuesReles();
              // Finalizar Cena
              
              if(getFlagExecuteScene()){
                clearBuffer();
                setFlagExecuteScene(false);
              }
              
            }        
        }     
        if(timeIsOver(futureTimePressed) && digitalRead(PORT_PULSADOR[x]) == LOW && flag_pressed[x]){
            if(!flagPressedScene){Serial.println("Tempo para executar Cena Atingido"); executeScene(x);}
            flagPressedScene = true;
        }
                   
      }
    }
}
