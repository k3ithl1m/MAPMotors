
#include <Servo.h>
Servo myservo;
const int bicepPin = 6;
const int tricepPin = 7;
const int servoPin = 4;
int pos = 0;
int bicepValue = 0;
int tricepValue = 0;
int servoState = 0;
unsigned long StartTime = 0;
unsigned long runningTime = 0;
int runningValue = 2000;
int currentTime = 0;
int pressedTime;
int releasedTime;
int pressLength_milliSeconds = 0;


void setup() {
  // put your setup code here, to run once:
  myservo.attach(4);
  myservo.writeMicroseconds(servoState);
  pinMode(bicepPin,INPUT);
  pinMode(tricepPin,INPUT);
  Serial.begin(9600);
}

/**
* Start of Muscle Motor class.
*
* Muscle Motor class takes in variables and signals and
* decide on what the output should be. For example
* Takes in a signal and outputs a boolean to signify that
* we should or not move the arm.
*
* ##grip is always open when true and close when false
**/
class MuscleMotor {
private:
  bool openGrip;
  bool currentGrip;
  bool signalPeaked;
  int16_t signalFromSensor;
  int16_t maxSignal;
  int16_t minSignal;
  unsigned long currentCounter;
  unsigned long pastCounter;
  int amountOfSeconds;


public:
  MuscleMotor(int16_t, int16_t);                    //done
  void sayHello();
  void readSignal(int16_t);
  int  getAmountOfSeconds();
  bool checkGripPosition(int16_t, int16_t);

};

/**
* Set the fields to a default value.
**/
MuscleMotor::MuscleMotor(int16_t maxsignal, int16_t minsignal)
{
  this->openGrip = true;
  this->currentGrip = true;
  this->maxSignal = maxsignal;
  this->minSignal = minsignal;
  this->signalPeaked = false;
  this->amountOfSeconds = 0;
}

/**
* @ReadSignal
* Takes in the signal and save it in a field
**/
void MuscleMotor::readSignal(int16_t signal)
{
  this->signalFromSensor = signal;
}

/**
* Outputs the amount of seconds we received the signals
**/
int MuscleMotor::getAmountOfSeconds()
{
  return this->amountOfSeconds;
}

// check to see if the grip should be open or close
// have to make a new function that calculates 2 seconds
bool MuscleMotor::checkGripPosition(int16_t bicepValue, int16_t tricepValue)
{

  if (amountOfSeconds >= 2000) {

    return openGrip;

    amountOfSeconds = 0;
  } else if (bicepValue != HIGH && tricepValue != HIGH) {
    amountOfSeconds = 0;
    return currentGrip;
  } else {
    delay(100);
    amountOfSeconds += 100;
    Serial.print("ms = ");
    Serial.println(amountOfSeconds);
  }

}

//Instantiate the class.
MuscleMotor* mm = new MuscleMotor(0.5, 0);

/** ###HARDWARE CONTROL### **/

/**
* func() openCloseActuator
*
* Open or close the actuator based on a boolean
* @parameter bool open: if gripOpen is true, open the hand
* @parameter int pressLength: We use pressLength to measure if it
*     has been 2 seconds. if val >= 2000, then its been 2 seconds.
**/
void openCloseActuator(bool gripOpen, int pressLength) {
  // if we receive a boolean that says, open is true
  // we move the actuator so that it opens.
  // else we close it.
  if (pressLength >= 2000) {

    if (gripOpen) {
      //writing onto the servo to open it (extend it)

      myservo.writeMicroseconds(0);
      delay(5);


    } else {
      //writing onto the servo to close it (retract it)

      myservo.writeMicroseconds(0);
      delay(5);


    }}
  }

  

  void loop() {
    // put your main code here, to run repeatedly:
    // Rule of thumb for optimization:
    // The code within this box should not be more than 8 lines


    bicepValue = digitalRead(bicepPin);
    tricepValue = digitalRead(tricepPin);
    // this will be used to change gripPosition
    bool grip = mm->checkGripPosition(bicepValue, tricepValue);
    pressLength_milliSeconds = mm->getAmountOfSeconds();

    openCloseActuator(grip, pressLength_milliSeconds);

  }
