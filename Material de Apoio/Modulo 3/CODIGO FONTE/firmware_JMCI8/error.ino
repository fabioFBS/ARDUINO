enum error {
      E_100,  // Comunicao nao autorizada
      E_101,  // Modelo Desconhecido
      E_102   // Comando Desconhecido
};


/*
 * 
*/
void handleError(byte error){

    switch(error){
      case E_100:
              client.println(F("{\"error\":\"Comunicacao nao autorizada\"}"));
      break;
      case E_101:
              client.println(F("{\"error\":\"Modelo do modulo desconhecido\"}"));
      break;
      case E_102:
              client.println(F("{\"error\":\"Comando desconhecido\"}"));
      break;
    }
}
