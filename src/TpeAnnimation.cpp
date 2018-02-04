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
float TpeAnnimation::currentRed(float avancement, uint group, uint led){
  return currentValue(avancement ,&getAnnimLed(group, led)->stepsRed);
}
float TpeAnnimation::currentBlue(float avancement, uint group, uint led){
  return currentValue(avancement ,&getAnnimLed(group, led)->stepsBlue);
}
float TpeAnnimation::currentRed(float avancement, uint led){
  return currentValue(avancement ,&getAnnimLed(led)->stepsRed);
}
float TpeAnnimation::currentBlue(float avancement, uint led){
  return currentValue(avancement ,&getAnnimLed(led)->stepsBlue);
}
float TpeAnnimation::currentValue(float avancement, const list<AnnimStep>* steps){
  AnnimStep* last = nullptr;

  auto iterateur = steps->begin();
  if(iterateur == steps->end()) return 0.;
  for(iterateur = steps->begin() ; iterateur != steps->end() && iterateur->setpTime > avancement ;iterateur++){
    last = &*iterateur;
  }
  if(last == nullptr) return iterateur->value;
  if(iterateur == steps->end()) return last->value;
  AnnimStep s1 = *last;
  AnnimStep s2 = *iterateur;
  float coef1 = (avancement-s1.setpTime)/(s2.setpTime-s1.setpTime);

  return s1.value * coef1 + s2.value * (1-coef1);
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
