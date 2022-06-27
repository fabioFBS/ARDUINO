
/*
 * Funções e seus tipos
 * 
*/



void setup() {
   Serial.begin(9600); // Inicializando Serial na velocidade definida (9600);
   Serial.println("Inicializando...");
   conexao();
}

void loop() {
  Serial.println(leituraSensor());
  delay(1000);
}
