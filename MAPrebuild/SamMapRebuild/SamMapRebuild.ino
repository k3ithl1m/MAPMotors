
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

class MuscleMotor {
private:
    bool openGrip;
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
    bool checkGripPosition(int16_t, unsigned long);

};

MuscleMotor::MuscleMotor(int16_t maxsignal, int16_t minsignal)
{
    this->openGrip = true;
    this->maxSignal = maxsignal;
    this->minSignal = minsignal;
    this->signalPeaked = false;
    this->amountOfSeconds = 0;
}


void MuscleMotor::sayHello()
{

}

void MuscleMotor::readSignal(int16_t signal)
{
    this->signalFromSensor = signal;
}

// check to see if the grip should be open or close
bool MuscleMotor::checkGripPosition(int16_t signal, unsigned long millis)
{

    currentCounter = millis;
    if (signal > maxSignal)
    {

        if (currentCounter - pastCounter >= 1000)
        {

    Serial.println("I'm here");
            amountOfSeconds ++;

    Serial.print("this is the amount of sec");
    Serial.println(amountOfSeconds);
            pastCounter = currentCounter;
        }
    } else {
        amountOfSeconds = 0;
    }

    // If the signal is more than max for 3 seconds,
    // change the grip from open to close or close
    // to open.
    if (amountOfSeconds == 3)
    {

    Serial.println("Changing grip");
        openGrip = !openGrip;
        amountOfSeconds = 0;
    }

    return openGrip;
}

MuscleMotor* mm = new MuscleMotor(0.5, 0);

void loop() {
  // put your main code here, to run repeatedly:
  buttonValue = digitalRead(buttonPin);
  StartTime = millis();

  if(gripPosition == false){
    if(buttonValue == HIGH){
      gripPosition = mm->checkGripPosition(buttonValue, StartTime);
      for (pos = 0; pos < 180; pos = pos + 1){
        myservo.write(pos);
        delay(5);
        }
      }
    }

  else if (gripPosition == true) {
    if (buttonValue == HIGH){

      gripPosition = mm->checkGripPosition(buttonValue, StartTime);
      for (pos = 180; pos > 1; pos = pos - 1) {
        myservo.write(pos);
        delay(5);
        }
      }
    }

}
