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
#include <vector>
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
  vector<AnnimStep>* stepsRed;
  vector<AnnimStep>* stepsBlue;
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
  static void copyBack(uint length, uint startFrom, vector<AnnimStep> &from, vector<AnnimStep> &to, float offest);
  static vector<AnnimStep>* oneStep(AnnimStep &step);
  // END PRIVATE
public: //============================================================== PUBLIC
  // -------------------------------------------------------------- Constuctors
  TpeAnnimation();
  TpeAnnimation(Annim data);
  // ----------------------------------------------------------------- Methodes
  byte currentRed(float avancement, uint group, uint led);
  byte currentBlue(float avancement, uint group, uint led);
  byte currentRed(float avancement, uint led);
  byte currentBlue(float avancement, uint led);
  static byte currentValue(float avancement, const vector<AnnimStep> &steps);
  static byte currentValue(float avancement, const vector<AnnimStep>* steps);
  static vector<AnnimStep>* offsetSteps(vector<AnnimStep> &inital, float offset);
  static vector<AnnimStep>* offsetStepsLoop(vector<AnnimStep> &inital, float offset);
  static vector<AnnimStep>* offsetStepsLoopComplet(vector<AnnimStep> &inital, float offset);
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
