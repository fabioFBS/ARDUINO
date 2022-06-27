/*
*  while(enquanto)
*/


int contador = 0;
boolean flag = false;

void setup() {
   Serial.begin(9600); // Inicializando Serial
   Serial.println("Inicializando..."); // mensagel
   
}

void loop(){
    if(contador <= 100){
        Serial.println(contador);
        contador++;
        if(contador == 100){
           flag = true;
        }
    }

    while(flag){
        contador = contador - 10;
        Serial.println(contador);
        delay(1000);

        if(contador == 101){
          flag = false;
        }
    }
  
}
