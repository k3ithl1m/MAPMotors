//
//  musclemotor.cpp
//  MAPMuscleMotor
//
//  Created by Keith Lim on 2/15/18.
//  Copyright © 2018 Keith Lim. All rights reserved.
//

#include "MuscleMotor.hpp"
#include <stdint.h>
#include <iostream>


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

void MuscleMotor::sayHello()
{
    std::cout << "Hello This is c++!";
}

bool MuscleMotor::getSignalRecorded()
{
    return this->signalRecorded;
}

void MuscleMotor::updateMaxSignal(int16_t signalReceived)
{
//    int16_t tempSignal;
//    // UpdateLEDOn();
//
//    //startCounter
//    uint32_t period = 1000L;
//
//    for ( uint32_t timerStart = millis(); (millis() - timerStart) < period; )
//    {
//
//        tempSignal = this->signalFromSensor;
//
//        if (tempSignal > this->maxSignal)
//        {
//            this->maxSignal = tempSignal;
//
//        } else if(tempSignal < this->minSignal)
//        {
//
//            this->minSignal = tempSignal;
//        }
//
//    }
//
//    //   UpdateLEDOff();
    return;
}

bool MuscleMotor::isMotorStop()
{
    return this->motorStop;
}

bool MuscleMotor::isLowerBound()
{
    int16_t lowerBound = this->minSignal + 500;

    if (this->signalFromSensor > lowerBound) {
        return false;
    }

    return true;
}

bool MuscleMotor::forwardOrReverse()
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
    //light1stMotion();
    return;
}

void MuscleMotor::closeGrip()
{
    this->motorStop = false;
    this->forwardNotReverse = true;
    return;
}

void MuscleMotor::openGrip()
{
    this->motorStop = false;
    this->forwardNotReverse = false;
    return;
}

bool MuscleMotor::didWeCloseGrip()
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
    //setMotor(4000, this->forwardNotReverse);
    //setSMotor(0, this-> forwardNotReverse);
    return;
}

void MuscleMotor::secondGrip()
{
    //setMotor(4000, this->forwardNotReverse);
    //setSMotor(4000, this-> forwardNotReverse);
    return;
}

void MuscleMotor::stopMotor()
{
    //setMotor(0, this->forwardNotReverse);
    //setSMotor(0, this-> forwardNotReverse);
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
    //int runB = digitalRead(runButton);
    //int gripS = digitalRead(gripSignal);

//    if(runB) {
//        if(gripS) {
//            this->firstGrip();
//        } else {
//            this->secondGrip();
//        }
//    }

    return;

}

void MuscleMotor::runMuscleMotor(int16_t emgSignal, int lengthOfWindow)
{

    //int16_t signalRMSWindow[lengthOfWindow];
    //int16_t totalSquare = 0;

    //int16_t signalModerator = ads.readADC_SingleEnded(0) - 13200;

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
    //signalModerator = abs(signalModerator);


    if(
       //    this->isLowerBound()
       runOrNot
       )
    {
        if(this->signalPeaked) {
            this->hasTheSignalPeakedFinish = true;
            this->signalPeaked = false;
            //      delay(1000);
            //Serial.println("stopped");
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
           // SetStrokeMM(10,10);
        }
    }

}
