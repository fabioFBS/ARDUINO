

void setup() {
   prepareBuzzer();
   setFlagBuzzer(false);
}

void loop() {

  if(getFlagBuzzer()){
    soundBuzzer();
  }
  
}
