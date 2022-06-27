/*
 *  Variaveis de manipulação do usuário.
*/

#define CHIP    "(47)99999-55555"

#define LINHA       4
#define COLUNA      3
#define _DDI        0
#define _DDD        1
#define NUMERO      2


String fones[LINHA][COLUNA] ={
                    {"55","47","955555555"},
                    {"55","null","null"},
                    {"55","null","null"},
                    {"55","null","null"}
};


#define ON       LOW
#define OFF      !ON

char chave[]                        = "ABC"; // chave para validação das mensagens recebidas via SMS

#define PIR_VIOLATED                HIGH    // Define estado PIR quando violado.

boolean monitoringPIR               = true;   // Ativa/Desativa Monitoramento PIR
boolean activedEmergencyInPIR       = true;   // Ativa o rele de emergência quando violado algum sensor de presença


boolean monitoringBlackout          = true;   // Ativa/Desativa Monitoramento Blackout
boolean activedEmergencyInBlackout  = false;   // Ativa o rele de emergência quando identificado Blackout


boolean activeReceivementSMS        = true;   // Ativa o modo de controle via SMS
boolean activeReceivementCall       = true;   // Ativa o modo de controle via Chamada
