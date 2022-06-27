/*
 *  COMPONENTE RELE
*/

#define PORT_RELE   7
#define ON    LOW
#define OFF   !ON


/*
 * 
*/
void prepareRele(){
    pinMode(PORT_RELE, OUTPUT);//módulo relé para ativar e desativar
}

/*
*   Liga Rele
*/
void setReleON(){
    digitalWrite(PORT_RELE,ON);
}

/*
* Desliga Rele
*/
void setReleOFF(){
    digitalWrite(PORT_RELE,OFF);
}

/*
 * 
*/
void monitoringRele(){

}
