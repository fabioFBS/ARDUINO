void void_relay(){
  pinMode(pinRelay1, OUTPUT);
  digitalWrite(pinRelay1, LOW);
}

void activating_relay(){
  digitalWrite(pinRelay1, HIGHT);
//digitalWrite(pinRelay1, HIGHT);
//digitalWrite(pinRelay1, HIGHT);
//digitalWrite(pinRelay1, HIGHT);
//digitalWrite(pinRelay1, HIGHT);
//digitalWrite(pinRelay1, HIGHT);
}
void deactivating_relay(){
  digitalWrite(pinRelay1, LOW);
//digitalWrite(pinRelay1, LOW);
//digitalWrite(pinRelay1, LOW);
//digitalWrite(pinRelay1, LOW);
//digitalWrite(pinRelay1, LOW);
//digitalWrite(pinRelay1, LOW);
}