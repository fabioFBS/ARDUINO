/*
 * COMPONENTE SINGLE BUTTON
 * Utiliza Serial
*/

#define PORT_SINGLE_BUTTON  5
boolean pressedSingleButton  = false;


/*
 *  Preparando o sistema
*/
void prepareSingleButton(){
     pinMode(PORT_SINGLE_BUTTON, INPUT_PULLUP);  
}


/*
 * Monitora a porta configura identificando um clique
 * @return true | false
*/
boolean monitoringSingleButton(){
  if(digitalRead(PORT_SINGLE_BUTTON) == LOW && pressedSingleButton == false) {
    delay(40);
      if(digitalRead(PORT_SINGLE_BUTTON) == LOW) {
          // Ação a ser executada após o clique
          pressedSingleButton = true;
          return true;
      }
  }else{
    if(digitalRead(PORT_SINGLE_BUTTON) == HIGH && pressedSingleButton == true) {
      pressedSingleButton = false; 
    }
  }
  return false;
}


/*
 *  Evento de Test
*/
void testSingleButton(){
   if(monitoringSingleButton()){
      Serial.println("Clicou");
   }
}
