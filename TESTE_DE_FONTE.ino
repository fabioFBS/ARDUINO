//libraries---------------------------------------------------------
#include "EmonLib.h" //INCLUSÃO DE BIBLIOTECA QUE VAI LER O SENSOR DE T/C


//Doors-------------------------------------------------------------
#define CURRENT_CAL 18.40 //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO MEDINDO A CORRENTE DA CARGA)
const int pinoSensor = A2; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
const int pinButton D2; //PINO DE BOTAO DE COUNT 
const int pinButtonDefect = D3; //PINO DE BOTAO DE DEFEITO
const int pinRelay1 = D4; //PINO DO RELE 1
int count_button = 0;
int count_defeito = 0;


EnergyMonitor emon1; //CRIA UMA INSTÂNCIA

void setup() {
Serial.begin(9600); //INICIALIZA A SERIAL EM 9600
void_relay();
void_teste_inicial();
}

void loop() {
teste_inicial();
}
