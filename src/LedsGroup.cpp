//
//  LedsGroup.cpp
//
//  Created by <author> on 20/01/2018.
//
//

#include "LedsGroup.h"
// :pinGroup(pinGroupe) = affecte les attributs de l'objet avec les valeurs des paramètres
LedsGroup::LedsGroup(byte pinGroupe):pinGroup(pinGroupe)  {
}

LedsGroup::~LedsGroup() {

}

void LedsGroup::addLed(LedRGB newLed){
  leds.push_back(newLed);
}
