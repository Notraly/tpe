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
#include "LedsGroupMuxing.h"
#include "TpeAnnimation.h"
#include "TpeConfig.h"

// --------------------------------------------------------------------- Struct
// ---------------------------------------------------------------------- const

class LedsGroupsManager {
private: //============================================================ PRIVATE
  // -------------------------------------------------------------------- const
  // --------------------------------------------------------------- attributes
  list<LedsGroup*> ledsGroups;
  LedsGroupMuxing* mux;
  TpeAnnimation* annimation;
  bool annimationLoop;
  uint annimationDuration;
  ulong annimationStart;
  // ----------------------------------------------------------------- methodes
  // END PRIVATE
public: //============================================================== PUBLIC
  // -------------------------------------------------------------- Constuctors
  LedsGroupsManager(const byte pinsLedsRGB[TPE_NB_LEDRGB_BY_GROUP][2],const byte pinGroups[TPE_NB_GROUP]);
  // ----------------------------------------------------------------- Methodes
  void init();
  void loop();

  void changeAnnimation(TpeAnnimation* annimation, uint Durration);
  void changeAnnimation(TpeAnnimation* annimation, uint Durration, bool loop);

  // ------------------------------------------------------- Getteurs/Sertteurs
  LedsGroup* getGroup(uint index);
  LedsGroup* getGroups();
  // ---------------------------------------------------------------- Destuctor
  ~LedsGroupsManager();
  // END PUBLIC
protected: //======================================================== PROTECTED

};


#endif /* LedsGroupsManager_h */
