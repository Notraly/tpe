#include <Arduino.h>
#include "./TpeAnnimation.h"
#include "./LedsGroupsManager.h"
#include "IRremote.h"

//byte pinsLedsRGB[TPE_NB_LEDRGB_BY_GROUP][2], byte pinGroups[TPE_NB_GROUP]

const byte pinsLeds[3][2] = {{4,5},{7,8},{10,11}};
const byte pinsGroups[5] = {3,6,9,12,13};
const byte pinsIR = 2 ;

IRrecv irrecv(pinsIR);
decode_results results;

LedsGroupsManager manager = LedsGroupsManager(pinsLeds,pinsGroups);

TpeAnnimation* annim1 = nullptr;

void setup() {
  Serial.begin(9600);
  manager.init();

  //new vector<AnnimStep> {{.0,},{.015,10},{.03,0}};
  AnnimLed animation_data_led = {
    new vector<AnnimStep> {{.0,0},{.5,10},{1.,10}},
    new vector<AnnimStep> {{.0,0},{.5,10},{1.,10}}
  };
  AnnimGroup animation_data_group = {animation_data_led,animation_data_led,animation_data_led};
  Annim animation_data = {animation_data_group,animation_data_group,animation_data_group,animation_data_group,animation_data_group};
  annim1 = new TpeAnnimation(animation_data);

  manager.changeAnnimation(annim1, 2000);
}

void loop() {
  manager.loop();
  if (irrecv.decode(&results)){
   Serial.print("IR : ");
   Serial.println(results.value, HEX);
    switch(results.value){
      case 0xFFA25D://power

        break;
      case 0xFF6897://0

        break;
      case 0xFF30CF://1

        break;
      case 0xFF18E7://2

        break;
      case 0xFF7A85://3

        break;
      case 0xFF38C7://5

        break;
      case 0xFF42BD://7

        break;
      case 0xFF4AB5://8

        break;
      case 0xFF52AD://9

        break;

      case 0xFF02FD://PlayPose
        
        break;
    }
   }
   irrecv.resume();
}
