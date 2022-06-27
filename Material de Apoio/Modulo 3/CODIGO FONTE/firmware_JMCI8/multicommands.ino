/*
 * E.000R.1S.101R.1S.1S.102R
*/

#define EMPTY                           " "

#define SIZE_COMMANDS                   20
String _commands[SIZE_COMMANDS];
byte posCommandExecuted                 = 0;

unsigned long futureTimeCommand         = 0;

void prepareMultiCommands(){
    clearCommands();
}


void setCommand(String *_data){

  String aux = "";
  int count  = 2;

  
  for(int a = 0; a < SIZE_COMMANDS; a++){
       aux = "";
       for(int x = count; x < (*_data).length(); x++){
            count++;
            if((*_data)[x] != LIMITER){
                aux += (*_data)[x];
            }else{
              break;
            }
       }

       if(aux.length()){
         _commands[a] = aux;
  
         Serial.print(F("posicao ["));
         Serial.print(a);
         Serial.print(F("] = "));
         Serial.println(_commands[a]);
       }else{
         break;
       }
       
  }
  
}

/*
 *  Ajusta o tempo de execução do comando
 *  conforme dados da Web
*/
void setFutureTimeCommand(float seconds){
    futureTimeCommand = millis() + (seconds * 1000);
}


/*
 *  Verifica se existe um comando a ser executado
*/
boolean isCommand(byte pos){
  return (_commands[pos].equals(EMPTY)) ? false : true;
}


/*
 * Limpa todo os comandos do buffer de execução
*/
void clearCommands(){
  for(int a = 0; a < SIZE_COMMANDS; a++){
      _commands[a] = EMPTY;
  }
  posCommandExecuted = 0;
}


/*
 * Executa as cenas enviadas pela WEB
*/
void monitoringMultiCommands(){

      if(isCommand(posCommandExecuted) && timeIsOver(futureTimeCommand)){
         // Executar
          Serial.print("-> Executando comando : ");
          Serial.println(_commands[posCommandExecuted]);

          if(_commands[posCommandExecuted].endsWith("S")){
              setFutureTimeCommand(1);
          
          }else if(_commands[posCommandExecuted].endsWith((String)SWITCH)){

                    // cod=XXXXXX&model=JMCI8-ECO&prot=002R
                   _buffer = "cod=";
                   _buffer += _KEY;
                   _buffer +="&model=";
                   _buffer += _MODEL;
                   _buffer +="&prot=";
                   _buffer += _commands[posCommandExecuted];
              
                   interpreter(&_buffer);
                   setFutureTimeCommand(0.5);
          }
          
         

          posCommandExecuted++;
          
         //limpar
         if(posCommandExecuted >= SIZE_COMMANDS || !isCommand(posCommandExecuted)){
            clearCommands();
         }
        
      }

}
