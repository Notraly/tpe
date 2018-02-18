//
//  TpeAnimation.cpp
//
//  Created by Egaro555 on 03/02/2018.
//
//

#include "TpeAnimation.h"

// PRIVATE ============================================================ PRIVATE
// ------------------------------------------------------------------- methodes

// END PRIVATE
// PUBLIC ============================================================== PUBLIC
// -------------------------------------------------------------- Constuctors



TpeAnimation::TpeAnimation()  {

}
TpeAnimation::TpeAnimation(Anim data): data(data)  {

}

// ------------------------------------------------------------------- Methodes
byte TpeAnimation::currentRed(float avancement, uint group, uint led){
  return getAnimLed(group, led)->arrayRed->data[(uint)avancement*100];
}
byte TpeAnimation::currentBlue(float avancement, uint group, uint led){
  return getAnimLed(group, led)->arrayBlue->data[(uint)avancement*100];
}
byte TpeAnimation::currentRed(float avancement, uint led){
  return getAnimLed(led)->arrayRed->data[(uint)avancement*100];
}
byte TpeAnimation::currentBlue(float avancement, uint led){
  return getAnimLed(led)->arrayBlue->data[(uint)avancement*100];
}
byte TpeAnimation::currentValue(float avancement, const vector<AnimStep>* steps){
  if(steps == nullptr) return 0.;
  return currentValue(avancement,*steps);
}
void TpeAnimation::print(const vector<AnimStep> &steps){
  Serial.print("[");
  for(auto an : steps){
    Serial.print("{ stepTime: ");
    Serial.print(an.stepTime);
    Serial.print(", value: ");
    Serial.print(an.value);
    Serial.print("}, ");
    break;
  }
  Serial.print("]\t");
}
byte TpeAnimation::currentValue(float avancement, const vector<AnimStep> &steps){
  uint nbSteps = steps.size();
  uint stepsId = 0;
  for(; stepsId < nbSteps && steps[stepsId].stepTime <= avancement ; stepsId++);
  if(stepsId == 0) return steps[0].value;
  if(stepsId == nbSteps) return steps[stepsId-1].value;
  AnimStep s1 = steps[stepsId-1];
  AnimStep s2 = steps[stepsId];
  float coef1 = (s2.stepTime-avancement)/(s2.stepTime-s1.stepTime);

  return s1.value * coef1 + s2.value * (1-coef1);
}
void TpeAnimation::copyBack(uint length, uint startFrom, vector<AnimStep> &from, vector<AnimStep> &to, float offest){
  for(uint i=0;length>i;i++){
    to.push_back({from[startFrom+i].stepTime +offest, from[startFrom+i].value});
  }
}
vector<AnimStep>* TpeAnimation::oneStep(AnimStep &step){
  vector<AnimStep>* res = new vector<AnimStep>();
  res->push_back(step);
  return res;
}
vector<AnimStep>* TpeAnimation::offsetSteps(vector<AnimStep> &steps, float offset){
  uint nbStep = steps.size();
  uint firstStep = 0;
  if(offset<0){
    AnimStep startedStep = {0.,currentValue(-offset,steps)};
    if(steps[nbStep-1].stepTime < -offset) return oneStep(startedStep);
    for(;steps[firstStep].stepTime < -offset ; firstStep++);
    vector<AnimStep>* res = new vector<AnimStep>();
    if(firstStep > 0) res->push_back(startedStep);
    copyBack(nbStep-firstStep,firstStep,steps,*res,offset);
    return res;
  }else{
    AnimStep lastStep = {1.,currentValue(1.-offset,steps)};
    if(steps[0].stepTime >= offset) return oneStep(lastStep);
    for(;steps[nbStep-1].stepTime > 1.-offset ; nbStep--);

    vector<AnimStep>* res = new vector<AnimStep>();
    copyBack(nbStep,0,steps,*res,offset);
    res->push_back(lastStep);
    return res;
  }
}
vector<AnimStep>* TpeAnimation::offsetStepsLoop(vector<AnimStep> &steps, float offset){
  uint nbStep = steps.size();
  uint nbStepBeforOffset = 0;
  for(;nbStepBeforOffset<nbStep && steps[nbStepBeforOffset].stepTime < offset;nbStepBeforOffset++);
  vector<AnimStep>* res = new vector<AnimStep>();
  copyBack(nbStep-nbStepBeforOffset,nbStepBeforOffset,steps,*res,offset-1);
  copyBack(nbStepBeforOffset,0,steps,*res,offset);
  return res;
}
vector<AnimStep>* TpeAnimation::offsetStepsLoopComplet(vector<AnimStep> &steps, float offset){
  uint nbStep = steps.size();
  uint nbStepBeforOffset = 0;
  for(;nbStepBeforOffset<nbStep && steps[nbStepBeforOffset].stepTime < offset;nbStepBeforOffset++);

  byte startValue = steps[0].value;
  byte endValue = steps[nbStep-1].value;
  bool diffStartEnd = startValue != endValue;
  bool cutcourbe = nbStepBeforOffset != 0 && nbStepBeforOffset != nbStep && steps[nbStepBeforOffset-1].value != steps[nbStepBeforOffset].value;
  byte cutValue = currentValue(1.-offset,steps);

  vector<AnimStep>* res = new vector<AnimStep>();
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
AnimArray TpeAnimation::animStepToArray(vector<AnimStep> steps){
  AnimArray res = AnimArray();
  for(int i=0;i<100;i++){
    res.data[i] = currentValue(i/100.,steps);
  }
  return res;
}
// --------------------------------------------------------- Getteurs/Sertteurs
AnimGroup* TpeAnimation::getAnimGroup(uint group){
  return &data.group[group];
}
AnimLed* TpeAnimation::getAnimLed(uint group, uint led){
  return &data.group[group].led[led];
}
AnimLed* TpeAnimation::getAnimLed(uint led){
  return getAnimLed(led/TPE_NB_LEDRGB_BY_GROUP , led%TPE_NB_LEDRGB_BY_GROUP );
}
// ------------------------------------------------------------------ Destuctor

TpeAnimation::~TpeAnimation() {

}

// END PUBLIC
// PROTECTED ======================================================== PROTECTED

// END PUBLIC
