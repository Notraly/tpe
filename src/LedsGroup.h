//
//  LedsGroup.hpp
//
//  Created by <author> on 20/01/2018.
//
//

#ifndef LedsGroup_hpp
#define LedsGroup_hpp


#include <stdio.h>

#include <arduino.h>
#include "LedRGB.h"
#include <list>

using namespace std;

class LedsGroup {
private:
  byte pinGroup;
  list<LedRGB> leds;
public:
    LedsGroup(byte pinGroupe);
    ~LedsGroup();
    void addLed(LedRGB newLed);
protected:

};


#endif /* LedsGroup_hpp */
