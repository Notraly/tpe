//
//  TpeAnimation.hpp
//
//  Created by Egaro555 on 03/02/2018.
//
//

#ifndef TpeAnimation_h
#define TpeAnimation_h

// ===================================================================== INLUDE

#include <stdio.h>
#include <vector>
#include <Arduino.h>
#include "Util.h"
#include "TpeConfig.h"

using namespace std;

// --------------------------------------------------------------------- Struct
struct AnimStep{
  float stepTime; // Betwin 0 and 1
  byte value; // stepValue;
};
struct AnimArray{
  byte data[101];
};
struct AnimLed{
  AnimArray* arrayRed;
  AnimArray* arrayBlue;

};
struct AnimGroup{
  AnimLed led[TPE_NB_LEDRGB_BY_GROUP];
};
struct Anim{
  AnimGroup group[TPE_NB_GROUP];
  Anim* next;
};

// ---------------------------------------------------------------------- const

class TpeAnimation {
private: //============================================================ PRIVATE
  // -------------------------------------------------------------------- const
  // --------------------------------------------------------------- attributes
  Anim data;
  TpeAnimation* next = nullptr;
  // ----------------------------------------------------------------- methodes
  static void copyBack(uint length, uint startFrom, vector<AnimStep> &from, vector<AnimStep> &to, float offest);
  static vector<AnimStep>* oneStep(AnimStep &step);
  // END PRIVATE
public: //============================================================== PUBLIC
  // -------------------------------------------------------------- Constuctors
  TpeAnimation();
  TpeAnimation(Anim data);
  TpeAnimation(Anim data,TpeAnimation* next);
  // ----------------------------------------------------------------- Methodes
  byte currentRed(byte avancement, uint group, uint led);
  byte currentBlue(byte avancement, uint group, uint led);
  byte currentRed(byte avancement, uint led);
  byte currentBlue(byte avancement, uint led);
  static byte currentValue(float avancement, const vector<AnimStep> &steps);
  static byte currentValue(float avancement, const vector<AnimStep>* steps);
  static vector<AnimStep>* offsetSteps(vector<AnimStep> &inital, float offset);
  static vector<AnimStep>* offsetStepsLoop(vector<AnimStep> &inital, float offset);
  static vector<AnimStep>* offsetStepsLoopComplet(vector<AnimStep> &inital, float offset);
  static AnimArray animStepToArray(vector<AnimStep> steps);
  static void print(const vector<AnimStep> &steps);
  // ------------------------------------------------------- Getteurs/Sertteurs
  AnimGroup* getAnimGroup(uint group);
  AnimLed* getAnimLed(uint group, uint led);
  AnimLed* getAnimLed(uint led);
  TpeAnimation* getNext();
  /*bool hasNext()const;
  void next();*/
  // ---------------------------------------------------------------- Destuctor
  ~TpeAnimation();
  // END PUBLIC
protected: //======================================================== PROTECTED

};

#endif /* TpeAnimation_h */
