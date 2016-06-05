#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int position = 0 ;    // state variable
boolean forward = false ;   // state variable
long ts = millis () ;   // time accounting.
int counter=0;

  int pd = 13; 
  int led = 2; 
  int senRead = 0; 
int minNum=0;
  
  void setup()    
 {  
  myservo.attach(0); 
 // myservo.write(0);   
  pinMode(pd,INPUT);  
  pinMode(led,OUTPUT);  
  digitalWrite(pd,HIGH);       //supply 5 volts to photodiode  
  //Serial.begin(9600);  
 } 
 
 void loop()  
 {  
  int val=analogRead(senRead);   
  Serial.println(val);
  if (counter==75)
  minNum=analogRead(senRead);
  Serial.println(1000+minNum);
  if (millis() - ts >= 20)
  {
    ts+=20;
  if(val > minNum )
  {  
   digitalWrite(led,HIGH);
      myservo.write (-- position) ;  // progress the servo
      if (position == 0)  // test for reverse
        forward = false ;
  }  
  else
  {  
   digitalWrite(led,LOW);  
      myservo.write (++ position) ;  // progress the servo
      if (position == 180)  // test for reverse
        forward = true ;
    }
 }  
 counter++;
 }
