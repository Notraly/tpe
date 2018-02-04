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
  digitalWrite(pin, enable ? PIN_ANABLE_VALUE : PIN_DISABLE_VALUE);
}

// Methodes public
void LedsGroup::addLed(LedRGB* newLed){
  leds.push_back(newLed);
}

void LedsGroup::init(){
  pinMode(pinGroup, OUTPUT);
  changePinValue(pinGroup, enable);
}
void LedsGroup::initLedsRGB(){
  for(LedRGB* led : leds){
    led->init();
    led->setEnable(enable);
  }
}
// Setteur Getteur

LedRGB* LedsGroup::getLedRGB(uint id) const{
  auto a = leds.begin();
  for(;id > 0; id--)
    a++;
  return *a;
}
list<LedRGB*>* LedsGroup::getLedRGBs(){ return &leds; }

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
