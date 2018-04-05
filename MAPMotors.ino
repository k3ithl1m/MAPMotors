/**
* @author Keith Lim and Sam Gullinello
* The Main file for working the MAP
* Consist of the latest working code
**/
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
int pressLength = 0;
bool gripOpen = false;


void setup() {
  // put your setup code here, to run once:
  myservo.attach(4);
  myservo.write(servoState);
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

  //A hack to allow the actuator to work. We've to change
  // the amount of seconds to be more than the time for
  // the grip to change. Once it is higher than the time
  // for the grip to change (2000 or 2 seconds). We change
  // the time press back to 0;
  if (amountOfSeconds >= 2100) {
    amountOfSeconds = 0;
  }

  //If the muscle is squeezed for 2 seconds, Switch the
  //grip, save the grip to the currentGrip and then
  // return the openGrip.
  if (amountOfSeconds >= 2000) {

    openGrip = !openGrip;
    currentGrip = openGrip;
    if (currentGrip) Serial.println("Changing bool to open");
    else Serial.println("Changing bool to close");
    amountOfSeconds+=100;
    return openGrip;

    //if the value of Bicep and tripcep is not high (not squeezed)
    // return the currentGrip Position.
  } else if (bicepValue != HIGH && tricepValue != HIGH) {
    amountOfSeconds = 0;
    return currentGrip;

    //if the muscles is squeezed for less than 2 seconds,
    //delay the system for 1 millisecond, then add 1 millisecond
    // to the total amount of seconds.
  } else {
    delay(100);
    amountOfSeconds += 100;
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
  if (pressLength >= 2100) {

    Serial.println(gripOpen);
    if (gripOpen) {


      Serial.println("open");
      //writing onto the servo to open it (extend it)
      for (pos = 0; pos < 180; pos = pos + 1){
        myservo.write(pos);
        delay(5);
      }

    } else {
      Serial.println("close");
      //writing onto the servo to close it (retract it)
      for (pos = 180; pos > 1; pos = pos - 1) {
        myservo.write(pos);
        delay(5);
      }

    }
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  // Rule of thumb for optimization:
  // The code within this box should not be more than 8 lines


  bicepValue = digitalRead(bicepPin);
  tricepValue = digitalRead(tricepPin);
  // this will be used to change gripPosition
  gripOpen = mm->checkGripPosition(bicepValue, tricepValue);
  pressLength = mm->getAmountOfSeconds();
  openCloseActuator(gripOpen, pressLength);


}
