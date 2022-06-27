/*
 *  COMPONENTE TIME OVER
*/



/*
 * 
*/
void prepareTimeOver(){}

/*
 * 
*/
void monitoringTimeOver(){}

/*
 * Retorna se já chegou no tempo futuro
*/
boolean timeOver(unsigned long time){
  return (millis() > time)? true : false;
}
