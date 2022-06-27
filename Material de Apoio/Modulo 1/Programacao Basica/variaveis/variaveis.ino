/*
*  Tipos de Variáveis mais utilizadas.
*/

int portaRele = 10;  //  valores até +- 32.767     
long nomeLong = 1000; // valores até +- 2.147.483.647
unsigned int nomeIntUns = 65000 ; // Valores até 65.535.
unsigned long nomeLongUns = 1234567890; // Valores até 4.294.967.295

float nomeFloat = 10.01;  // Variavel para guardar valor flutuantes
char nomaChar = 65; // Char pode receber caracter ou um numero inteiro, sempre seguirá tabela ASCII
boolean nomeBol = true; // Verdadeiro ou Falso apenas

/*
*  Arrays ou listas
*/
int nomeIntArray[] = {2,4,6,8}; //  Array de inteiros, Conjunto de informções dentro de uma única variável
int nomeCharArray[] = {'C','A','R','L','O','S'}; // Array de Caracteres
String nomeString = "Carlos Freitas"; // Conjunto de caracteres 


void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando...");

  Serial.println("Variaveis Simples"); // Imprimindo mensagem no Serial Monitor
  Serial.println(portaRele); // Imprimindo o valor da Variável
  Serial.println(nomeLong); // Imprimindo o valor da Variável
  Serial.println(nomeIntUns); // Imprimindo o valor da Variável
  Serial.println(nomeLongUns); // Imprimindo o valor da Variável
  Serial.println(nomeFloat); // Imprimindo o valor da Variável
  Serial.println(nomaChar); // Imprimindo o valor da Variável
  Serial.println(nomeBol); // Imprimindo o valor da Variável
  Serial.println("---------------------------------");
  Serial.println("Variaveis Inteiras do tipo Array");
  Serial.print(nomeIntArray[0]); // Imprimindo o valor da posição 0 da variável
  Serial.print(nomeIntArray[1]);// Imprimindo o valor da posição 1 da variável
  Serial.print(nomeIntArray[2]);// Imprimindo o valor da posição 2 da variável
  Serial.println(nomeIntArray[3]);  // Imprimindo o valor da posição 3 da variável
  Serial.println("---------------------------------");
  Serial.println("Variaveis Char do tipo Array");
  //Serial.println(nomeCharArray);  // Imprimindo todo o Array
  Serial.println(nomeCharArray[0]);
  Serial.println(nomeCharArray[1]);
  Serial.println(nomeCharArray[2]);
  Serial.println(nomeCharArray[3]);
  Serial.println(nomeCharArray[4]);
  Serial.println(nomeCharArray[6]);


  portaRele = 11;  // Atribiu novo valores.
  portaRele = 1 + 2 ; // Soma
  portaRele = 2 - 1 ; // Subtração
  portaRele = 4 / 2;  // Divisão
  portaRele = 4 * 10; // Multiplicação
  portaRele = 4 % 2;   // Captura o Resto de uma divisão
  

}

void loop() {

  portaRele =  3 + 3  -  (2 / 3)  * 5 ; //
  Serial.println(portaRele);
  
}
