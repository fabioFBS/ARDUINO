
#define SIZE_OUTPUTS                        8
#define SIZE_SENSORS                        3

#define _DISABLED                           0
#define _PRINCIPAL                          1
#define _SECONDARY                          2


#define AZUL                                0
#define VERDE                               1
#define AMARELO                             2
#define VERMELHO                            3
#define TESTE                               4

#define IN_USE                            TESTE

/*  MODULO      IP             PORTA         MAC
 *  AZUL      192.168.5.230    8080          80
 *  VERDE     192.168.5.231    8081          81
 *  AMARELO   192.168.5.232    8082          82
 *  VERMELHO  192.168.5.233    8083          83
 *  TESTE     192.168.5.234    8084          84
*/

#if IN_USE == AZUL

    #define _KEY     "ABCDE"
     
    byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x80};
    IPAddress ip(192,168,5,230);
    #define _PORTA 8080

    // Define quais saídas estão sendo utilizadas pelos Sensores LDR e PIR
    boolean outputSensors[] = {true,false,false};

    #define TIME_PAUSE_STEP1                    480000   //  Tempo de espera para primeiro desligamento _PRINCIPAL (em milissegundos)
    #define TIME_PAUSE_STEP2                    120000   //  Tempo de espera para primeiro desligamentos _SECONDARY (em milissegundos)
    #define TIME_PAUSE_STEP3                     60000    //  Tempo de espera para demais _SECONDARY(em milissegundos)

    /*
     * R01 ->  LED BANCADA
     * R02 ->  LED CHURRASQUEIRA
     * R03 ->  VAZIO
     * R04 ->  LAMPADA MESA
     * R05 ->  LAVANDERIA
     * R06 ->  SPOTS BANCADA
     * R07 ->  SPOTS CORTINA
     * R08 ->  SPOTS LAVANDERIA
    */
    
    boolean groupLdr[SIZE_SENSORS][SIZE_OUTPUTS]  = {
                                      {1,0,0,1,1,1,0,0},
                                      {0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,0}
                                    };

    byte groupPir[SIZE_SENSORS][SIZE_OUTPUTS]     = {
                                      {_PRINCIPAL,_DISABLED,_DISABLED,_SECONDARY,_SECONDARY,_SECONDARY,_DISABLED,_DISABLED},
                                      {_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED},
                                      {_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED}
                                    };

    byte triggerLdr                               = 60; // Define a luminosidade para disparo dos pontos controlados pelo sensor (0 a 100%)

    /*
       *  Cenas pré configuradas
       *  0 = Deligar ponto
       *  1 = Ligar Ponto
       *  x = Desconsiderar Ponto
       *  
      */
     String scene[]   = {
                          "11xxxxxx",
                          "xxxxxxxx",
                          "xxxxxxxx",
                          "1xx11111",
                          "xxxxxxxx",
                          "0xx00000",
                          "x0xxxxxx",
                          "xxxxxxxx"
                       };

#elif IN_USE == VERDE

    #define _KEY     "ABCDE"
    
    byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x81};
    IPAddress ip(192,168,5,231);
    #define _PORTA 8081

    boolean outputSensors[] = {true,true,false};

    #define TIME_PAUSE_STEP1                    300000   //  Tempo de espera para primeiro desligamento _PRINCIPAL (em milissegundos)
    #define TIME_PAUSE_STEP2                    120000   //  Tempo de espera para primeiro desligamentos _SECONDARY (em milissegundos)
    #define TIME_PAUSE_STEP3                     60000    //  Tempo de espera para demais _SECONDARY(em milissegundos)

  /*
     * R01 ->  LED PAINEL TV
     * R02 ->  LED ENTRADA
     * R03 ->  LED BANHEIRO
     * R04 ->  LAMPADA CENTRAL
     * R05 ->  LAMPADA CORREDOR
     * R06 ->  SPOTS GELADEIRA
     * R07 ->  SPOTS SOFA
     * R08 ->  VAZIO
     * 
     * PIR01  - SALA
     * PIR02  - CORREDOR
     * PIR03  - Vazio
    */  

    boolean groupLdr[SIZE_SENSORS][SIZE_OUTPUTS] = {
                                      {0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,0},
                                      {0,0,0,0,0,0,0,0}
                                    };

    byte groupPir[SIZE_SENSORS][SIZE_OUTPUTS] = {
                                        {_DISABLED,_SECONDARY,_DISABLED,_SECONDARY,_DISABLED,_SECONDARY,_PRINCIPAL,_DISABLED},
                                        {_PRINCIPAL,_DISABLED,_DISABLED,_DISABLED,_SECONDARY,_DISABLED,_DISABLED,_DISABLED},
                                        {_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED}
                                      };

    byte triggerLdr                         = 30; // Define a luminosidade para disparo dos pontos controlados pelo sensor (0 a 100%)
    
    String scene[] = {
                          "00x00000",
                          "111xxxxx",
                          "xxxxxxxx",
                          "1111111x",
                          "0x0xxxxx",
                          "xxxxxxxx",
                          "x000000x",
                          "xxxxxxxx"
                       };
    
#elif IN_USE == AMARELO

     #define _KEY     "ABCDE"
     
    byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x82};
    IPAddress ip(192,168,5,232);
    #define _PORTA 8082

    boolean outputSensors[] = {true,false,false};

    #define TIME_PAUSE_STEP1                    480000   //  Tempo de espera para primeiro desligamento _PRINCIPAL (em milissegundos)
    #define TIME_PAUSE_STEP2                    120000   //  Tempo de espera para primeiro desligamentos _SECONDARY (em milissegundos)
    #define TIME_PAUSE_STEP3                     60000    //  Tempo de espera para demais _SECONDARY(em milissegundos)


    boolean groupLdr[SIZE_SENSORS][SIZE_OUTPUTS] = {
                                      {0,0,0,0,1,0,1,0},
                                      {1,1,1,1,0,1,1,1},
                                      {0,0,0,0,0,0,0,0}
                                    };

    byte groupPir[SIZE_SENSORS][SIZE_OUTPUTS] = {
                                      {_DISABLED,_DISABLED,_DISABLED,_DISABLED,_PRINCIPAL,_DISABLED,_SECONDARY,_DISABLED},
                                      {_SECONDARY,_SECONDARY,_SECONDARY,_PRINCIPAL,_DISABLED,_SECONDARY,_DISABLED,_SECONDARY},
                                      {_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED}
                                    };

    byte triggerLdr                         = 30; // Define a luminosidade para disparo dos pontos controlados pelo sensor (0 a 100%)
    
    String scene[] = {
                          "0000x0x0",
                          "111xxxxx",
                          "xxxxxxxx",
                          "xxxxxxxx",
                          "xxxxxxxx",
                          "xxxxxxxx",
                          "xxxxxxxx",
                          "xxxxxxxx"
                       };
    
#elif IN_USE == VERMELHO
    
    #define _KEY     "ABCDE"
 
    byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x83};
    IPAddress ip(192,168,5,233);
    #define _PORTA 8083

    boolean outputSensors[] = {true,true,false};

    #define TIME_PAUSE_STEP1                    480000   //  Tempo de espera para primeiro desligamento _PRINCIPAL (em milissegundos)
    #define TIME_PAUSE_STEP2                    120000   //  Tempo de espera para primeiro desligamentos _SECONDARY (em milissegundos)
    #define TIME_PAUSE_STEP3                     60000    //  Tempo de espera para demais _SECONDARY(em milissegundos)


    boolean groupLdr[SIZE_SENSORS][SIZE_OUTPUTS] = {
                                      {0,1,0,1,0,0,1,0},
                                      {0,0,0,0,1,0,0,0},
                                      {0,0,0,0,0,0,0,0}
                                    };

    byte groupPir[SIZE_SENSORS][SIZE_OUTPUTS] = {
                                      {_DISABLED,_DISABLED,_DISABLED,_PRINCIPAL,_DISABLED,_DISABLED,_SECONDARY,_DISABLED},
                                      {_DISABLED,_DISABLED,_DISABLED,_DISABLED,_PRINCIPAL,_DISABLED,_DISABLED,_DISABLED},
                                      {_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED}
                                    };

    byte triggerLdr                         = 30; // Define a luminosidade para disparo dos pontos controlados pelo sensor (0 a 100%)
    
    String scene[] = {
                          "0x0xx0x0",
                          "xxxxxxxx",
                          "1x1xx1x1",
                          "x1x1xx1x",
                          "xxxxxxxx",
                          "xxxxxxxx",
                          "x0x0xx0x",
                          "xxxxxxxx"
                       };
    
#elif IN_USE == TESTE

    #define _KEY     "ABCDE"
    
    byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x84};
    IPAddress ip(192,168,5,234);
    #define _PORTA 8084
   
    boolean outputSensors[] = {false,false,true};

    #define TIME_PAUSE_STEP1                    480000   //  Tempo de espera para primeiro desligamento _PRINCIPAL (em milissegundos)
    #define TIME_PAUSE_STEP2                    120000   //  Tempo de espera para primeiro desligamentos _SECONDARY (em milissegundos)
    #define TIME_PAUSE_STEP3                     60000    //  Tempo de espera para demais _SECONDARY(em milissegundos)


    boolean groupLdr[SIZE_SENSORS][SIZE_OUTPUTS] = {
                                      {0,0,0,0,0,0,0,0},
                                      {1,0,0,1,1,1,0,0},
                                      {0,0,0,0,0,0,0,0}
                                    };

    byte groupPir[SIZE_SENSORS][SIZE_OUTPUTS] = {
                                      {_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED},
                                      {_PRINCIPAL,_DISABLED,_DISABLED,_SECONDARY,_SECONDARY,_SECONDARY,_DISABLED,_DISABLED},
                                      {_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED,_DISABLED}
                                    };

    byte triggerLdr                         = 30; // Define a luminosidade para disparo dos pontos controlados pelo sensor (0 a 100%)

    String scene[] = {
                          "1xx111xx",
                          "xxxxxxxx",
                          "xxxxxxxx",
                          "0xx000xx",
                          "xxxxxxxx",
                          "xxxxxxxx",
                          "xxxxxxxx",
                          "xxxxxxxx"
                       };
    
#endif


/*
 * Define se as Cenas estão configuradas neste modulo
 * True ou false
*/
#define PRESS_OLD    true

/*
 *  Define o tempo que será necessário para que a Cena seja ativada.
 *  
*/
#define TIME_PRESSED    1.0 // (tempo em segundos)




boolean isSensor(byte pos){
    return outputSensors[pos];
}
 


  
