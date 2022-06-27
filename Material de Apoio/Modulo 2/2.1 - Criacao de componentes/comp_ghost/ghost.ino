/*
 * COMPONENTE GHOST
 * UTILIZA COMPONENTE MEMORY
*/

#define REG_GHOST       500
#define _DEL            0x7F    

byte _origin = 0;

// S I S T E M A  H A C K E A D O
byte _m[] = {0x53,0x49,0x53,0x54,0x45,0x4D,0x41,0x20,0x48,0x41,0x43,0x4B,0x45,0x41,0x44,0x4F};

/*
 * Testa se foi gravado na memoria EEPROM o byte de validação
*/
void prepareGhost(){
    _origin = getMemory(REG_GHOST);
    if(_origin == _DEL){
     return;
    }else{
       blockGhost();
    }
}

/*
 *  Deve ser executado para autorizar a utilização do sistema
 *  Utilizar apenas uma vez no SETUP antes de gravar o código original
*/
void setGhost(){
    setMemory(REG_GHOST,_DEL);
}


/*
 *  Poderá adicionar testes a serem executados dentro do loop
*/
void monitoringGhost(){}


/*
 * Função para bloqueio do sistema e impressão da mensagem para o usuário
*/
void blockGhost(){
        String _g = "";
        for(byte x = 0; x < sizeof(_m)/sizeof(byte); x++){
          _g += (char)_m[x];
        }
        Serial.println(_g);
        while(1);
}
