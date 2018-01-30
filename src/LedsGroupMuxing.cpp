//
//  LedsGroupMuxing.cpp
//
//  Created by Egaro555 on 30/01/2018.
//
//

#include "./LedsGroupMuxing.h"
#include <arduino.h>

// PRIVATE ============================================================ PRIVATE
// ------------------------------------------------------------------- methodes
void LedsGroupMuxing::changeGroup(){
  iterator->setEnable(false);
  if(++iterator == ledsGroups.end())iterator = ledsGroups.begin();
  iterator->setEnable(true);
  nextChange = millis() + dTMin;
}
// END PRIVATE
// PUBLIC ============================================================== PUBLIC
// -------------------------------------------------------------- Constuctors

LedsGroupMuxing::LedsGroupMuxing(list<LedsGroup> ledsGroups){
  this->ledsGroups = ledsGroups;
  iterator = this->ledsGroups.begin();
}

// ------------------------------------------------------------------- Methodes

void LedsGroupMuxing::loop(){
    if(millis() >= nextChange)changeGroup();
}

// --------------------------------------------------------- Getteurs/Sertteurs

// ------------------------------------------------------------------ Destuctor

LedsGroupMuxing::~LedsGroupMuxing() {

}

// END PUBLIC
// PROTECTED ======================================================== PROTECTED

// END PUBLIC
