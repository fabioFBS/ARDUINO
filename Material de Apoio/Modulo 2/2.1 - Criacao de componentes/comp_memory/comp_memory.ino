
byte portRele[] = {5,6,7,8,9};
#define SIZE_PORT_RELE    sizeof(portRele)/sizeof(byte)
boolean isPulso[SIZE_PORT_RELE] = {true,true,false,false,false};

void setup() {
    Serial.begin(9600);
    Serial.println("Inicializando..."); 

    prepareMemory();
    
    for(byte x = 0; x < SIZE_PORT_RELE; x++ ){
        isPulso[x] = getMemory(getFirstMemoryIsPulso()+x);
        Serial.print("PORTA [");
        Serial.print(portRele[x]);
        Serial.print("] ");
        Serial.println(isPulso[x] ? "PULSO" : "RETENCAO");
    }

}

void loop() {

    if(Serial.available() > 0){
      // 5R
      char c = Serial.read();
      delay(10);
      byte pos = 0;
      
      switch(c){
        case '5':  pos = 0;  break;
        case '6':  pos = 1;  break;
        case '7':  pos = 2;  break;
        case '8':  pos = 3;  break;
        case '9':  pos = 4;  break;
        case 'F': setRefreshMemory(); break;
        default:
          Serial.println("Primeiro Caractere invalido");
      }  
      
      c = Serial.read();
      switch(c){
        case 'P': setMemory(getFirstMemoryIsPulso()+pos, true); break;
        case 'R': setMemory(getFirstMemoryIsPulso()+pos, false); break;
        default:
          Serial.println("Segundo Caractere invalido");
      }
    }
}
