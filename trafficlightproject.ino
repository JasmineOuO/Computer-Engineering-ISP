//[0]=red [1]=green [2]=yellow [3]=red2 [4]=green2 [5]=yellow2
int pin [6]={10,9,8,7,6,5};
byte state [6]={HIGH,LOW,LOW,LOW,LOW,LOW};
long pinMillis [6];
long previousMillis [6];
int pinInterval [6]={500,500,500,500,500,500};//laura change these values for timing
long currentMillis = 0;

void setup() {
  for (int x=0;x<6;x++)
     {
  pinMode(pin[x], OUTPUT);
     }
}

void loop() {
  currentMillis = millis();
  for (int x=0;x<6;x++)
  {
   updateState(pin[x],state[x],previousMillis[x], pinInterval[x]);
  }
}

//if there is an error check if the same variable names effect it. 
void updateState(int &pin, byte &state, long &previousMillis, int &interval){
  int diff=currentMillis - previousMillis;
  if (state==LOW){
    if (diff >=interval){
      state=HIGH;
      previousMillis += interval;
    }
  }
  else{
    if (diff >= interval) {
      state = LOW;
      previousMillis += interval;
    }
  }
}

void switchLeds() {
     for (int x=0;x<6;x++)
     {
         digitalWrite(pin [x], state[x]);
     }
}
