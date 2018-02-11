//
//  LedsGroupsManager.hpp
//
//  Created by Egaro555 on 30/01/2018.
//
//

#ifndef LedsGroupsManager_h
#define LedsGroupsManager_h

// ===================================================================== INLUDE

#include <stdio.h>
#include <arduino.h>
#include "Util.h"
#include "LedsGroup.h"
#include "TpeAnimation.h"
#include "TpeConfig.h"

// --------------------------------------------------------------------- Struct
// ---------------------------------------------------------------------- const

class LedsGroupsManager {
private: //============================================================ PRIVATE
  // -------------------------------------------------------------------- const
  // --------------------------------------------------------------- attributes
  vector<LedsGroup> ledsGroups;
  TpeAnimation* animation;
  bool animationLoop;
  bool animationPause;
  uint animationDuration;
  ulong lastTime;
  float avancement;
  // ----------------------------------------------------------------- methodes
  // END PRIVATE
public: //============================================================== PUBLIC
  // -------------------------------------------------------------- Constuctors
  LedsGroupsManager(const byte pinsLedsRGB[TPE_NB_LEDRGB_BY_GROUP][2],const byte pinGroups[TPE_NB_GROUP]);
  // ----------------------------------------------------------------- Methodes
  void init();
  void loop();

  void changeAnimation(TpeAnimation* animation, uint Duration);
  void changeAnimation(TpeAnimation* animation, uint Duration, bool loop);
  void changeAnimation(TpeAnimation* animation, uint Duration, bool loop, bool start);
  void playPause();
  void accelerate(float acceleration);
  // ------------------------------------------------------- Getteurs/Sertteurs
  LedsGroup* getGroup(uint index);
  LedsGroup* getGroups();
  void setAnimationLoop(bool loopAnimation);
  // ---------------------------------------------------------------- Destuctor
  ~LedsGroupsManager();
  // END PUBLIC
protected: //======================================================== PROTECTED

};


#endif /* LedsGroupsManager_h */
