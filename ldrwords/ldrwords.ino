int sensorPin = A5;   // select the input pin for ldr
int sensorValue = 0;  // variable to store the value coming from the sensor

int sensorLED = 2;
int redPin = 10;
int yellowPin = 9;
int greenPin = 8;
int redPin2 = 7;
int yellowPin2 = 6;
int greenPin2 = 5;
int pedestrianPin=4;
int buttonPin=3;

byte redPinState = HIGH; 
byte yellowPinState = LOW; 
byte greenPinState = LOW; 
byte red2PinState = LOW; 
byte yellow2PinState = LOW; 
byte green2PinState = HIGH; 
byte pedestrianPinState=HIGH;
 
int buttonState=0;

long currentMillis = 0;    // stores the value of millis() in each iteration of loop()

long previousRedMillis=0;
long previousYellowMillis=0;
long previousGreenMillis=0;
long previousRed2Millis=0;
long previousYellow2Millis=0;
long previousGreen2Millis=0;
long previousPedestrianMillis=0;

long previousButtonMillis=0;

bool first=false;
bool first2=false;

void setup() {
      Serial.begin(9600); //sets serial port for communication
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin2, OUTPUT);
  pinMode(yellowPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(pedestrianPin, OUTPUT);
  pinMode(buttonPin,INPUT);
  pinMode (sensorLED, OUTPUT
  buttonState=HIGH;
}

void loop() {
   currentMillis = millis();
      ldr();
   if (greenPinState==LOW&&yellowPinState==LOW&&yellow2PinState==LOW&&red2PinState==LOW){
   readButton();}
   if (buttonState==LOW)
   {
   updateState(greenPin,greenPinState,previousGreenMillis,3000,3000);
   updateState(redPin,redPinState,previousRedMillis,2000,6000);
   updateState(yellowPin,yellowPinState,previousYellowMillis,1000,5000);
   
   updateState(pedestrianPin,pedestrianPinState,previousPedestrianMillis,2000,6000);
   
   updateState(redPin2,red2PinState,previousRed2Millis,4000,2000);
   if (currentMillis-previousButtonMillis<2000)
   {
   updateState(greenPin2,green2PinState,previousGreen2Millis,1000,3000);
   updateState(yellowPin2,yellow2PinState,previousYellow2Millis,1000,2000);
   }
   }
   else 
   {
   updateState(redPin,redPinState,previousRedMillis,4000,4000);
   if (first==false)
   updateState(greenPin,greenPinState,previousGreenMillis,3000,4000);
   else
   updateState(greenPin,greenPinState,previousGreenMillis,3000,5000);
   updateState(yellowPin,yellowPinState,previousYellowMillis,1000,7000);
  
   updateState(pedestrianPin,pedestrianPinState,previousPedestrianMillis,4000,4000);
   }
   if (yellowPinState==HIGH)
   updateState(pedestrianPin,pedestrianPinState,previousPedestrianMillis,100,100);
    if (redPinState==HIGH)
    pedestrianPinState=HIGH;
    if (greenPinState==HIGH)
    pedestrianPinState=LOW;
    
   //idk why this chunk of code is outside the "else" but it only works if it is
   updateState(redPin2,red2PinState,previousRed2Millis,4000,4000);
   updateState(greenPin2,green2PinState,previousGreen2Millis,3000,5000);
   if (first2==false)
   updateState(yellowPin2,yellow2PinState,previousYellow2Millis,1000,3000);
   else
   updateState(yellowPin2,yellow2PinState,previousYellow2Millis,1000,7000);
   //end code chunk
   
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
 digitalWrite(pedestrianPin, pedestrianPinState);
}

void readButton() {
   if (digitalRead(buttonPin) == LOW) {
     buttonState = LOW; 
   first=false;
   first2=false;
     previousButtonMillis=currentMillis;
   }
   if (buttonState==LOW&&currentMillis-previousButtonMillis>=5000)
   {
   buttonState=HIGH;
   }
 }
 
 void ldr() 
{
   sensorValue = analogRead(sensorPin);    
   Serial.println(sensorValue); //prints the values coming from the sensor on the screen
  
  if(sensorValue < 300 )
    digitalWrite(sensorLED,HIGH);
  
  else 
    digitalWrite(sensorLED,LOW);                  
}
