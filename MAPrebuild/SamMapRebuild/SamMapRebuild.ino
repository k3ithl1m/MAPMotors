
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
  Serial.print(buttonValue);
  Serial.print("    ");
  StartTime = millis();
  delay(200);
  Serial.println(StartTime);
  
  if(servoState == 0){
    if(buttonValue == HIGH){
      servoState = 1;
      for (pos = 0; pos < 180; pos = pos + 1){
      myservo.write(pos); 
      delay(5);
            }
    }
    }

  else if (servoState == 1) {
    if (buttonValue == HIGH){
    servoState = 0;
      for (pos = 180; pos > 1; pos = pos - 1) {
      myservo.write(pos);
      delay(5);
            }
      }
    }

}  



