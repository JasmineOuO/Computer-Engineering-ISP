int ledDelay = 10000; // delay in between changes
int redPin = 10;
int yellowPin = 9;
int greenPin = 8;
int redPin2 = 7;
int yellowPin2 = 6;
int greenPin2 = 5;
//int buttonPin=4;

byte redPinState = HIGH; 
byte yellowPinState = LOW; 
byte greenPinState = LOW; 
byte red2PinState = LOW; 
byte yellow2PinState = LOW; 
byte green2PinState = HIGH;  
//byte buttonState=LOW;

long currentMillis = 0;    // stores the value of millis() in each iteration of loop()

long previousRedMillis=0;
long previousYellowMillis=0;
long previousGreenMillis=0;
long previousRed2Millis=0;
long previousYellow2Millis=0;
long previousGreen2Millis=0;
//long previousButtonMillis=0;

bool first=false;
bool first2=false;
bool first3=false;
bool buttonPressed=true;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin2, OUTPUT);
  pinMode(yellowPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  //pinMode(buttonPin,OUTPUT);
}

void loop() {
   currentMillis = millis();

   //readButton();
   if (buttonPressed)
   updateState(redPin,redPinState,previousRedMillis,2000,6000);
   else
   updateState(redPin,redPinState,previousRedMillis,4000,4000);

   if (buttonPressed)
   updateState(greenPin,greenPinState,previousGreenMillis,5000,2000);
   else if (first==false)
   updateState(greenPin,greenPinState,previousGreenMillis,3000,4000);
   else
   updateState(greenPin,greenPinState,previousGreenMillis,3000,5000);
   
   updateState(yellowPin,yellowPinState,previousYellowMillis,1000,7000);

   if (buttonPressed)
   updateState(redPin2,red2PinState,previousRed2Millis,5000,3000);
   else
   updateState(redPin2,red2PinState,previousRed2Millis,4000,4000);

   if (buttonPressed)
   updateState(greenPin2,green2PinState,previousGreen2Millis,2000,6000);
   else
   updateState(greenPin2,green2PinState,previousGreen2Millis,3000,5000);

   if (buttonPressed&&first3==false)
   updateState(yellowPin2,yellow2PinState,previousYellow2Millis,1000,2000);
   if (buttonPressed&&first3==true)
   updateState(yellowPin2,yellow2PinState,previousYellow2Millis,1000,5000);
   else if (first2==false)
   updateState(yellowPin2,yellow2PinState,previousYellow2Millis,1000,3000);
   else
   updateState(yellowPin2,yellow2PinState,previousYellow2Millis,1000,7000);
   
   switchLeds();
}

void updateState(int pin, byte &state, long &previousMillis, int intervalOn, int intervalOff){
  if (state==LOW){
    if (currentMillis - previousMillis >=intervalOff){
      state=HIGH;
      if (pin==8)
      first=true;
      if (pin==6)
      {
      first2=true;
      if (buttonPressed)
      first3=true;
      }
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
 digitalWrite(redPin, redPinState);
 digitalWrite(greenPin, greenPinState);
 digitalWrite(yellowPin, yellowPinState);
 digitalWrite(redPin2, red2PinState);
 digitalWrite(greenPin2, green2PinState);
 digitalWrite(yellowPin2, yellow2PinState);
}

//void readButton() {
//   if (digitalRead(buttonPin) == HIGH) 
//   {
//    buttonPressed=true;
//   }
//   else
//   buttonPressed=false;
//}
