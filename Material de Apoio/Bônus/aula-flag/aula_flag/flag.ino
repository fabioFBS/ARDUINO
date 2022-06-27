

boolean flag_acionamento = false;

void setFlag(boolean status){
  flag_acionamento = status;
}

boolean getFlag(){
  return flag_acionamento;
}

void monitoringFlag(){
  if(getFlag()){
    setLed(true);
    
  }else{
    setLed(false);  
  }
}
