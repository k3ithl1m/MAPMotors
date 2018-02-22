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
    bool forwardNotReverse;
    bool motorStop;
    bool signalRecorded;
    bool hasTheSignalPeakedFinish;
    bool signalPeaked;
    bool isTheGripInOpenPosition;
    int16_t signalFromSensor;
    int16_t signalModerator;
    int16_t maxSignal;
    int16_t minSignal;
    int16_t temp;
    int speed;
    
    
public:
    MuscleMotor();                    //done
    bool getSignalRecorded();
    bool isMotorStop();            //done
    bool forwardOrReverse();       //done
    bool didWeCloseGrip();         //done
    bool isLowerBound();           //done
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
    void sayHello();
    
};

#endif /* musclemotor_hpp */

