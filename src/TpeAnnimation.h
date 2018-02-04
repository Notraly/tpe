//
//  TpeAnnimation.hpp
//
//  Created by Egaro555 on 03/02/2018.
//
//

#ifndef TpeAnnimation_h
#define TpeAnnimation_h

// ===================================================================== INLUDE

#include <stdio.h>
#include <list>
#include <Arduino.h>
#include "Util.h"
#include "TpeConfig.h"

using namespace std;

// --------------------------------------------------------------------- Struct
struct AnnimStep{
  float setpTime; // Betwin 0 and 1
  byte value; // stepValue;
};
struct AnnimLed{
  list<AnnimStep> stepsRed;
  list<AnnimStep> stepsBlue;
};
struct AnnimGroup{
  AnnimLed led[TPE_NB_LEDRGB_BY_GROUP];
};
struct Annim{
  AnnimGroup group[TPE_NB_GROUP];
};

// ---------------------------------------------------------------------- const

class TpeAnnimation {
private: //============================================================ PRIVATE
  // -------------------------------------------------------------------- const
  // --------------------------------------------------------------- attributes
  Annim data;
  // ----------------------------------------------------------------- methodes
  // END PRIVATE
public: //============================================================== PUBLIC
  // -------------------------------------------------------------- Constuctors
  TpeAnnimation();
  TpeAnnimation(Annim data);
  // ----------------------------------------------------------------- Methodes
  float currentRed(float avancement, uint group, uint led);
  float currentBlue(float avancement, uint group, uint led);
  float currentRed(float avancement, uint led);
  float currentBlue(float avancement, uint led);
  static float currentValue(float avancement, const list<AnnimStep>* steps);
  // ------------------------------------------------------- Getteurs/Sertteurs
  AnnimGroup* getAnnimGroup(uint group);
  AnnimLed* getAnnimLed(uint group, uint led);
  AnnimLed* getAnnimLed(uint led);
  // ---------------------------------------------------------------- Destuctor
  ~TpeAnnimation();
  // END PUBLIC
protected: //======================================================== PROTECTED

};


#endif /* TpeAnnimation_h */
