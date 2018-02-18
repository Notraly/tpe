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

LedsGroupsManager::LedsGroupsManager(const byte pinsLedsRB[TPE_NB_LEDRGB_BY_GROUP][2],const byte pinGroups[TPE_NB_GROUP]) {
  for(uint iGroup = 0 ; iGroup < TPE_NB_GROUP; iGroup++){
    LedsGroup group = LedsGroup(pinGroups[iGroup]);
    for(uint iLed = 0 ; iLed < TPE_NB_LEDRGB_BY_GROUP; iLed++){
      LedRGB led = LedRGB(pinsLedsRB[iLed][0], -1, pinsLedsRB[iLed][1]);
      group.addLed(led);
    }
    ledsGroups.push_back(group);
  }

  animation = nullptr;
}

// ------------------------------------------------------------------- Methodes
void LedsGroupsManager::init(){
  for(LedsGroup group : ledsGroups){
    group.init();
    group.initLedsRGB();
  }
}

void LedsGroupsManager::playPause(){
  animationPause = !animationPause;
}

void LedsGroupsManager::loop(){
  if(animation != nullptr){
    long newTime = millis();

    if (animationPause == false) {
      avancement += min((newTime - lastTime)*1./animationDuration,.99);
    }

    if(avancement>=1){
      avancement = animationLoop?0:.99;

    }
    /*
    Serial.print(avancement);
    Serial.print("\t");
    Serial.print(animation->currentRed(avancement, 0, 0));
    Serial.print("\t");
    Serial.print(animation->currentBlue(avancement, 0, 0));
    Serial.print("\t");
    Serial.print(TpeAnimation::currentValue(avancement,*(animation->getAnimLed(0,0)->arrayRed)));
    Serial.println("");
    */
    for(int iG=0;iG<5;iG++){
      for(int iL=0;iL<3;iL++){
        ledsGroups[iG].getLedRGB(iL).setValue(
          animation->currentRed(avancement, iG, iL),
          0,
          animation->currentBlue(avancement, iG, iL)
        );
      }
      ledsGroups[iG].setEnable(true);
      delay(5);
      ledsGroups[iG].setEnable(false);
    }
    lastTime = newTime;
  }
}


void LedsGroupsManager::changeAnimation(TpeAnimation* animation, uint duree){ changeAnimation(animation, duree, true); }
void LedsGroupsManager::changeAnimation(TpeAnimation* animation, uint duree, bool loop){
  changeAnimation(animation, duree, loop, true);
}
void LedsGroupsManager::changeAnimation(TpeAnimation* animation, uint duree, bool loop, bool start){
  animationPause = !start;
  this->animation = animation;
  this->animationDuration = duree;
  this->animationLoop = loop;
  this->avancement = 0;
}

void LedsGroupsManager::accelerate(float acceleration){
  animationDuration /= acceleration;
}

// --------------------------------------------------------- Getteurs/Sertteurs
void LedsGroupsManager::setAnimationLoop(bool loopAnimation){
  animationLoop = loopAnimation;
}
// ------------------------------------------------------------------ Destuctor

LedsGroupsManager::~LedsGroupsManager() {
}

// END PUBLIC
// PROTECTED ======================================================== PROTECTED

// END PUBLIC
