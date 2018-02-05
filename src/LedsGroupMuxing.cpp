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
  ledsGroups[currentPos] -> setEnable(false);
  if(++currentPos == ledsGroups.size())currentPos = 0;
  ledsGroups[currentPos] -> setEnable(true);
  nextChange = millis() + dTMin;
}

// END PRIVATE
// PUBLIC ============================================================== PUBLIC
// -------------------------------------------------------------- Constuctors

LedsGroupMuxing::LedsGroupMuxing(vector<LedsGroup*> ledsGroups){
  this->ledsGroups = ledsGroups;
  currentPos = 0;
}

// ------------------------------------------------------------------- Methodes
void LedsGroupMuxing::init(){
    isInit = true;
}

void LedsGroupMuxing::loop(){
  if(isInit){
    if(millis() >= nextChange)changeGroup();
  }
}

LedsGroup* LedsGroupMuxing::currentGroup(){
  return ledsGroups[currentPos];
}
ushort LedsGroupMuxing::getCurrentPos(){
  return currentPos;
}

// --------------------------------------------------------- Getteurs/Sertteurs

// ------------------------------------------------------------------ Destuctor

LedsGroupMuxing::~LedsGroupMuxing() {

}

// END PUBLIC
// PROTECTED ======================================================== PROTECTED

// END PUBLIC
