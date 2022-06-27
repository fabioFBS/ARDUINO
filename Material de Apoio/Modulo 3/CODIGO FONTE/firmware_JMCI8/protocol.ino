
#define _START      0x3F // '?'
#define _END        0x21 // '!'



byte getEnd(){
  return _END;
}

byte getStart(){
  return _START;
}

/*
 * Função responsável por interpretar
 * os parâmetros enviados
 * 
 * cod=XXXXXX&model=JMCI8-ECO&prot=002R
*/
void interpreter(String *buff){
    Serial.println(*buff);

    String data;
    int sizeData;

    if( searchData(&(*buff),"cod=").equals(_KEY) ){
        if( searchData(&(*buff),"model=").equals(_MODEL) ){
            data = searchData(&(*buff),"prot=");
            sizeData = data.length();

            if(sizeData >= 4){

                if(data.startsWith("STATUS")){
                    httpResponse();
                
                }else if(data.startsWith("RESUME")){
                    httpResumeStatus();
                   
                
                }else if(data.startsWith(MULTI_COMMAND)){

                    setCommand(&data);
                    httpResponse();
                
                }else if(data[sizeData - 1] == SWITCH){      // 100R
                    int pos = convertCharToInt(data[sizeData - 3],data[sizeData - 2]);
                    if(pos >= 0 && pos < getSizeRele()){
                        setRele(pos, (data[sizeData - 4] == '1') ? ON : OFF);
                    }                  
                    httpResponse();
                    
                }else{
                    handleError(E_102);
                }

                
            } else{
                handleError(E_102);
            }

            
            
        }else{
          handleError(E_101);
        }
        
    }else{
      
        handleError(E_100);
    }
   
    
    
}

/*
 * (*prot) -> String na qual o valor deve ser procurado
 *  param  -> Parametro a ser procurado na String
 *  
 *  @return -> retorn o valor do parametro procurado
*/
String searchData(String *prot, String param){
  byte inicio = (*prot).indexOf(param);
  byte fim    = (*prot).indexOf('&',inicio);
  
  return (*prot).substring(inicio + (param).length(),fim);
}
