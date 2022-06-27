
SoftwareSerial mySerial(7,8);

#define   PORT_PWR_KEY      9

#define CR          (char) 0xD  // \r
#define ASPAS       (char) 0x22 // ""
#define SUB         (char) 0x1A // Ctrl + Z
#define EOT         (char) 0x3E // >
#define SOT         (char) 0x3C // < 

#define SMS         "AT+CMGF=1"
#define cSEND       "AT+CMGS="
#define cREADY      "AT+CMGL=\"ALL\""      // REC UNREAD = Mensagens não Lidas
#define cDELETE     "AT+CMGDA=\"DEL ALL\"" //Deleta todas as mensagens

#define DIAL        "ATD + +"  // Efetuando uma chamada telefonica

char bufferSms[10];                   // Recebe o buffer de SMS do cartão SIM

unsigned long  tNextSMS               = 0;
unsigned long  tDelayNextSMS          = 1800000 ; // Tempo em milissegundos para reenviar a mensagens de alerta 1000 * 60 * 30

boolean flagCall                      = false;
unsigned long tReceivedCall           = 0;
int dReceivedCall                     = 8000; // tempo para desligar chamada


boolean flagSMS                      = false;
unsigned long tReceivedSMS           = 0;
int dReceivedSMS                     = 1000; // tempo para leitura da mensagem SMS



void prepareSim(){
    mySerial.begin(19200);
    pinMode(PORT_PWR_KEY,OUTPUT);
    beginSIM();
}


/*
 * Preparando o Shield para envio e recebimento de mensagens
*/
void beginSIM(){
    Serial.println(F("Desligando SIM900"));
    mySerial.println("AT+CPOWD=1");
    mySerial.println(CR);
    delayWithLed(5000);
    Serial.println(F("Religando...."));
    powerUp();
    mySerial.println(SMS);
    mySerial.println(CR);
    delayWithLed(1000);
    mySerial.println("AT+CPAS");
    mySerial.println(CR);
    delayWithLed(1000);
    mySerial.println("AT+CMGF=1\n;AT+CNMI=1,2,0,0,0\n;ATX4\n;AT+COLP=1\n");
    mySerial.println(CR);
    Serial.println(F("Sistema On-line"));
    Serial.println();
      
}

/*
 * Comandos para executar o POWER UP
 * Desligar e Ligar o Shield
*/
void powerUp(){
  digitalWrite(PORT_PWR_KEY,LOW);
  delayWithLed(1000);
  digitalWrite(PORT_PWR_KEY,HIGH);
  delayWithLed(2000);
  digitalWrite(PORT_PWR_KEY,LOW);
  delayWithLed(3000);
}

/*
 * Limpa o tempo do próximo envio de mensagens SMS para envio imediato
*/
void clearTimeNextSMS(){
  tNextSMS = 0;
}

/*
 * Seta um novo tempo para o ciclo de disparo SMS
*/
void setNextSMS(){
  tNextSMS = millis() + tDelayNextSMS;
}

/*
 *  Retorna se já passou o tempo da última mensagem
*/
boolean getNextSMS(){
  return waiting(tNextSMS);
}


/*
 * Monta SMS para envio do Status do Sistema
*/
void createSMSMessage(){

    if(!getNextSMS()){
        return;
    }
    Serial.println();
    
    for(int i = 0; i < LINHA; i++ ){
      if(fones[i][NUMERO] != "null"){
        Serial.println(F("Enviando mensagem..."));
        setLedSMS(HIGH);
        headMessage(i);
        createContentMessage();
        footerMessage();
        setLedSMS(LOW);
      }
    }
    setNextSMS();
    Serial.println(F("Todas as mensagens foram enviadas"));
    Serial.println();
    
}

/*
 * Cabeçalho para configurar cartão SIM para envio de SMS
*/
void headMessage(byte pos){
   mySerial.print(SMS);
   mySerial.print(CR);
   delay(1000);
   mySerial.print(cSEND);
   mySerial.print(ASPAS);
   mySerial.print(fones[pos][_DDI]);
   mySerial.print(fones[pos][_DDD]);
   mySerial.print(fones[pos][NUMERO]);
   mySerial.println(ASPAS);
   delay(1000);
}

/*
 * Construindo mensagem de SMS do Status do Sistema
*/
void createContentMessage(){
  mySerial.println("Monitorando...");
  
  if(monitoringPIR){
    mySerial.print("PIR         = ");
    mySerial.println( (getFlagPIR()) ? VIOLADO : NORMAL);
  }

  if(monitoringBlackout){
    mySerial.print("Energia     = ");
    mySerial.println( (getFlagBlackout()) ? BLACKOUT : NORMAL);
  }

   mySerial.print("Sirene       = ");
   mySerial.println( (getBuzzer()) ? "ON" : "OFF");
   
   mySerial.print("rEmergencia  = ");
   mySerial.println((getRele() == ON) ? "ON": "OFF");

   mySerial.println("");
   delay(100);
}

/*
 * Finalizando Mensagem SMS
*/
void footerMessage(){
    mySerial.println(SUB); //Ctrl + z
    mySerial.println(CR);
    delay(1000);
    mySerial.println();
}

/*
 *  Envia SMS informando se o Sistema está Ativado ou Desativado
*/
void createSMSStatus(boolean status){
    for(int i = 0; i < LINHA; i++ ){
      if(fones[i][NUMERO] != "null"){
        setLedSMS(HIGH);
        headMessage(i);
        if(status){
              mySerial.print(MODEL); 
              mySerial.println(" Ativado"); 
              Serial.print(MODEL); 
              Serial.println(" Ativado"); 
              
        }else{
              mySerial.print(MODEL); 
              mySerial.println(" Desativado"); 
              Serial.print(MODEL); 
              Serial.println(" Ativado"); 
        }
        footerMessage();
        setLedSMS(LOW);
      }
    }
}

/*
 * 
 * Monitora o recebimento de chamadas e textos
*/
void monitoringSIM(){

  if(flagCall == false && flagSMS ==false){
      while(mySerial.available() != 0){
          setLedSMS(HIGH);
          char c = mySerial.read();
         // Serial.print(c);
          delay(10);  
  
          /*
           * Recebendo uma Chamada
          */
          if(c == 'R'){
              if(mySerial.read() == 'I'){
                  if(mySerial.read() == 'N'){
                      if(mySerial.read() == 'G'){
                        if(!flagCall) tReceivedCall = millis() + dReceivedCall;
                        flagCall = true;
                        break;
                        
                      }
                  }
              }
          }
  
          /*
           * Recebendo uma Mensagem de Texto
          */
          if(c == '+'){
              if(mySerial.read() == 'C'){
                  if(mySerial.read() == 'M'){
                      if(mySerial.read() == 'T'){
                        flagSMS = true;
                        break;
                        
                      }
                  }
              }
          }
       setLedSMS(LOW);
    }
  }
    
}

/*
 * Monitora o recebimento de chamadas de voz e retorno o status do sistema
*/
void getReceivementCall(){
  if(activeReceivementCall && flagCall){
    if(waiting(tReceivedCall)){
        mySerial.println("ATH");
        mySerial.println(CR);
        delayWithLed(1000);
        flagCall = false;

        clearTimeNextSMS();
        createSMSMessage();
        clearTimeNextSMS();
        
        delayWithLed(2000);
        
        while(mySerial.available() != 0 ){
            mySerial.read();
        }
    }
  }
}

void getReceivementSMS(){
  if(activeReceivementSMS && flagSMS){
    if(waiting(tReceivedSMS)){
         readSMS();
         flagSMS = false;   
    }
  }
}

/**
 * Lendo mensagem SMS
 * < ABC DS >
*/
void readSMS(){
  int i = 0;
  boolean ativa = false;
  while(mySerial.available() != 0 ){
        setLedSMS(HIGH);

        delay(20);
        char sms =  mySerial.read();
        if(sms == SOT){
          ativa = true;
        }
        if(ativa){
          if(sms != EOT){
             bufferSms[i] = sms;
             if( i < sizeof(bufferSms)) i++;
          }else{
              ativa = false;
              break;
          }
        }
        setLedSMS(LOW);
  }
  setLedSMS(LOW);

  Serial.println(F("**********************************"));
  Serial.println(bufferSms);
  Serial.println(F("**********************************"));

  delay(100);
  mySerial.println(CR);
  mySerial.println(cDELETE);
  mySerial.println(CR);
  delayWithLed(500);

  decodeSMS();
  
}

/*
 * Decodificando Mensagem SMS recebida
 * <ABCDS
 *             0   1   2   3   4   5
 * chave      [A] [B] [D]
 * bufferSMS  [<] [A] [B] [C] [S] [D] []
*/
void decodeSMS(){

    if(bufferSms[1] == chave[0] && bufferSms[2] == chave[1] && bufferSms[3] == chave[2]){

         switch(bufferSms[4]){
          case 'S':
               if(bufferSms[5] == 'L'){
                  setStartSystem(false);
                  actionPressedSwitch();
               }else if(bufferSms[5] == 'D'){
                  setStartSystem(true);
                  actionPressedSwitch();
               }
               
          break;
          case 'R':
                  if(bufferSms[5] == 'L'){
                      clearTimeNextSMS();
                      createSMSMessage();
                      clearTimeNextSMS();
                  }
          break;
         }
    }

    clearBuffer();
}

void clearBuffer(){
  byte i = 0;
  for (i; i < sizeof(bufferSms); i++){
    bufferSms[i] = '.';
  }
  bufferSms[i] = '\n';
}
