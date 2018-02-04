#include <Arduino.h>
#include "./TpeAnnimation.h"
#include "./LedsGroupsManager.h"

//byte pinsLedsRGB[TPE_NB_LEDRGB_BY_GROUP][2], byte pinGroups[TPE_NB_GROUP]

const byte pinsLeds[3][2] = {{4,5},{7,8},{10,11}};
const byte pinsGroups[5] = {3,6,9,12,13};

LedsGroupsManager manager = LedsGroupsManager(pinsLeds,pinsGroups);

TpeAnnimation* annim1 = nullptr;

void setup() {
  Serial.begin(14400);
  manager.init();


  AnnimLed animation_data_led = {};
  animation_data_led.stepsRed.push_back({0.,0});
  animation_data_led.stepsRed.push_back({1.,255});
  animation_data_led.stepsBlue.push_back({0.5,0});
  animation_data_led.stepsBlue.push_back({0.5,0});
  AnnimGroup animation_data_group = {animation_data_led,animation_data_led,animation_data_led};
  Annim animation_data = {animation_data_group,animation_data_group,animation_data_group,animation_data_group,animation_data_group};
  annim1 = new TpeAnnimation(animation_data);

  manager.changeAnnimation(annim1, 2000);
}

void loop() {
  manager.loop();
}
