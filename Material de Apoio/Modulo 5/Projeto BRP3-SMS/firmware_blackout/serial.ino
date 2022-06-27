
#define MODEL      "BRP3-SMS"
#define VERSION    "1.0"

void prepareSerial(){
      Serial.begin(19200); 
      Serial.println();
      Serial.println(F("*******************************************"));
      Serial.println(F("             Iniciando Sistema             "));
      Serial.println(F("*******************************************"));
      info();
      smsDestiny();
      Serial.println(F("*******************************************"));
      Serial.println();
      
}

void info(){
  Serial.print(F("Modelo        :"));
  Serial.println(MODEL);
  Serial.print(F("Versao        :"));
  Serial.println(VERSION);
  Serial.print(F("CHIP SIM      :"));
  Serial.println(CHIP);
}

/*
 * Imprime os telefones cadastrados para receber os Alertas
 * 55(47)999622575
*/
void smsDestiny(){
  Serial.println(F("*******************************************"));
  Serial.println(F(">>> SMS DESTINO"));
  for(int i = 0; i < LINHA; i++ ){
    if(fones[i][NUMERO] != "null"){
      Serial.print(F(" -> "));
      Serial.print(fones[i][_DDI]);
      Serial.print(F(" ("));
      Serial.print(fones[i][_DDD]);
      Serial.print(F(")"));
      Serial.println(fones[i][NUMERO]);
    }
  }
}
