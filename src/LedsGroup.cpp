//
//  LedsGroup.cpp
//
//  Created by Notraly on 20/01/2018.
//
//

#include "LedsGroup.h"
// :pinGroup(pinGroupe) = affecte les attributs de l'objet avec les valeurs des paramètres
LedsGroup::LedsGroup(const byte pinGroupe):pinGroup(pinGroupe)  {
}

LedsGroup::~LedsGroup() {

}
// Methodes pivate

void LedsGroup::changePinValue(byte pin, bool enable) const{
  digitalWrite(pin, enable ? LOW : HIGH);
}

// Methodes public
void LedsGroup::addLed(LedRGB* newLed){
  leds.push_back(newLed);
}

// Setteur Getteur

LedRGB* LedsGroup::getLedRGB(unsigned int id) const{
  auto a = leds.begin();
  for(;id > 0; id--)
    a++;
  return *a;
}

bool LedsGroup::isEnable()const{
  return enable;
}
void LedsGroup::setEnable(const bool &enable){
  this->enable = enable;
  if(!enable)changePinValue(pinGroup,false);

  for(LedRGB* led : leds){
    led->setEnable(enable);
  }

  if(enable)changePinValue(pinGroup,true);
}
