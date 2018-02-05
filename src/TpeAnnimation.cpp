//
//  TpeAnnimation.cpp
//
//  Created by Egaro555 on 03/02/2018.
//
//

#include "TpeAnnimation.h"

// PRIVATE ============================================================ PRIVATE
// ------------------------------------------------------------------- methodes

// END PRIVATE
// PUBLIC ============================================================== PUBLIC
// -------------------------------------------------------------- Constuctors

TpeAnnimation::TpeAnnimation()  {

}
TpeAnnimation::TpeAnnimation(Annim data): data(data)  {

}

// ------------------------------------------------------------------- Methodes
byte TpeAnnimation::currentRed(float avancement, uint group, uint led){
  return currentValue(avancement ,getAnnimLed(group, led)->stepsRed);
}
byte TpeAnnimation::currentBlue(float avancement, uint group, uint led){
  return currentValue(avancement ,getAnnimLed(group, led)->stepsBlue);
}
byte TpeAnnimation::currentRed(float avancement, uint led){
  return currentValue(avancement ,getAnnimLed(led)->stepsRed);
}
byte TpeAnnimation::currentBlue(float avancement, uint led){
  return currentValue(avancement ,getAnnimLed(led)->stepsBlue);
}
byte TpeAnnimation::currentValue(float avancement, const vector<AnnimStep>* steps){
  if(steps != nullptr) return 0.;
  return currentValue(avancement,*steps);
}
byte TpeAnnimation::currentValue(float avancement, const vector<AnnimStep> &steps){
  uint nbSteps = steps.size();
  uint stepsId = 0;
  for(; stepsId < nbSteps && steps[nbSteps].setpTime <= avancement ; nbSteps++);
  if(stepsId == 0) return steps[0].value;
  if(stepsId == nbSteps) return steps[stepsId-1].value;
  AnnimStep s1 = steps[stepsId-1];
  AnnimStep s2 = steps[stepsId];
  float coef1 = (s2.setpTime-avancement)/(s2.setpTime-s1.setpTime);

  return s1.value * coef1 + s2.value * (1-coef1);
}
void TpeAnnimation::copyBack(uint length, uint startFrom, vector<AnnimStep> &from, vector<AnnimStep> &to, float offest){
  for(uint i=0;length>i;i++){
    to.push_back({from[startFrom+i].setpTime +offest, from[startFrom+i].value});
  }
}
vector<AnnimStep>* TpeAnnimation::oneStep(AnnimStep &step){
  vector<AnnimStep>* res = new vector<AnnimStep>();
  res->push_back(step);
  return res;
}
vector<AnnimStep>* TpeAnnimation::offsetSteps(vector<AnnimStep> &steps, float offset){
  uint nbStep = steps.size();
  uint firstStep = 0;
  if(offset<0){
    AnnimStep startedStep = {0.,currentValue(-offset,steps)};
    if(steps[nbStep-1].setpTime < -offset) return oneStep(startedStep);
    for(;steps[firstStep].setpTime < -offset ; firstStep++);
    vector<AnnimStep>* res = new vector<AnnimStep>();
    if(firstStep > 0) res->push_back(startedStep);
    copyBack(nbStep-firstStep,firstStep,steps,*res,offset);
    return res;
  }else{
    AnnimStep lastStep = {1.,currentValue(1.-offset,steps)};
    if(steps[0].setpTime >= offset) return oneStep(lastStep);
    for(;steps[nbStep-1].setpTime > 1.-offset ; nbStep--);

    vector<AnnimStep>* res = new vector<AnnimStep>();
    copyBack(nbStep,0,steps,*res,offset);
    res->push_back(lastStep);
    return res;
  }
}
vector<AnnimStep>* TpeAnnimation::offsetStepsLoop(vector<AnnimStep> &steps, float offset){
  uint nbStep = steps.size();
  uint nbStepBeforOffset = 0;
  for(;nbStepBeforOffset<nbStep && steps[nbStepBeforOffset].setpTime < offset;nbStepBeforOffset++);
  vector<AnnimStep>* res = new vector<AnnimStep>();
  copyBack(nbStep-nbStepBeforOffset,nbStepBeforOffset,steps,*res,offset-1);
  copyBack(nbStepBeforOffset,0,steps,*res,offset);
  return res;
}
vector<AnnimStep>* TpeAnnimation::offsetStepsLoopComplet(vector<AnnimStep> &steps, float offset){
  uint nbStep = steps.size();
  uint nbStepBeforOffset = 0;
  for(;nbStepBeforOffset<nbStep && steps[nbStepBeforOffset].setpTime < offset;nbStepBeforOffset++);

  byte startValue = steps[0].value;
  byte endValue = steps[nbStep-1].value;
  bool diffStartEnd = startValue != endValue;
  bool cutcourbe = nbStepBeforOffset != 0 && nbStepBeforOffset != nbStep && steps[nbStepBeforOffset-1].value != steps[nbStepBeforOffset].value;
  byte cutValue = currentValue(1.-offset,steps);

  vector<AnnimStep>* res = new vector<AnnimStep>();
  if(cutcourbe)res->push_back({0.,cutValue});
  copyBack(nbStep-nbStepBeforOffset,nbStepBeforOffset,steps,*res,offset-1);
  if(diffStartEnd){
    res->push_back({offset,endValue});
    res->push_back({offset,startValue});
  }
  copyBack(nbStepBeforOffset,0,steps,*res,offset);
  if(cutcourbe)res->push_back({1.,cutValue});

  return res;
}
// --------------------------------------------------------- Getteurs/Sertteurs
AnnimGroup* TpeAnnimation::getAnnimGroup(uint group){
  return &data.group[group];
}
AnnimLed* TpeAnnimation::getAnnimLed(uint group, uint led){
  return &data.group[group].led[led];
}
AnnimLed* TpeAnnimation::getAnnimLed(uint led){
  return getAnnimLed(led/TPE_NB_LEDRGB_BY_GROUP , led%TPE_NB_LEDRGB_BY_GROUP );
}
// ------------------------------------------------------------------ Destuctor

TpeAnnimation::~TpeAnnimation() {

}

// END PUBLIC
// PROTECTED ======================================================== PROTECTED

// END PUBLIC
