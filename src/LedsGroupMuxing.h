//
//  LedsGroupMuxing.hpp
//
//  Created by Egaro555 on 30/01/2018.
//
//

#ifndef LedsGroupMuxing_h
#define LedsGroupMuxing_h

// ===================================================================== INLUDE

#include <stdio.h>
#include <vector>
#include "./LedsGroup.h"
#include "./Util.h"

// --------------------------------------------------------------------- Struct
// ---------------------------------------------------------------------- const

class LedsGroupMuxing {
private: //============================================================ PRIVATE
  // -------------------------------------------------------------------- const
  // --------------------------------------------------------------- attributes
  vector<LedsGroup*> ledsGroups;
  ushort currentPos;
  ushort dTMin = 10; // Delta milis min avant changement de group
  ulong nextChange = 0; // Temp en milliseconde du prochain changement de group
  bool isInit = false;
  // ----------------------------------------------------------------- methodes
  void changeGroup();
  // END PRIVATE
public: //============================================================== PUBLIC
  // -------------------------------------------------------------- Constuctors
  LedsGroupMuxing(vector<LedsGroup*> ledsGroups);
  // ----------------------------------------------------------------- Methodes
  void init();
  void loop();
  LedsGroup* currentGroup();
  // ------------------------------------------------------- Getteurs/Sertteurs
  void setMinDTime(short millis);
  short getMinDTime()const;
  ushort getCurrentPos();
  // ---------------------------------------------------------------- Destuctor
  ~LedsGroupMuxing();
  // END PUBLIC
protected: //======================================================== PROTECTED

};


#endif /* LedsGroupMuxing_h */
