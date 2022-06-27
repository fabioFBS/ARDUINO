/***********************************************
 *   COMPONENTE A.V.
 *   SENSOR LDR
 ***********************************************/
 
#define PORT_LDR    A0


/*
 * Inicializando e preparando o componente
*/
void prepareLDR(){
    pinMode(PORT_LDR,INPUT);
}

int getLDR(){
  return analogRead(PORT_LDR);
}

boolean isViolateLDR(int *percent){
  int conv = map(getLDR(),0,1023,0,100);
  if(conv < (*percent)){
     return true;
  }
  
  return false;
}

/*
 * Informe as Regas para monitoramento
 */
void monitoringLDR(int percent){
   if(isViolateLDR(&percent)){
    //acão a ser executada
    setFlag(false);
    Serial.print(" Luminosidade está menor que ");
    Serial.print(percent);
    Serial.println("%");
    delay(100);
  }
}


/*
 * Quando nenhum valor em % é informado
*/
void monitoringLDR(){
   monitoringLDR(10);
}
