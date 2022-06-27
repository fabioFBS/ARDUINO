/*
 * Componente Reles
*/

const byte PORT_RELE[]            = {22,24,26,28,30,32,34,36};    


/*
 * Preparando as portas de saídas dos Reles
*/
void prepareRele(){
   for(byte x = 0; x < getSizeRele(); x++){
        pinMode(PORT_RELE[x],OUTPUT);
        setRele(x,OFF);
   } 
}


/*
 * Retorna a quantidade de portas de saída
*/
byte getSizeRele(){
  return sizeof(PORT_RELE)/sizeof(byte);
}


/*
 * Liga/Desliga uma saída rele
*/
void setRele(byte pos, boolean status){
  digitalWrite(PORT_RELE[pos],status);
  monitoringLedRele();
}


/*
 * Retorna o estado atual da saída informada
*/
boolean getRele(byte pos){
  return digitalRead(PORT_RELE[pos]);
}


/*
 *  Monitora se existe algum rele ativo para ligar/desligar 
 *  o Led visual do módulo
*/
void monitoringLedRele(){
  boolean start = false;
  for(byte x = 0; x < getSizeRele(); x++){
      if(digitalRead(PORT_RELE[x]) == ON){
          start = true;
          break;
      }
  } 

  if(start){
     ledReleOn();
  }else{
     ledReleOff();
  }
}

void monitoringRele(){}

/*
 * Imprime como estão as 8 saídas
 * 0 ou 1
*/

void printValuesReles(){
  for(byte x = 0; x < getSizeRele(); x++){
     Serial.print((getRele(x) == ON) ? 1 : 0);
  } 
  Serial.println();
}
