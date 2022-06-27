/*
*  for (para , repita)
*/


                    // 0 1 2 3 4 5 6 7  8  9 10 11
int portasArduino[] = {2,3,4,5,6,7,8,9,10,11,12,13}; // Guardando portas do Arduino


byte numero = 2;
int resultado = 0;


void setup() {

  Serial.begin(9600); // Inicializando Serial
  Serial.println("Inicializando..."); // impressão

  for(int x=1; x <= (sizeof(portasArduino) / sizeof(int)); x++ ){
      pinMode(portasArduino[x],OUTPUT);

      if(x < 8){
        digitalWrite(portasArduino[x],LOW);
      }else{
        digitalWrite(portasArduino[x],HIGH);
      }
  }
  
  

}

void loop() {
 

}
