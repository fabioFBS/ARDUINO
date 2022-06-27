/*
 *  COMPONENTE LCD
 *  UTILIZA O COMPONENTE MULTI BUTTON
 *  UTILIZA BIBLIOTECA LiquidCrystal.h
 *  
*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

#define LINE_SELECTED         0
#define COLUMN_SELECTED       1

enum {MENU_1,MENU_2,MENU_3,MENU_4,MENU_5};

#define SUBMENU_11    1
#define SUBMENU_12    2

#define SUBMENU_21    1
#define SUBMENU_22    2


#define SIZE_LINE         5
#define SIZE_COLUMN       4
const String menuLcd[SIZE_LINE][SIZE_COLUMN] = {
    {"Giros e RPM->","Livre", "2 Jogadores"},
    {"Desafio X->","Aleatorio","2 Jogadores"},
    {"Calibrar"},
    {"Som on/off"},
    {"Sair"},
};

byte lineMenuSelected           = -1;
byte columnMenuSelected         = 0;

byte pointerMenu                = LINE_SELECTED;


/* Telas */
#define SCREEN_BRAND                  1
#define SCREEN_GIROS_LIVRE            2
#define SCREEN_GIROS_JOGADORES        3

#define SCREEN_DESAFIO_ALEATORIO      4
#define SCREEN_DESAFIO_JOGADORES      5

#define SCREEN_CLEAR                  6
#define SCREEN_CRON                   7



/*
 * 
*/
void prepareLcd(){
  lcd.begin(16, 2);
  screenLcd(SCREEN_BRAND);
  delay(2000);
  screenLcd(SCREEN_GIROS_LIVRE);
  
    
}

/*
 *  Altera o ponteiro para a linha desejada
*/
void setLineMenuSelected(byte pos){
    lineMenuSelected = pos;
}

/*
 *  Retorna em qual linha está o ponteiro
*/
byte getLineMenuSelected(){
    return lineMenuSelected;
}

/*
 * Altera o ponteiro para a coluna desejada
*/
void setColumnMenuSelected(byte pos){
    columnMenuSelected = pos;
}

/*
 * Retorna em qual coluna está o ponteiro
*/
byte getColumnMenuSelected(){
  return columnMenuSelected;
}

/*
 * Altera o ponteiro para mover entre linhas
*/
void setPointerLine(){
  setColumnMenuSelected(0);
  pointerMenu = LINE_SELECTED;
}

/*
 *  Altera o ponteiro para mover entre colunas
*/
void setPointerColumns(){
  pointerMenu = COLUMN_SELECTED;
}

/*
 * 
*/
byte getPointerMenu(){
    return pointerMenu;
}


/*
 * 
*/
void nextMenu(){
  if(getPointerMenu() == LINE_SELECTED){
    moveLine();
     lcd.clear();
     lcd.setCursor(0, 0);
    if(getLineMenuSelected() <= MENU_2){
       lcd.print("OPCOES de JOGOS ");
    }else{
       lcd.print("CONFIGURACOES   ");
    }
    
  }else if(getPointerMenu() == COLUMN_SELECTED){
       moveColumn();
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("MODO do JOGO    ");
     
  }
  movingMenu();
  
}

/*
 * Move as posições do Menu Coluna a Coluna
*/
void moveColumn(){
 setColumnMenuSelected(getColumnMenuSelected() + 1);
 /* ADD */
 if(getLineMenuSelected() == 255)
    setLineMenuSelected(getLineMenuSelected() + 1);
    
 if(getColumnMenuSelected() >= SIZE_COLUMN || !isMenuItem()){
    setColumnMenuSelected(1);
  }
}

/*
 * Move as posições do Menu Linha a Linha
*/
void moveLine(){
 setLineMenuSelected(getLineMenuSelected() + 1);
 if(getLineMenuSelected() >= SIZE_LINE || !isMenuItem()){
    setLineMenuSelected(0);
  }
}

/*
 * 
*/
void movingMenu(){
 // lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(menuLcd[getLineMenuSelected()][getColumnMenuSelected()]);
}

boolean isMenuItem(){
   return menuLcd[getLineMenuSelected()][getColumnMenuSelected()].length();
}

/*
 * 
*/
void monitoringLcd(){}


/*
 * 
*/
void actionMenuChoose(){
    switch(getLineMenuSelected()){
      case MENU_1:
          switch(getColumnMenuSelected()){
            case SUBMENU_11:
                 Serial.println("Voce esta no SUBMENU 11");
                 setPointerLine();
                 clearGame();
                 setModeGame();
                
            break;
            case SUBMENU_12:
                Serial.println("Voce esta no SUBMENU 12");
                 setPointerLine();
                 movingMenu();
                 clearGame();
                 
            break;
            default:
                Serial.println("Clicou no menu 1");
                nextMenu();                
          }
      break;     
      case MENU_2:
                Serial.println("Clicou no menu 2");
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("***  CLICOU  ***");
                lcd.setCursor(0, 1);
                lcd.print("**** MENU 2  ***");
                delay(3000);
                
                setPointerLine();
                movingMenu();
                screenLcd(getGameSelect());
      break;     
      case MENU_3:
           switch(getColumnMenuSelected()){
            default:
                Serial.println("Clicou no menu 3");
                nextMenu();                
          }
      break; 
      case MENU_5:
              setPointerLine();
              setModeGame();
              clearGame();
      break;    
     }
     
     debugLcd();
}


/*
 * 
*/
void debugLcd(){
    Serial.print("Linha :");
    Serial.print(getLineMenuSelected());
    Serial.print(" Coluna :");
    Serial.print(getColumnMenuSelected());
    Serial.print(" Ponteiro :");
    Serial.println(getPointerMenu() ? "COLUNA": "LINHA");
}

/*
  Telas do sistema 
*/
void screenLcd(byte pos){
  switch(pos){
    case SCREEN_BRAND: 
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    DESAFIO X   ");
    break;
    case SCREEN_GIROS_LIVRE: 
             lcd.clear();
             lcd.setCursor(0, 0);
             lcd.print("GIROS:0000 TEMPO");
             lcd.setCursor(0, 1);
             lcd.print("RPM  :0000 00:00");
    break;
    case SCREEN_CLEAR:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ZERANDO...");
    break;
    case SCREEN_CRON:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("   INICIANDO    ");
            lcd.setCursor(0, 1);
            lcd.print("  JOGO EM : ");
            for (byte x = 3; x >= 1; x--){
              lcd.setCursor(12, 1);
              lcd.print(x);
              delay(1000);
            }
            screenLcd(getGameSelect());
     break;
  }
}

/*
 * Atualiza os dados da Jogo
 * GIROS:0000 TEMPO
 * RPM  :0000 00:00
*/
void updateDataGiroLivre(int giros, int rpm){
            lcd.setCursor(6, 0);
            //0999
            if(giros < 999)
              lcd.print(0);
            if(giros < 99)
              lcd.print(0);
            if(giros < 9)
              lcd.print(0);
              lcd.print(giros);
              
            lcd.setCursor(6, 1);
              if(rpm < 999)
              lcd.print(0);
            if(rpm < 99)
              lcd.print(0);
            if(rpm < 9)
              lcd.print(0);
              lcd.print(rpm);
             
}

void updateTime(byte col, byte min, byte sec){
 
              lcd.setCursor(col, 1);
              if(min > 0){
                  lcd.print("0");
                  lcd.print(min);                   
              }else
                  lcd.print("00");

              lcd.print(":");
              
              if(sec < 10)
                  lcd.print("0");
              lcd.print(sec);    
                          
}


/*
 *  Limpa a Tela e 
*/

void screenClear(){
    screenLcd(SCREEN_CLEAR);
    delay(1000);
    screenLcd(SCREEN_CRON);
}
