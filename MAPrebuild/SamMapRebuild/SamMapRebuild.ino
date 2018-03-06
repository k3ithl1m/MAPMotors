#include <Servo.h>
Servo myservo;
const int buttonPin = 6;
const int servoPin = 4;
int pos = 0;
int buttonValue = 0;
int servoState = 0;
unsigned long StartTime = 0;
unsigned long runningTime = 0;
int runningValue = 2000;
int currentTime = 0;
int pressedTime;
int releasedTime;
bool gripPosition = false;


void setup() {
  // put your setup code here, to run once:
myservo.attach(4);
myservo.write(servoState);
pinMode(buttonPin,INPUT);
Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  buttonValue = digitalRead(buttonPin);
  StartTime = millis();

  if(gripPosition == false){
    if(buttonValue == HIGH){
           pressedTime = millis();
      if(pressedTime - StartTime >2000){
      for (pos = 0; pos < 180; pos = pos + 1){
        myservo.write(pos);
        delay(5);
        gripPosition == true;
          }
        }
      }
    }

  else if (gripPosition == true) {
    if (buttonValue == HIGH){
           pressedTime = millis();
      if(pressedTime - StartTime > 2000){
      for (pos = 180; pos > 1; pos = pos - 1) {
        myservo.write(pos);
        delay(5);
        gripPosition == false;
          }
        }
      }
    }

}

