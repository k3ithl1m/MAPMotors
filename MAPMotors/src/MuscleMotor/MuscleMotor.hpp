//
//  musclemotor.hpp
//  MAPMuscleMotor
//
//  Created by Keith Lim on 2/15/18.
//  Copyright © 2018 Keith Lim. All rights reserved.
//

#ifndef MuscleMotor_hpp
#define MuscleMotor_hpp

#include <stdio.h>


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

#endif /* musclemotor_hpp */

