//
//  wpt.cpp
//  MAPMotors
//
//  Created by Keith Lim on 2/22/18.
//  Copyright © 2018 MAP. All rights reserved.
//

#include "wpt.hpp"
#include <stdint.h>
#include <iostream>

wpt::wpt(int16_t signal)
{
    this->signal = signal;
}

void wpt::sayHello()
{
    std::cout<< std::to_string(this->signal) + "is the min signal \n Calling from wpt\n";
}
