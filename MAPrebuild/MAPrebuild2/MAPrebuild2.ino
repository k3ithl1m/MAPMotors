
#include <Servo.h>
Servo myservo;
const int buttonPin = 6;
const int servoPin = 4;
int pos = 0;
int buttonValue = 0;
int servoState = 0;
int StartTime = 0;
bool gripPosition = false;
int pressLength_milliSeconds = 0;


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
    while (digitalRead(buttonPin) == HIGH ){ 
 
    delay(100);   
    pressLength_milliSeconds = pressLength_milliSeconds + 100;   
 
   
    Serial.print("ms = ");
    Serial.println(pressLength_milliSeconds);
    if (pressLength_milliSeconds >= 2000) {
      break;
    }
    
  }
   if(gripPosition == false){
      if(pressLength_milliSeconds >= 2000){
      for (pos = 0; pos < 180; pos = pos + 1){
        myservo.write(pos);
        delay(5);
        gripPosition = true;
          }
        }
    }


   else if (gripPosition == true) {
      if(pressLength_milliSeconds >= 2000){
      for (pos = 180; pos > 1; pos = pos - 1) {
        myservo.write(pos);
        delay(5);
        gripPosition = false;
          }
        }
    } 
    while(digitalRead(buttonPin) == HIGH){
      myservo.write(pos);
      delay(50);
      }
    
 pressLength_milliSeconds = 0;
}
