
/*
 * Valida o tempo atual.
*/
boolean waiting(unsigned long time){
    return (millis() > time) ? true : false;
}
