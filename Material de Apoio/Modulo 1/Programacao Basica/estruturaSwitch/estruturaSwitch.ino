
/**
 *  switch(caso){
 *    case x : 
 *         //corpo
 *    break;
 *  }
 */


 char protocolo = 'C';

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando");

}

void loop() {

   if(Serial.available()){
      char var = Serial.read();
      Serial.println(var); 

      switch(var){
        case 'A' : 
              Serial.println("Você digitou A");
        break;
        case 'D' : 
              Serial.println("Você digitou D");
        break;
        case 'R' : 
              Serial.println("Você digitou R");
        break;
      }
     
   }
  
}
