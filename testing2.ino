int ledDelay = 10000; // delay in between changes
int redPin = 10;
int yellowPin = 9;
int greenPin = 8;
int redPin2 = 7;
int yellowPin2 = 6;
int greenPin2 = 5;

byte redPinState = HIGH; 
byte yellowPinState = LOW; 
byte greenPinState = LOW; 
byte red2PinState = LOW; 
byte yellow2PinState = LOW; 
byte green2PinState = LOW;  

long currentMillis = 0;    // stores the value of millis() in each iteration of loop()
long redPinMillis = 0;
long yellowPinMillis = 0;
long greenPinMillis = 0;
long red2PinMillis = 0;
long yellow2PinMillis = 0;
long green2PinMillis = 0;

long previousRedMillis=0;
long previousYellowMillis=0;
long previousGreenMillis=0;
long previousRed2Millis=0;
long previousYellow2Millis=0;
long previousGreen2Millis=0;
bool first=false;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin2, OUTPUT);
  pinMode(yellowPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
}
void loop() {
   currentMillis = millis();
   updateState(redPin,redPinState,previousRedMillis,4000,6000);
   if (first==false)
   updateState(greenPin,greenPinState,previousGreenMillis,4000,4000);
   else
   updateState(greenPin,greenPinState,previousGreenMillis,4000,6000);
   updateState(yellowPin,yellowPinState,previousYellowMillis,2000,8000);
   switchLeds();
   
}

void updateState(int pin, byte &state, long &previousMillis, int intervalOn, int intervalOff){
  if (state==LOW){
    if (currentMillis - previousMillis >=intervalOff){
      state=HIGH;
      if (pin==8)
      first=true;
      previousMillis += intervalOff;
    }
  }
  else{
    if (currentMillis - previousMillis >= intervalOn) {
      state = LOW;
      previousMillis += intervalOn;
    }
  }
}

void switchLeds() {
     // this is the code that actually switches the LEDs on and off
 digitalWrite(redPin, redPinState);
 digitalWrite(greenPin, greenPinState);
 digitalWrite(yellowPin, yellowPinState);
}
