/*
 * COMPONENTE TIMING
*/

/*
 * Retorna verdadeiro quando o tempo atual passou 
 * o tempo do parametro (time)
*/
boolean timing(unsigned long time){
  return (millis() > time)? true : false;
}
