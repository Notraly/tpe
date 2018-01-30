//
//  LedsGroup.hpp
//
//  Created by Notraly on 20/01/2018.
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
  const byte pinGroup;
  list<LedRGB*> leds;
  bool enable;
  // Methode
  void changePinValue(byte pin, bool enable )const;
public:
    LedsGroup(const byte pinGroupe);
    ~LedsGroup();
    void addLed(LedRGB* newLed);
    // Setteur Getteur
    LedRGB* getLedRGB(const unsigned int id) const;
    bool isEnable()const;
    void setEnable(const bool &enable);

protected:
};


#endif /* LedsGroup_hpp */
