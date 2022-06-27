
int valor = 1200;


void setup() {
    Serial.begin(9600);
    Serial.println("Inicializando..."); 

    // 00000100 10110000
    
    //00000100 10110000
    //00000000 11111111
    //00000000 10110000


    //00000100 10110000
    
    //00000000 00000100
    //         11111111
    //         00000100
    

    byte _byte  = valor & 255;
    byte _byte2 = (valor >> 8);
    
    Serial.println(_byte,DEC);
    Serial.println(_byte,BIN);

    Serial.println(_byte2,DEC);
    Serial.println(_byte2,BIN);
    Serial.println(valor,BIN);
    Serial.println("=====================");

    // 10110000
    // 00000100
    
    // 00000100 00000000
    //          10110000
    // 00000100 10110000

    
    int valor2 = (_byte2 << 8)  +  _byte;
    Serial.println(valor2);

   

    

}

void loop() {

}
