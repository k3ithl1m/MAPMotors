#include <Wire.h>
#include <Servo.h>
<<<<<<< HEAD
#include <Adafruit_ADS1015.h> 
=======
#include <Adafruit_ADS1015.h>
>>>>>>> e01cb1d03df7265f77c839fd9c8ffadc6e8cac78

Servo myservo;
int forthPinMotion = 4;
int buttonInput = A0;
<<<<<<< HEAD
int buttonPin = 6;
int pos = 0;
=======
>>>>>>> e01cb1d03df7265f77c839fd9c8ffadc6e8cac78

void setup() {
  pinMode(buttonInput, INPUT);
  myservo.attach(forthPinMotion);
  Serial.begin(9600);
}

void SetStrokePerc(float strokePercentage)
{
  int usec;
  if ( strokePercentage >= 1.0 && strokePercentage <= 99.0 )
  {
<<<<<<< HEAD
   int usec = 1000 + strokePercentage * ( 2000 - 1000 ) / 100.0 ;
=======
    usec = 1000 + strokePercentage * ( 2000 - 1000 ) / 100.0 ;
>>>>>>> e01cb1d03df7265f77c839fd9c8ffadc6e8cac78
    
    
  }
    myservo.writeMicroseconds( usec );
}

void SetStrokeMM(int strokeReq,int strokeMax)
{
  SetStrokePerc( ((float)strokeReq) / strokeMax );
}


void loop() {
<<<<<<< HEAD
  myservo.writeMicroseconds( usec );
=======
  
  int buttonInt = digitalRead(buttonInput);
  Serial.println(buttonInt);
  if (buttonInt) {
    SetStrokeMM(10,10);
  } else {
    SetStrokeMM(0,10);
  }
>>>>>>> e01cb1d03df7265f77c839fd9c8ffadc6e8cac78
}
