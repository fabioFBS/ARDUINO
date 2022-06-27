/***********************************************
 *   COMPONENTE A.V.
 *   PUSHBUTTON / PULSADORES DIVERSOS
 ***********************************************/
 

#define PORT_BUTTON  5

boolean pressed = false;

/*
 * Inicializando e preparando o componente
*/
void prepareButton(){
  pinMode(PORT_BUTTON,INPUT_PULLUP);
}


/*
 * Informe as Regas para monitoramento
 */
void monitoringButton(){
   if(digitalRead(PORT_BUTTON) == LOW && pressed == false){
    delay(50);
      if(digitalRead(PORT_BUTTON) == LOW){
        pressed = true;
        Serial.println("Clicou");
        setFlag(!getFlag());
        // ação a ser executada
      }
   }else if(digitalRead(PORT_BUTTON) == HIGH && pressed == true){
      pressed = false;
   }
}
