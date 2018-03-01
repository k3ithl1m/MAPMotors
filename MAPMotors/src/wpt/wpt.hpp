//
//  wpt.hpp
//  MAPMotors
//
//  Created by Keith Lim on 2/22/18.
//  Copyright © 2018 MAP. All rights reserved.
//

#ifndef wpt_hpp
#define wpt_hpp

#include <stdio.h>

class wpt {
private:
    int16_t signal;
    
public:
    wpt(int16_t);
    void sayHello();
};

#endif /* wpt_hpp */
