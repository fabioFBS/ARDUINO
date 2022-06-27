// INCLUSÃO DAS BIBLIOTECAS BAIXADAS!
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <PushButton.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
 
//Inicializando o display no endereço 0x27
LiquidCrystal_I2C lcd(0x27,20,4); // Configura endereço I2C e display com 20 caracteres e 4 linhas  
 
// PINAGENS DO PROJETO
#define button 5
#define trava 8
 
// INSTANCIANDO OBJETOS
SoftwareSerial mySerial(7, 6); // mySerial( Rx, Tx) <-- Pinagens do Sensor;
 
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
PushButton botao(button);
 
// DECLARAÇÃO DAS VARIÁVEIS E FUNCOES
uint8_t numID = 1;
bool gravar=false;
 
uint8_t modoGravacaoID(uint8_t IDgravar);
 
void setup() {
  lcd.begin(16,2);
  lcd.noCursor();
  pinMode(trava, OUTPUT);
  digitalWrite(trava, HIGH);
  
  //Serial.begin(9600);
  finger.begin(57600);
 
  if(finger.verifyPassword()){
    lcd.print("DY-50 encontrado!");
    delay(1000);
      
  } else {
    lcd.autoscroll();
    lcd.print("DY-50 não encontrado");
    delay(3000);
    lcd.clear();
    while(true) { 
      delay(1); 
     }
  }
  
  lcd.print("sensor Carregado");
  delay(900);
  lcd.clear();
  lcd.print("   Aguardando");
  lcd.setCursor(1,1);
  lcd.print("   entrada");
  
 
}
 
void loop() {
  botao.button_loop();
 
  if ( botao.pressed() ){
    gravar = true;
  }
 
  if(gravar){
    modoGravacaoID(0);
    gravar = false;
  }
 
  getFingerprintIDez();
  
}
 
uint8_t modoGravacaoID(uint8_t IDgravar) {
 
  int p = -1;
  lcd.print("Registre o ADM #");
  lcd.print(IDgravar);
  delay(2000);
  lcd.clear();
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      lcd.print(" concluído");
      break;
    case FINGERPRINT_NOFINGER:
      lcd.print(".");
      delay(200);
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.print("Erro");
      break;
    case FINGERPRINT_IMAGEFAIL:
      lcd.print("Erro leitura");
      break;
    default:
      lcd.print("ERROR");
      break;
    }
  }
 
  // Se não entrou em algum dos erros, todos os processos estão OK ! 
 
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      lcd.print("Leitura convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.print("tente novamente ");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.print("ERROR");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      lcd.print("Endereço invalido");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.print("Imagem invalida");
      return p;
    default:
      lcd.print("ERRO");
      return p;
  }
   lcd.clear();
  lcd.print("Retire o Dedo");
  delay(2000);
  lcd.clear();
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  lcd.print("ID "); 
  lcd.print(IDgravar);
  p = -1;
  lcd.print("  Insira o dedo ");
  lcd.setCursor(1,1);
  lcd.print("  novamente");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      lcd.print("Concluido ! ");
      break;
    case FINGERPRINT_NOFINGER:
      lcd.print(".");
      delay(200);
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.print("Erro no pacote");
      break;
    case FINGERPRINT_IMAGEFAIL:
      lcd.print("Erro na imagem");
      break;
    default:
      lcd.print("Erro ");
      break;
    }
  }
 
  // Se não entrou em algum dos erros, o primeiro processo está OK ! 
 
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
    lcd.print("Leitura convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
     lcd.print("Má leitura");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    lcd.print("Erro- comunicacao");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      lcd.print("Endereco invalido");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.print("imagem invalida");
      return p;
    default:
   lcd.print("Erro ");
      return p;
  }
  
  // Se não entrou em algum dos erros, todos os processos estão OK ! 
  lcd.print("Novo ID para #");  
  lcd.print(IDgravar);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
  lcd.print("As digitais batem!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.print("Erro de comunicação");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    lcd.print("As digitais não batem");
    return p;
  } else {
    lcd.print("Erro desconhecido");
    return p;
  }   
  
  lcd.print("ID "); 
  lcd.print(IDgravar);
  p = finger.storeModel(IDgravar);
  if (p == FINGERPRINT_OK) {
   lcd.print("Armazenado!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.print("Erro de comunicação");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    lcd.print("Erro na memória");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    lcd.print("Erro-memória flash");
    return p;
  } else {
    lcd.print("Erro desconhecido");
    return p;
  }   
}
 
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
 
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
 
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  //Alguma digital foi reconhecida pelo sensor
  if (finger.fingerID == 0) {
     lcd.print("Modo ADM ON");
     
     numID++;
     modoGravacaoID(numID);
     return 0; 
  
  } else {
     lcd.clear();
     digitalWrite(trava, LOW);
     lcd.print("ID encontrado #"); 
     lcd.print(finger.fingerID); 
     lcd.setCursor(1,1);
     lcd.print("seguranca:");
     lcd.print(finger.confidence); //Confiabilidade da leitura ! 
     delay(1000); //<<----- Tempo que a trava ficará aberta em milisegundos
     digitalWrite(trava, HIGH);
     delay(1000);
     lcd.clear();
     lcd.print("   Aguardando");
     lcd.setCursor(1,1);
     lcd.print("   entrada"); 
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
