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

enum {MENU_1,MENU_2,MENU_3};

#define SUBMENU_11    1
#define SUBMENU_12    2
#define SUBMENU_13    3

#define SUBMENU_31    1
#define SUBMENU_32    2


#define SIZE_LINE         3
#define SIZE_COLUMN       4
const String menuLcd[SIZE_LINE][SIZE_COLUMN] = {
    {"Menu 1 ->","SubMenu 1.1", "SubMenu 1.2","<- Voltar"},
    {"Menu 2"},
    {"Menu 3 ->","SubMenu 3.1","<- Voltar"},
};

byte lineMenuSelected           = -1;
byte columnMenuSelected         = 0;

byte pointerMenu                = LINE_SELECTED;

/*
 * 
*/
void prepareLcd(){
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("***  JORNADA ***");
  lcd.setCursor(0, 1);
  lcd.print("Seja Bem Vindo !");
  
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
  }else if(getPointerMenu() == COLUMN_SELECTED){
    moveColumn();
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
  lcd.clear();
  lcd.setCursor(0, 0);
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
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("***  CLICOU  ***");
                  lcd.setCursor(0, 1);
                  lcd.print("** SUBMENU 1.1 *");
                  delay(3000);
                  movingMenu();
                
            break;
            case SUBMENU_12:
                Serial.println("Voce esta no SUBMENU 12");
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("***  CLICOU  ***");
                  lcd.setCursor(0, 1);
                  lcd.print("** SUBMENU 1.2 *");
                  delay(3000);
                  movingMenu();
            break;
            case SUBMENU_13:
                Serial.println("Voce esta no SUBMENU 13");
                setPointerLine();
                movingMenu();
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
      break;     
      case MENU_3:
           switch(getColumnMenuSelected()){
            case SUBMENU_31:
                  Serial.println("Voce esta no SUBMENU 31");
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("***  CLICOU  ***");
                  lcd.setCursor(0, 1);
                  lcd.print("** SUBMENU 3.1 *");
                  delay(3000);
                  movingMenu();
            break;
            case SUBMENU_32:
                Serial.println("Voce esta no SUBMENU 32");
                 setPointerLine();
                 movingMenu();
            break;
            default:
                Serial.println("Clicou no menu 3");
                nextMenu();                
          }
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
