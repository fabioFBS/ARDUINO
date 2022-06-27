
#define MODE_GAME 0
#define MODE_MENU 1 

#define SELECT_GAME_GIRO_LIVRE               2
#define SELECT_GAME_GIRO_JOGADORES           3

#define SELECT_GAME_DESAFIO_ALEATORIO        4
#define SELECT_GAME_DESAFIO_JOGADORES        5

#define SELECT_GAME_NONE                     0


boolean gameMode = MODE_GAME;
byte gameSelect  =  SELECT_GAME_GIRO_LIVRE;

int count_giros   = 0;
int count_rpm     = 0;
int count_min     = 0;
int count_sec     = 0;

unsigned long gameTimeStopped     = 0;
int limitGameTimeStopped          = 1000;

boolean gameStart                 = false;


/*
 * Altera o modo do Jogo para modo Game
*/
void setModeGame(){
    gameMode = MODE_GAME;
}

/*
 * Altera o modo do Jogo para modo Menu
*/
void setModeMenu(){
    gameMode = MODE_MENU;
}

/*
 * Retorna verdadeiro se estiver no modo Game
*/
boolean isModeMenu(){
    return (gameMode == MODE_MENU)? true : false;
}


void setGameSelect(byte game){
  gameSelect = game;
}

byte getGameSelect(){
  return gameSelect;
}

boolean isGameGirosLivre(){
  return (getGameSelect() == SELECT_GAME_GIRO_LIVRE)? true : false;
}



void monitoringEngine(){
    customMultiButton();

    if(isModeMenu())
      return;
   
    switch(getGameSelect()){
     case SELECT_GAME_GIRO_LIVRE:
           
          if(countPulsoSensor()){
              gameStart = true;
              gameTimeStopped = millis() + limitGameTimeStopped;
              count_giros = getMedia();  
             // Serial.println("Giros : ");
             // Serial.print(count_giros);
          }

          setRpm(monitoringRpm());
          if(getRpm() != -1){
            count_rpm  =  getRpm();
          }
          
          if(!gameStart){
            return;
          }
          
          if(monitoringTimeOver()){
            count_sec++;
            if(count_sec >= 60){
              count_sec = 0;
              count_min++;
            }
            updateTime(11,count_min,count_sec);
            
          }
            
          updateDataGiroLivre(count_giros,count_rpm);
          

          // Se o jogo parar por alguns segundos
          if(timeIsOver(gameTimeStopped)){
             gameStart = false;
          }
          
     break;
    }
}


/*
 * Limpa os dados do Jogo Atual
*/
void clearGame(){
  screenClear();
  count_min     = 0;
  count_sec     = 0;
  clearOptical();
}
