/*
 *  COMPONENTE MEMORY
 *  UTILIZA BIBLIOTECA EEPROM
 *  ATmega 328p  = 1024 bytes
*/

#include <EEPROM.h>
#define REG_REFRESH     10 // 
#define NOT_EMPTY       0x20 // Space
    

/*
 * 
*/
void prepareMemory(){
  byte test = getMemory(REG_REFRESH);
  Serial.println(test);
  if(test != NOT_EMPTY){
     setMemory(REG_REFRESH,NOT_EMPTY);
  }
}


/*  0  1  2  3  4  5  6
 *  [] [] [] [] [] [] []
 *  Grava dados na Memória EEPROM
*/
void setMemory(int pos, byte data){
    EEPROM.update(pos,data);
//    Serial.print("Escrevendo na Posicao [");
//    Serial.print(pos);
//    Serial.print("] Dado : ");
//    Serial.println(data);
    
}

/*
 *  Returna dados de uma posição específica da memória
*/
byte getMemory(int pos){
    return EEPROM.read(pos);
}


/*
 *  Grava dados na posição responsável por restaurar o sistema
*/
void setRefreshMemory(){
   setMemory(REG_REFRESH,1);
   Serial.println("Restauracao de Fabrica executada");
   Serial.println("**** Reiniciar o sistema");
   while(1);
}


/*
 * 
*/
void monitoringMemory(){}
