void void_reading_sensor(){  
  Serial.begin(9600); //INICIALIZA A SERIAL
  emon1.current(pinoSensor, CURRENT_CAL); //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO)
}

void reading_sensor(){
  emon1.calcVI(17, 100); //FUNÇÃO DE CÁLCULO (17 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
  double currentDraw = emon1.Irms; //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO

    Serial.print("Corrente medida: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(currentDraw); //IMPRIME NA SERIAL O VALOR DE CORRENTE MEDIDA
    Serial.println("A"); //IMPRIME O TEXTO NA SERIAL
    if(currentDraw == 0){
      currentDraw = 0;
    }

}

void primary_test(){
  Serial.println("iniciando primeiro teste");
  Serial.println("desativando rele");
  deactivating_relay();
  Serial.println("rele desativado");


}