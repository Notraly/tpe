//
//  LedsGroupsManager.cpp
//
//  Created by Egaro555 on 30/01/2018.
//
//

#include "LedsGroupsManager.h"

// PRIVATE ============================================================ PRIVATE
// ------------------------------------------------------------------- methodes

// END PRIVATE
// PUBLIC ============================================================== PUBLIC
// -------------------------------------------------------------- Constuctors

LedsGroupsManager::LedsGroupsManager(const byte pinsLedsRB[TPE_NB_LEDRGB_BY_GROUP][2],const byte pinGroups[TPE_NB_GROUP])  {
  for(uint iGroup = 0 ; iGroup < TPE_NB_GROUP; iGroup++){
    LedsGroup* group = new LedsGroup(pinGroups[iGroup]);
    for(uint iLed = 0 ; iLed < TPE_NB_LEDRGB_BY_GROUP; iLed++){
      LedRGB* led = new LedRGB(pinsLedsRB[iLed][0], -1, pinsLedsRB[iLed][1]);
      group->addLed(led);
    }
    ledsGroups.push_back(group);
  }
  mux = new LedsGroupMuxing(ledsGroups);

  annimation = nullptr;
}

// ------------------------------------------------------------------- Methodes
void LedsGroupsManager::init(){
  for(LedsGroup* group : ledsGroups){
    group->init();
    group->initLedsRGB();
  }
  mux->init();
  lastMuxGroup = mux->currentGroup();
  lastMuxPos = mux->getCurrentPos();
}

void LedsGroupsManager::loop(){
  mux->loop();
  if(annimation != nullptr){
    float avancement = (millis() - annimationStart)*1./annimationDuration;
    if(annimationLoop && avancement>1){
      avancement = 0;
      annimationStart = millis();
    }

    Serial.print(avancement);
    Serial.print("\t");
    Serial.print(annimation->currentRed(avancement, 0, 0));
    Serial.print("\t");
    Serial.print(annimation->currentBlue(avancement, 0, 0));
    Serial.print("\t");
    Serial.println("");

    if( lastMuxPos != mux->getCurrentPos()){
      for(LedRGB* led : *lastMuxGroup->getLedRGBs()) led->setValue(0,0,0);
      lastMuxPos = mux->getCurrentPos();
      lastMuxGroup = mux->currentGroup();
    }

    int iL = 0;
    for(LedRGB* led : *lastMuxGroup->getLedRGBs()){
        led->setValue(
          annimation->currentRed(avancement, lastMuxPos, iL),
          0,
          annimation->currentBlue(avancement, lastMuxPos, iL)
        );
      iL++;
    }
  }
}


void LedsGroupsManager::changeAnnimation(TpeAnnimation* annimation, uint duree){ changeAnnimation(annimation, duree, true); }
void LedsGroupsManager::changeAnnimation(TpeAnnimation* annimation, uint duree, bool loop){
  this->annimation = annimation;
  this->annimationDuration = duree;
  this->annimationLoop = loop;

  this->annimationStart = millis();
}

// --------------------------------------------------------- Getteurs/Sertteurs

// ------------------------------------------------------------------ Destuctor

LedsGroupsManager::~LedsGroupsManager() {
  for(LedsGroup* group : ledsGroups){
    for(uint iLed = 0 ; iLed < 3; iLed++){
      delete group->getLedRGB(iLed);
    }
    delete group;
  }
}

// END PUBLIC
// PROTECTED ======================================================== PROTECTED

// END PUBLIC
