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
#include <vector>
#include "Util.h"
#include "LedRGB.h"

using namespace std;

class LedsGroup {
private:
  const byte pinGroup;
  vector<LedRGB*> leds;
  bool enable;
  // Methode
  void changePinValue(byte pin, bool enable )const;
public:
  static const int PIN_DISABLE_VALUE = LOW;
  static const int PIN_ANABLE_VALUE = HIGH;

  LedsGroup(const byte pinGroupe);
  ~LedsGroup();
  void addLed(LedRGB* newLed);
  void init();
  void initLedsRGB();
  // Setteur Getteur
  LedRGB* getLedRGB(const uint id) const;
  vector<LedRGB*>* getLedRGBs();
  bool isEnable()const;
  void setEnable(const bool &enable);

protected:
};


#endif /* LedsGroup_hpp */
