/*
*  SERIAL
*/


void setup() {
   Serial.begin(9600); // Inicializando Serial na velocidade definida (9600);
   Serial.println("Inicializando...");

   Serial.print("Estou na Mesma Linha : ");
   Serial.println("Eu Também");

}

void loop() {

  if(Serial.available()){
    char c = Serial.read();
    switch(c){
      case 'A' :
            Serial.println("Imprimir valor do sensor X");
      break;
      case 'B' :
            Serial.println("Imprimir Menu");
      break;
    }

    
  }
}
