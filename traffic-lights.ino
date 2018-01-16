  /* Programmed by: Jackie Nguyen, Jasmine Ou and Laura Wong
     Teacher: Mr. Wong
     Date: Friday June 10, 2016
     Description: This program controls a T-intersection including the timing of the three traffic lights,
     the pedestrian lights, the pedestrian button, the LDR sensor to turn on the bright light of the lamp
     and an IR sensor to open and close the gates.
  */
  #include <Servo.h>
  
  Servo myservo;  // create servo object to control a servo
  int position = 0;  // state variable
  boolean forward = false;  // state variable
  long ts = millis ();  // time accounting.
  int senRead = 0;      // stores the sensor value
  int sensorValue = 0;  // variable to store the value coming from the sensor
  
  //These variables store the pin number for each piece of hardware (LED, sensor...etc)
  int redPin = 13;
  int yellowPin = 12;
  int greenPin = 11;
  int redPin2 = 10;
  int yellowPin2 = 9;
  int greenPin2 = 8;
  int buttonPin = 7;
  int pedestrianPin = 6;
  int pd = A0;
  int sensorPin = A5;
  int sensorLED = 5; //bright light
  
  //These variables store the state of the LEDs and button
  byte redPinState = HIGH;
  byte yellowPinState = LOW;
  byte greenPinState = LOW;
  byte red2PinState = LOW;
  byte yellow2PinState = LOW;
  byte green2PinState = HIGH;
  byte pedestrianPinState = HIGH;
  int buttonState = 0;
  
  long currentMillis = 0;    // stores the value of millis() in each iteration of loop()
  
  //These variables store the time that each LED/button state was previously changed for timing purposes
  long previousRedMillis = 0;
  long previousYellowMillis = 0;
  long previousGreenMillis = 0;
  long previousRed2Millis = 0;
  long previousYellow2Millis = 0;
  long previousGreen2Millis = 0;
  long previousPedestrianMillis = 0;
  long previousButtonMillis = 0;
  
  //booleans to determine if this is the first loop of the traffic light system since the timing is different for only the first loop for some LEDs
  bool first = false; 
  bool first2 = false;
  
  /* Sets up the pins and servo so that the LEDs are outputting and assigned to their respective pins. 
  The servo is attached to pin 0 and has an initial position of 0. The button state is set to high meaning
  that the button is not pressed initially and the photodiode (pd) is set to high to supply 5 volts to photodiode.
  */
  void setup ()
  {
      pinMode (redPin, OUTPUT);
      pinMode (yellowPin, OUTPUT);
      pinMode (greenPin, OUTPUT);
      pinMode (redPin2, OUTPUT);
      pinMode (yellowPin2, OUTPUT);
      pinMode (greenPin2, OUTPUT);
      pinMode (buttonPin, INPUT);
      pinMode (pedestrianPin, OUTPUT);
      pinMode (pd, INPUT);
      digitalWrite (pd, HIGH);    
      pinMode (sensorLED, OUTPUT);
      myservo.attach (0);
      myservo.write (0);
      buttonState = HIGH;
  }
  
  /*This loop makes sure that the traffic light system keeps running in a loop and that the sensors for the
  bright light (LDR sensor) and the motor (IR sensor) are constantly being read as well as the button. 
  If the button is pressed, the timing of the traffic lights is sped up for one cycle and then returns to normal. 
  The update state () method is called to update the state of a specific LED.
  The first cycle of the traffic light system has a slight variation of timing for the green and yellow LED so 
  the first variable is used in an if statement to ensure the timing is changed for the first cycle. 
  CurrentMillis is updates in each iteration to store the most recent time of the computer clock. 
  The switchLeds() method is called to turn the LEDs on or off.
  */
  void loop ()
  {
      currentMillis = millis ();
      ldr ();
      servo ();
      if (greenPinState == LOW && yellowPinState == LOW && yellow2PinState == LOW && red2PinState == LOW)
      {
          readButton ();
      }
  
  
      if (buttonState == LOW)
      {
          updateState (greenPin, greenPinState, previousGreenMillis, 3000, 3000);
          updateState (redPin, redPinState, previousRedMillis, 2000, 6000);
          updateState (yellowPin, yellowPinState, previousYellowMillis, 1000, 5000);
          updateState (pedestrianPin, pedestrianPinState, previousPedestrianMillis, 2000, 6000);
          updateState (redPin2, red2PinState, previousRed2Millis, 4000, 2000);
          if (currentMillis - previousButtonMillis < 2000)
          {
              updateState (greenPin2, green2PinState, previousGreen2Millis, 1000, 3000);
              updateState (yellowPin2, yellow2PinState, previousYellow2Millis, 1000, 2000);
          }
      }
  
  
      else
      {
          updateState (redPin, redPinState, previousRedMillis, 4000, 4000);
          if (first == false)
              updateState (greenPin, greenPinState, previousGreenMillis, 3000, 4000);
          else
              updateState (greenPin, greenPinState, previousGreenMillis, 3000, 5000);
          updateState (yellowPin, yellowPinState, previousYellowMillis, 1000, 7000);
          updateState (pedestrianPin, pedestrianPinState, previousPedestrianMillis, 4000, 4000);
      }
  
  
      if (yellowPinState == HIGH)
          updateState (pedestrianPin, pedestrianPinState, previousPedestrianMillis, 100, 100);
      if (redPinState == HIGH)
          pedestrianPinState = HIGH;
      if (greenPinState == HIGH)
          pedestrianPinState = LOW;
  
      updateState (redPin2, red2PinState, previousRed2Millis, 4000, 4000);
      updateState (greenPin2, green2PinState, previousGreen2Millis, 3000, 5000);
      if (first2 == false)
          updateState (yellowPin2, yellow2PinState, previousYellow2Millis, 1000, 3000);
      else
          updateState (yellowPin2, yellow2PinState, previousYellow2Millis, 1000, 7000);
  
      switchLeds ();
  }
  
  /*
  The updateState method with parameters passed in including the pin number, state value, previousMillis time, intervalOn and intervalOff.
  intervalOn is the number of milliseconds the specific LED should be on for. 
  intervalOff is the number of milliseconds the specific LED should be off for. 
  If the state is low, the state is changed to high, else the state is changed to low.
  The next if statements make sure that enough time has passed since the last time the LED state was changed according to intervalOn and intervalOff.
  The two if statements that change the first variable is to make sure that the first iteration of the loop has a different timing. 
 */ 
  void updateState (int pin, byte & state, long & previousMillis, int intervalOn, int intervalOff)
  {
      if (state == LOW)
      {
          if (currentMillis - previousMillis >= intervalOff)
          {
              state = HIGH;
              if (pin == 8)
                  first = true;
              if (pin == 6)
              {
                  first2 = true;
              }
              previousMillis += intervalOff;
          }
      }
      else
      {
          if (currentMillis - previousMillis >= intervalOn)
          {
              state = LOW;
              previousMillis += intervalOn;
          }
      }
  }
  
  
  /*
  The switchLeds method uses the digitalWrite method to change the LED's state in order to turn the LED on or off according to their respective state variables. 
  */
  void switchLeds ()
  {
      digitalWrite (redPin, redPinState);
      digitalWrite (greenPin, greenPinState);
      digitalWrite (yellowPin, yellowPinState);
      digitalWrite (redPin2, red2PinState);
      digitalWrite (greenPin2, green2PinState);
      digitalWrite (yellowPin2, yellow2PinState);
      digitalWrite (pedestrianPin, pedestrianPinState);
  }
  
  /*
  The readButton method reads the pedestrian button to see if it is pressed (LOW) or not pressed (HIGH).
  If it is pressed, the buttton state is set to low, the first variables are reset to false and the 
  previousButtonMillis variable is updated to the current time. 
  If the button is pressed and the 5000 milliseconds have already passed (one cycle for the traffic light system)
  the button state is set to HIGH meaning not pressed. 
  */
  void readButton ()
  {
      if (digitalRead (buttonPin) == LOW)
      {
          buttonState = LOW;
          first = false;
          first2 = false;
          previousButtonMillis = currentMillis;
      }
  
  
      if (buttonState == LOW && currentMillis - previousButtonMillis >= 5000)
      {
          buttonState = HIGH;
      }
  }
  
  
  /*
  The ldr method updates the sensor value with the value of the LDR sensor and prints numbers to the serial monitor. 
  If the sensor value if larger than 10 (It does not sense light) , the sensor LED is turned on else it is turned off. 
  */
  void ldr ()
  {
      sensorValue = analogRead (sensorPin);
      Serial.println (sensorValue);
  
      if (sensorValue > 10)
          digitalWrite (sensorLED, HIGH);
      else
          digitalWrite (sensorLED, LOW);
  }
  
  /*
  The servo method moves the servo motor which opens and closes the gates to the parking lot. 
  The val variable stores the value of the sensor and prints it to the serial monitor
  If 20 milliseconds have passed, the ts variable is updated.
  If the sensor does not sense the IR light, the motor's position progressively goes to 0 degrees which causes the gates to open.
  If the position of the motor is 0 degrees, the variable forward is set to false indicating that it has moved 180 dregrees.
  If the sensor does sense the IR light, the motor's position goes progressively to 180 degrees which causes the gates to close.
  If the position of the motor is 180 degrees, the varoable forward is set to true indicating that it has moved 180 degrees.
  */
  void servo ()
  {
      int val = analogRead (senRead);
      Serial.println (val);
  
      if (millis () - ts >= 20)
      {
          ts += 20;
          if (val >= 1005 && forward == true)
          {
              myservo.write (--position);   
              if (position == 0) 
                  forward = false;
          }
          else
              if (val < 1005 && forward == false)
              {
                  myservo.write (++position);   
                  if (position == 180)  
                      forward = true;
              }
      }
  }

