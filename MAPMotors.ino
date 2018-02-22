/*
  MAPMotors_h - Class for MAP prosthetics.
  Created by Keith Lim, November 2, 2017.
  Released into the public domain.
*/
#ifndef MAPMotors_h
#define MAPMotors_h
#include <Wire.h>
#include <Servo.h>

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int feedbackPin = 1;
int minDegrees = 0;
int maxDegrees = 120;

int rangeSignal = 520 - 140;

class MAPMotors
{
  public:
    MAPMotors();
    void moveMotors();

  private:
    float calculateSignal(int feedback);
    Servo MAPServo;

}

MAPMotors::MAPMotors(int baudRateForDisplay, int servoToPin) 
{
  Serial.begin(baudRateForDisplay);
  this->MAPServo.attach(servoToPin);
}

float MAPMotors::calculateSignal(int feedback) {
  float newControlled = feedback - 139;
  float calculatedSignal = (newControlled/rangeSignal * maxDegrees);
  Serial.println(calculatedSignal);
  return calculatedSignal;
}

void MAPMotors::writeToServo(int value)
{
  val = map(value, 0, 1023, 0, 180);
  this->MAPServo.write(val);
  
}

#endif
