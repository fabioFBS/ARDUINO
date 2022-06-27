/*
 * Componente MultiCenas
*/


const byte PORT_CENA[]                      = {38,39,40};
#define SIZE_CENA                           sizeof(PORT_CENA)/sizeof(byte)
boolean flag_pressedMultiCena[SIZE_CENA];


/*
 * Preparando as portas de Entrada Multi-Cenas
*/
void prepareMultiCena(){
  for(byte x = 0; x < SIZE_CENA; x++){
      pinMode(PORT_CENA[x],INPUT_PULLUP);
  } 
}


/*
 * Monitorando as entradas para ações
*/
void monitoringMultiCena(){
 for(byte x = 0; x < SIZE_CENA; x++){
      if(digitalRead(PORT_CENA[x]) == LOW && flag_pressedMultiCena[x] == false){
         delay(60);
         if(digitalRead(PORT_CENA[x]) == LOW){
            
            flag_pressedMultiCena[x] = true;
            Serial.print("Clicou na Cena [C");
            Serial.print(x+1);
            Serial.println("]");

            if(x == 0){
              chargeMode(true);
            }
           
         }
      }else{
        
        if(digitalRead(PORT_CENA[x]) == HIGH && flag_pressedMultiCena[x] == true){
          flag_pressedMultiCena[x] = false;
        } 
          
      }
    }
}
