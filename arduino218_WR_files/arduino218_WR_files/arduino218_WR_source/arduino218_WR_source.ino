/* =============================================================================================================

    Aula 218

    Menu em formato de lista horizontal


============================================================================================================= */


// =============================================================================================================
// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal.h>


// =============================================================================================================
// --- Mapeamento de Hardware --- 
#define   bt_r   14   //botão direita
#define   bt_l   15   //botão esquerda
#define   bt_e   16   //botão enter
#define   bt_b   17   //botão voltar


// =============================================================================================================
// --- Constantes e Objetos --- 
#define   menu_max   4                  //número máximo de menus existentes
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// =============================================================================================================
// --- Protótipo das Funções ---
void keyboard();
void menu1();
void menu2();
void menu3();
void menu4();

// =============================================================================================================
// =============================================================================================================
// --- Variáveis Globais --- 
int menu_num = 1, sub_menu = 1;


// =============================================================================================================
// --- Configurações Iniciais ---
void setup() 
{
  pinMode(bt_r, INPUT_PULLUP);
  pinMode(bt_l, INPUT_PULLUP);
  pinMode(bt_e, INPUT_PULLUP);
  pinMode(bt_b, INPUT_PULLUP);
 
  lcd.begin(16, 2);
 

} //end setup


// =============================================================================================================
// --- Configurações Iniciais ---
void loop() 
{

  keyboard();
  
  switch(menu_num)
  {
    case 1: menu1(); break;
    case 2: menu2(); break;
    case 3: menu3(); break;
    case 4: menu4(); break;
    
    
  } //end switch

} //end loop


// =============================================================================================================
// --- Desenvolvimento das Funções ---
void keyboard()
{
   if(!digitalRead(bt_r) && sub_menu == 1)
   {
      delay(150);
      if(menu_num <= menu_max) menu_num += 1;
    
   } //end bt_r

   if(!digitalRead(bt_l) && sub_menu == 1)
   {
      delay(150);
      if(menu_num > 0) menu_num -= 1;
    
   } //end bt_l

   if(!digitalRead(bt_e))
   {
      delay(150);
      if(sub_menu <= 2) sub_menu += 1;
    
   } //end bt_e

   if(!digitalRead(bt_b))
   {
      delay(150);
      if(sub_menu > 0) sub_menu -= 1;
    
   } //end bt_b
   
  
} //end keyboard


void menu1()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("   Voltimetro  >");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print("   Voltimetro   ");
       lcd.setCursor(0,1);
       lcd.print("   10.0 Volts   ");
       
       break;
  }
  
  
} //end menu1


void menu2()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("<  Amperimetro >");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print("   Amperimetro  ");
       lcd.setCursor(0,1);
       lcd.print("    1.5 Amps    ");
       break;
  }
  
  
} //end menu2


void menu3()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("<  Ohmimetro   >");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print("   Ohmimetro    ");
       lcd.setCursor(0,1);
       lcd.print("    100 Ohms    ");
       break;
  }
  
  
} //end menu3


void menu4()
{
  switch(sub_menu)
  {
     case 1:
       lcd.setCursor(0,0);
       lcd.print("<  Wattimetro   ");
       lcd.setCursor(0,1);
       lcd.print("                ");
       break;
     case 2:
       lcd.setCursor(0,0);
       lcd.print("   Wattimetro   ");
       lcd.setCursor(0,1);
       lcd.print("    55 Watts    ");
       break;
  }
  
  
} //end menu4
