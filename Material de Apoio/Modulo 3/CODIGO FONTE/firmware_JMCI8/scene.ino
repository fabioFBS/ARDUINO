/*
 * COMPONENTE CENA
*/

#define CMD_CLEAR                             '?'

/*
 *  Cenas pré configuradas
 *  0 = Deligar ponto
 *  1 = Ligar Ponto
 *  x = Desconsiderar Ponto
*/
//String scene[] = {
//                    "1xx111xx",
//                    "xxxxxxxx",
//                    "xxxxxxxx",
//                    "0xx000xx",
//                    "xxxxxxxx",
//                    "xxxxxxxx",
//                    "xxxxxxxx",
//                    "xxxxxxxx"
//                 };
#define   SIZE_SCENE                          sizeof(scene)/sizeof(String)

#define SIZE_BUFFER_SCENE                     10
char bufferCommand[SIZE_BUFFER_SCENE];

byte posCommandBuffer                         = 0;

boolean flagExecuteScene                      = false; 

unsigned long futureTimeScene                 = 0;
#define TIME_DELAY_SCENE                      300


void prepareScene(){}


/*
 *  Coloca como True ou false a flag que controla a execução das cenas 
*/
void setFlagExecuteScene(byte status){
  flagExecuteScene = status;
}


/*
 * Retorna true se a Cena está sendo executada.
*/
boolean getFlagExecuteScene(){
    return flagExecuteScene;
}


/*
 *  Limpa o buffer da Cena que foi executada
*/
void clearBuffer(){
   for(int x = 0 ; x < SIZE_BUFFER_SCENE ; x++){
         bufferCommand[x] = CMD_CLEAR;
    }
    posCommandBuffer = 0;
    Serial.println("Limpando Buffer...");
}


/*
 *  Monitora a execução da cena solicitada
 *  e esvazia o buffer
*/
void monitoringScene(){

  if(getFlagExecuteScene() && timeIsOver(futureTimeScene)){
    if(posCommandBuffer < SIZE_BUFFER_SCENE){
        if(bufferCommand[posCommandBuffer] == '0' || bufferCommand[posCommandBuffer] == '1'){
            modifyOutputPir(posCommandBuffer);
            setRele(posCommandBuffer,(bufferCommand[posCommandBuffer] == '1') ? ON : OFF);
            futureTimeScene = millis() + TIME_DELAY_SCENE;
            printValuesReles();
        }
        posCommandBuffer ++;
    }else{
        // limpa buffer
        clearBuffer();
        setFlagExecuteScene(false);
    }
  }
     
}


/*
 * Armazena a cena programada no buffer de execução
*/
void executeScene(byte pos){
    int _size = (scene[pos]).length();
    for(int x = 0 ; x < _size ; x++){
         bufferCommand[x] = scene[pos][x];
     }
     setFlagExecuteScene(true);
}


/*
 * Imprime no Serial Monitor as cenas pre-configuradas
*/
void showScenes(){
   Serial.println(F("*********************************"));
   Serial.println(F("[CENAS PRE-CONFIGURADAS] "));
   Serial.println(F("**  0 = Desligar"));
   Serial.println(F("**  1 = Ligar"));
   Serial.println(F("**  x = Desconsiderar"));
   Serial.println(F("*********************************"));
  
    for(int x = 0 ; x < SIZE_SCENE ; x++){
         Serial.print(F("CENA PULSADOR P0"));
         Serial.print(x + 1);
         Serial.print(F(" => "));
         Serial.println(scene[x]);
    }

    Serial.println();
}
