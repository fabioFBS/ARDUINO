
//                                         14,15,16,17,18,19
// portas  0,1,2,3,4,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3,A4,A5.
// Portas analogicas 0 até 1023 quando Usadas como Entrada (analogRead)

/* 
*  if(Se)
* Operadores Lógicos ( == (igual), &&(E) , ||(OU) , >(Maior) , <(Menor) , >=(maior e igual),
  <=(menor e Igual), != (Diferente) , !(Negação/ Inverter))
  */


/* IF
 *  
 *   Se Carlos acordou coloque o cafe na mesa
 *  
 *  
 *   nome = Carlos
 *   status = acordou
 *   
 *   
 *   if(Carlos == acordou){
        Imprima "Coloque cafe na mesa"
 *   }
 *   
 *   
 *    Se( verdade ){
           executa este bloco...
      } senão {
           execute este bloco...
      }
 *  
 *  
*/

byte portaLDR = A3;
byte saidaLed = 7;

int valor_ldr = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando...");

  pinMode(portaLDR,INPUT);
  pinMode(saidaLed,OUTPUT);

}

void loop() {

  valor_ldr = analogRead(portaLDR);
  Serial.println(valor_ldr);
  if(valor_ldr >= 400){
    //corpo
    Serial.println("Maior que 400");
  }else{
    Serial.println("Menor que 400");
  }
  delay(1000);
}
