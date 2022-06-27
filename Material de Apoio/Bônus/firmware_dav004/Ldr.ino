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


/*
 * Retorna a o valor atual do Sensor LDR
*/
int getLDR(){
  return analogRead(PORT_LDR);
}


/*
 * Retorna verdadeiro quando o Sensor LDR 
 * atinge o % de luminosidade informado
 * no parâmetro
*/
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
boolean monitoringLDR(int percent){
   if(isViolateLDR(&percent)){
    //acão a ser executada
    Serial.print("Luminosidade está menor que ");
    Serial.print(percent);
    Serial.println("%");
    return true;
  }
  return false;
}


/*
 * Quando nenhum valor em % é informado
*/
void monitoringLDR(){
   monitoringLDR(10);
}
