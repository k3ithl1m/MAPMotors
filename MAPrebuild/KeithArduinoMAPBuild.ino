/*
Adafruit Arduino - Lesson 15. Bi-directional Motor
*/
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;

Servo myservo;  // create servo object to control a servo
Servo secServo;
Servo thirdServo;

int enablePin = 10;
int in1Pin = 9;
int in2Pin = 8;
int Sin1Pin = 11;
int Sin2Pin = 12;
int SEnablePin = 13;

//Takes up the pin to either move servo or light led
int firstMotion = 4;
int secondMotion = 5;
int thirdMotion = 6;

//int updatingLED = 2;   //led for when updating signal
int buttonPin = 3;
//int buttonState = 0;

int runButton = 3; //the switch that turns on the motors
int gripSignal = 2; //the switch that makes the decision on what grip to perform

//Degrees used for the servo
int minDegrees = 0;
int maxDegrees = 120;
int rangeSignal = 520 - 140;

int maxPeak, lowPeak;

void setup()
{
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(SEnablePin, OUTPUT);
  pinMode(Sin1Pin, OUTPUT);
  pinMode(Sin2Pin, OUTPUT);
//  pinMode(firstMotion, OUTPUT);
//  pinMode(secondMotion, OUTPUT);
//  pinMode(thirdMotion, OUTPUT);

  //attaching the servo to pins
  myservo.attach(firstMotion);  // 4th pin
  secServo.attach(secondMotion); //5 pin
  thirdServo.attach(thirdMotion); //6 pin


  //pinMode(updatingLED, OUTPUT);
//  pinMode(switchPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT);

  pinMode(gripSignal, INPUT);
  pinMode(runButton, INPUT);

  Serial.begin(9600);

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input
  // range!
  // Setting these values incorrectly may destroy your ADC!
  //
  //                               ADS1015  ADS1115
  //
  //                               -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);
  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);
  // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);
  // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);
  // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);
  // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);
  // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  ads.begin();
}

// INPUTS //


// OUTPUTS //

void light1stMotion() {
  digitalWrite(firstMotion, HIGH);
  digitalWrite(secondMotion, LOW);
  digitalWrite(thirdMotion, LOW);
}

void light2ndMotion() {
  digitalWrite(firstMotion, LOW);
  digitalWrite(secondMotion, HIGH);
  digitalWrite(thirdMotion, LOW);
}

void light3rdMotion() {
  digitalWrite(firstMotion, LOW);
  digitalWrite(secondMotion, LOW);
  digitalWrite(thirdMotion, HIGH);
}

void setMotor(int speed, boolean reverse)
{
  //code for lego motors
//  analogWrite(enablePin, speed);
//  digitalWrite(in1Pin, !reverse);
//  digitalWrite(in2Pin, reverse);

  Serial.println("motor should go");
  //code for servo motors
  int val;
  if (reverse) {
    val = map(0, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  } else {
    val = map(180, 0, 1023, 0, 180);
  }
//  myservo.write(val);
//  secServo.write(val);
}

void setSMotor(int speed, boolean reverse)
{
  //code for lego motors
//  analogWrite(SEnablePin, speed);
//  digitalWrite(Sin1Pin, !reverse);
//  digitalWrite(Sin2Pin, reverse);

  //code for servo motors
  int val;
  if (reverse) {
    val = map(0, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  } else {
    val = map(180, 0, 1023, 0, 180);
  }
  secServo.write(val);
}



// void UpdateLEDOn() {
//   digitalWrite(updatingLED, HIGH);
// }
//
// void UpdateLEDOff() {
//   digitalWrite(updatingLED, LOW);
// }


//Calculate signal for servo feedback
float calculateSignal(int feedback)
{
  float newControlled = feedback - 139;
  return (newControlled/rangeSignal * maxDegrees);
}

double performRMSCalculation(int16_t arr[])
{
  double signalRMS = RMS(arr, ((sizeof arr) / (sizeof *arr)));
  return signalRMS;
}

/**
 * RMS =  root mean squared
 * square all the values first, the divide it by the length
 * to get the mean, then root the whole thing.
 */
double RMS(int16_t arr[], int length)
{
  double add = 0;
  for (int i = 0; i < length; i++)
  {
    add += arr[i] * arr[i];
  }

  return sqrt(add/double(length));
}


//find percentage for linear actuator  utopiamechanicus.com/article/linear-actuator-arduino
void SetStrokePerc(float strokePercentage)
{
  int usec;
  if ( strokePercentage >= 1.0 && strokePercentage <= 99.0 )
  {
    usec = 1000 + strokePercentage * ( 2000 - 1000 ) / 100.0 ;
    
    
  }
//    thirdServo.writeMicroseconds( usec );
    myservo.writeMicroseconds( usec );
}
void SetStrokeMM(int strokeReq,int strokeMax)
{
  SetStrokePerc( ((float)strokeReq) / strokeMax );
}


// OUTPUTS //


class MuscleMotor {
private:
  boolean forwardNotReverse;
  boolean motorStop;
  boolean signalRecorded;
  boolean hasTheSignalPeakedFinish;
  boolean signalPeaked;
  boolean isTheGripInOpenPosition;
  int16_t signalFromSensor;
  int16_t signalModerator;
  int16_t maxSignal;
  int16_t minSignal;
  int16_t temp;
  int speed;


public:
  MuscleMotor();                    //done
  boolean getSignalRecorded();
  boolean isMotorStop();            //done
  boolean forwardOrReverse();       //done
  boolean didWeCloseGrip();         //done
  boolean isLowerBound();           //done
  int16_t getSignalFromSensor();    //done
  void saveTempSignal();
  void updateMaxSignal(int16_t signalReceived);
  void updateSignalFromSensor(int16_t signalReceived); //done
  void gripAtRest();                //done
  void closeGrip();                 //done
  void openGrip();                  //done
  void toggleMotor();               //done
  void toggleDirection();           //done
  void runMuscleMotor(int16_t emgSignal, int lengthOfWindow);
  void firstGrip();
  void secondGrip();
  void stopMotor();
  void gripDecisionCloseOrOpen();
  void whichGripShouldWeRun();

};


MuscleMotor::MuscleMotor()
{
  this->forwardNotReverse = true;
  this->signalRecorded = false;
  this->motorStop = true;
  this->maxSignal = 7000;
  this->minSignal = 1000;
  this->hasTheSignalPeakedFinish = true;
  this->signalPeaked = false;
  this->isTheGripInOpenPosition = true;
}

boolean MuscleMotor::getSignalRecorded()
{
  return this->signalRecorded;
}

void MuscleMotor::updateMaxSignal(int16_t signalReceived)
{
  int16_t tempSignal;
  // UpdateLEDOn();

  //startCounter
  uint32_t period = 1000L;

  for ( uint32_t timerStart = millis(); (millis() - timerStart) < period; )
  {

    tempSignal = this->signalFromSensor;

    if (tempSignal > this->maxSignal)
    {
      this->maxSignal = tempSignal;

    } else if(tempSignal < this->minSignal)
    {

      this->minSignal = tempSignal;
    }

  }

  //   UpdateLEDOff();
  return;
}

boolean MuscleMotor::isMotorStop()
{
  return this->motorStop;
}

boolean MuscleMotor::isLowerBound()
{
  int16_t lowerBound = this->minSignal + 500;

  if (this->signalFromSensor > lowerBound) {
    return false;
  }

  return true;
}

boolean MuscleMotor::forwardOrReverse()
{
  return this->forwardNotReverse;
}

void MuscleMotor::toggleMotor()
{
  this->motorStop = !this->motorStop;
  return;
}

void MuscleMotor::toggleDirection()
{
  this->forwardNotReverse = !this->forwardNotReverse;
  return;
}

void MuscleMotor::gripAtRest()
{
  this->motorStop = true;
  light1stMotion();
  return;
}

void MuscleMotor::closeGrip()
{
  this->motorStop = false;
  this->forwardNotReverse = true;
  light2ndMotion();
  Serial.println("CloseGrip");
  return;
}

void MuscleMotor::openGrip()
{
  this->motorStop = false;
  this->forwardNotReverse = false;
  light3rdMotion();
  Serial.println("OpenGrip");
  return;
}

boolean MuscleMotor::didWeCloseGrip()
{
  if (this->forwardNotReverse)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void MuscleMotor::updateSignalFromSensor(int16_t signalReceived)
{
  this->signalFromSensor = signalReceived;
  return;
}

int16_t MuscleMotor::getSignalFromSensor()
{
  return this->signalFromSensor;
}

void MuscleMotor::firstGrip()
{
  setMotor(4000, this->forwardNotReverse);
  setSMotor(0, this-> forwardNotReverse);
  return;
}

void MuscleMotor::secondGrip()
{
  setMotor(4000, this->forwardNotReverse);
  setSMotor(4000, this-> forwardNotReverse);
  return;
}

void MuscleMotor::stopMotor()
{
  setMotor(0, this->forwardNotReverse);
  setSMotor(0, this-> forwardNotReverse);
  return;
}

void MuscleMotor::gripDecisionCloseOrOpen()
{
  this->signalPeaked = true;

  if (this->hasTheSignalPeakedFinish) {
    if (!this->didWeCloseGrip())
    {
      this->closeGrip();
    }
    else
    {
      this->openGrip();
    }
  }
  this->hasTheSignalPeakedFinish = false;

  return;
}

void MuscleMotor::whichGripShouldWeRun()
{
    //Integration of New Code
  int runB = digitalRead(runButton);
  int gripS = digitalRead(gripSignal);

  if(runB) {
    if(gripS) {
      this->firstGrip();
    } else {
      this->secondGrip();
    }
  }

  return;

}

void MuscleMotor::runMuscleMotor(int16_t emgSignal, int lengthOfWindow)
{

  int16_t signalRMSWindow[lengthOfWindow];
  int16_t totalSquare = 0;
   int16_t signalModerator = ads.readADC_SingleEnded(0) - 13200;
//  for (int i = 0; i < lengthOfWindow; i++)
//  {
////    signalRMSWindow[i] = signalModerator;
//    signalModerator = ads.readADC_SingleEnded(0)-13200;
//    int16_t x = signalModerator * signalModerator;
//    totalSquare = (x) + totalSquare;
//    
//    Serial.println(signalModerator);
//  }

//  totalSquare = totalSquare / lengthOfWindow;
////  Serial.println(totalSquare);
//  totalSquare = sqrt(totalSquare);
//  Serial.println(totalSquare);
//  Serial.println(signalModerator);
//  Serial.println(performRMSCalculation(signalRMSWindow));

  bool runOrNot = false;
  int16_t up = 500; 
  int16_t down = -2500;

//
  if (signalModerator > up || signalModerator < down) {
    runOrNot = true;
//    Serial.println(1);
  } else {
    runOrNot = false;
//    Serial.println(0);
  }
//
  signalModerator = abs(signalModerator);
  Serial.println(signalModerator);


  if(
//    this->isLowerBound()
    runOrNot
  )
  {
    if(this->signalPeaked) {
      this->hasTheSignalPeakedFinish = true;
      this->signalPeaked = false;
//      delay(1000);
      Serial.println("stopped");
      this->stopMotor();
    }
    this->gripAtRest();
  }
  else if (
//    !this->isLowerBound()
     !runOrNot
    )
  {
//    this->gripDecisionCloseOrOpen();
//
//    this->whichGripShouldWeRun();

//    Serial.println("we are here");

    for (int j = 0; j < 200; j++) {
    SetStrokeMM(10,10);
    }
  }

}

MuscleMotor* newMuscleMotor = new MuscleMotor;

void loop()
{
  int16_t adc0 = ads.readADC_SingleEnded(0);
  newMuscleMotor->updateSignalFromSensor(adc0);
  newMuscleMotor->runMuscleMotor(adc0, 10);

}
