#include <Wire.h>
#include <Servo.h>
#include <Adafruit_ADS1015.h>

Servo myservo;
int forthPinMotion = 4;
int buttonInput = A0;

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
    usec = 1000 + strokePercentage * ( 2000 - 1000 ) / 100.0 ;
    
    
  }
    myservo.writeMicroseconds( usec );
}

void SetStrokeMM(int strokeReq,int strokeMax)
{
  SetStrokePerc( ((float)strokeReq) / strokeMax );
}


void loop() {
  
  int buttonInt = digitalRead(buttonInput);
  Serial.println(buttonInt);
  if (buttonInt) {
    SetStrokeMM(10,10);
  } else {
    SetStrokeMM(0,10);
  }
}
