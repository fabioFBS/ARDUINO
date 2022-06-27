#define BLYNK_PRINT Serial                      //Define o serial do Blynk
#include <WiFi.h>                               //Inclusão das bibliotecas
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = "seu_token";                      //Inclua aqui o token recebido por email
char ssid[] = "TP_LINK";                        //Insira aqui o nome da sua rede Wi-Fi
char pass[] = "56916050";                       //Insira aqui a senha da sua rede Wi-Fi
void setup() {
  Serial.begin(9600);                           //Inicialização do Monitor Serial
  Blynk.begin(auth, ssid, pass);                //Inicia o Blynk
  pinMode(23, OUTPUT);                          //Definição dos pinos a serem utilizados (botão estará na porta 21)
  pinMode(22, OUTPUT);
  pinMode(21, INPUT);
}
void loop() {
  Blynk.run();                                  //Ativa o Blynk
  if (digitalRead(21)) {                        //Verifica se o botão foi pressionado
    Blynk.notify("O botao foi pressionado");    //Se sim, envia uma notificação ao app
  }
}
