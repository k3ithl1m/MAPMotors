//
//  musclemotor.cpp
//  MAPMuscle
//
//  Created by Keith Lim on 2/15/18.
//  Copyright © 2018 Keith Lim. All rights reserved.
//

#include "MuscleMotor.hpp"
#include "wpt.hpp"
#include <stdint.h>
#include <iostream>


MuscleMotor::MuscleMotor(int16_t maxsignal, int16_t minsignal)
{
    this->openGrip = true;
    this->maxSignal = maxsignal;
    this->minSignal = minsignal;
    this->signalPeaked = false;
    
    
}

void MuscleMotor::sayHello()
{
    wpt* wave = new wpt(this->minSignal);
    std::cout << "Hello This is c++!\n";
    std::cout << std::to_string(this->maxSignal) + " is the max signal\n";
    wave->sayHello();
    
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
            amountOfSeconds ++;
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
        openGrip = !openGrip;
        amountOfSeconds = 0;
    }
    
    return openGrip;
}





