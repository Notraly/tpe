#include <Arduino.h>
#include "./TpeAnimation.h"
#include "./LedsGroupsManager.h"
#include "IRremote.h"

//byte pinsLedsRGB[TPE_NB_LEDRGB_BY_GROUP][2], byte pinGroups[TPE_NB_GROUP]

const byte pinsLeds[3][2] = {{2,3},{6,7},{8,5}};//{{2,3},{13,5},{6,7}};
const byte pinsGroups[5] = {53, 51, 49, 47, 45}; //{8,9,10,11,12};
const byte pinsIR = 11;  //26
const byte pinVCC = 12;  //24
const byte pinGND = 13;  //22
const byte pinGND2 = 30;
const byte pinGND3 = 34;
const byte pinWarning = 31;
const byte pinCheck = 35;

IRrecv irrecv(pinsIR);
decode_results results;

LedsGroupsManager manager = LedsGroupsManager(pinsLeds,pinsGroups);

TpeAnimation* animDflt = nullptr;
TpeAnimation* animPwr = nullptr;
TpeAnimation* anim0 = nullptr;
TpeAnimation* anim1 = nullptr;
TpeAnimation* anim2 = nullptr;
TpeAnimation* anim3 = nullptr;
TpeAnimation* anim4 = nullptr;

void setup() {

	pinMode(pinVCC, OUTPUT);
	pinMode(pinGND, OUTPUT);
	pinMode(pinGND2, OUTPUT);
	pinMode(pinGND3, OUTPUT);
	pinMode(pinWarning, OUTPUT);
	pinMode(pinCheck, OUTPUT);


	digitalWrite(pinVCC, HIGH);
	digitalWrite(pinGND, LOW);
	digitalWrite(pinGND2, LOW);
	digitalWrite(pinGND3, LOW);

	irrecv.enableIRIn();

	Serial.begin(9600);
	manager.init();


	AnimArray* anHigh= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep> {{.0,255},{1.,255}}));
	AnimArray* anLow= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep> {{.0,0},{1.,0}}));
	AnimArray* anUp= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep> {{.0,0},{1.,255}}));
	AnimArray* anDown= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep> {{.0,255},{1.,0}}));

	AnimLed animation_data_ledDflt_0 = {anLow,anLow};
	AnimGroup animation_data_groupDflt_0 = {animation_data_ledDflt_0,animation_data_ledDflt_0,animation_data_ledDflt_0};

	Anim animation_dataDflt = {
		animation_data_groupDflt_0,
		animation_data_groupDflt_0,
		animation_data_groupDflt_0,
		animation_data_groupDflt_0,
		animation_data_groupDflt_0
	};
	animDflt = new TpeAnimation(animation_dataDflt); // default

	AnimArray* anPwr_0= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep> {{.0,0},{0.2,20},{0.2,0},{0.3,20},{0.4,0},{0.5,20},{0.6,0}}));
	AnimArray* anPwr_1= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep> {{.0,20},{0.1,0},{0.2,20},{0.3,0},{0.4,20},{0.5,0}}));

	AnimLed animation_data_ledPwr_0 = {anPwr_0,anPwr_1};

	AnimGroup animation_data_groupPwr_0 = {animation_data_ledPwr_0,animation_data_ledPwr_0,animation_data_ledPwr_0};

	Anim animation_dataPwr = {
		animation_data_groupPwr_0,
		animation_data_groupPwr_0,
		animation_data_groupPwr_0,
		animation_data_groupPwr_0,
		animation_data_groupPwr_0
	};
	animPwr = new TpeAnimation(animation_dataPwr); // Allumage

	//new vector<AnimStep> {{.0,},{.015,10},{.03,0}};
	AnimLed animation_data_led1_0 = {anLow,anHigh};
	AnimLed animation_data_led1_1 = {anLow,anDown};
  AnimLed animation_data_led1_2 = {anLow,anLow};

	AnimGroup animation_data_group1_0 = {animation_data_led1_0,animation_data_led1_0,animation_data_led1_0};
	AnimGroup animation_data_group1_1 = {animation_data_led1_1,animation_data_led1_1,animation_data_led1_1};
  AnimGroup animation_data_group1_2 = {animation_data_led1_2,animation_data_led1_2,animation_data_led1_1};
  // led 0 du groupe     led 1 du groupe     led 2 du groupe
	Anim animation_data1 = {
		animation_data_group1_0,
		animation_data_group1_0,
    animation_data_group1_2,
		animation_data_group1_1,
		animation_data_group1_1
	};
	anim1 = new TpeAnimation(animation_data1); // debut journée

	AnimLed animation_data_led2_0 = {anLow,anLow};
	AnimLed animation_data_led2_1 = {anUp,anDown};

	AnimGroup animation_data_group2_0 = {animation_data_led2_0,animation_data_led2_0,animation_data_led2_0};
	AnimGroup animation_data_group2_1 = {animation_data_led2_1,animation_data_led2_1,animation_data_led2_1};
	// led 0 du groupe     led 1 du groupe     led 2 du groupe
	Anim animation_data2 = {
		animation_data_group2_1,
		animation_data_group2_1,
		animation_data_group2_0,
		animation_data_group2_0,
		animation_data_group2_0,
	};
	anim2 = new TpeAnimation(animation_data2); // pendant journée

	AnimLed animation_data_led3_0 = {anLow,anUp};
	AnimLed animation_data_led3_1 = {anHigh,anLow};
  AnimLed animation_data_led3_2 = {anLow,anLow};

	AnimGroup animation_data_group3_0 = {animation_data_led3_0,animation_data_led3_0,animation_data_led3_0};
	AnimGroup animation_data_group3_1 = {animation_data_led3_1,animation_data_led3_1,animation_data_led3_1};
  AnimGroup animation_data_group3_2 = {animation_data_led3_2,animation_data_led3_2,animation_data_led3_0};


	Anim animation_data3 = {
		animation_data_group3_1,
		animation_data_group3_1,
		animation_data_group3_2,
		animation_data_group3_0,
		animation_data_group3_0
	};
	anim3 = new TpeAnimation(animation_data3); // Soir


	AnimArray* an4_G0R0= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,255},{0.25,255},{0.45,0}}));
  AnimArray* an4_G0B0= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0},{0.25,0},{0.45,255}}));
  AnimArray* an4_G0R1= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,255},{0.2,255},{0.4,0}}));
  AnimArray* an4_G0B1= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0},{0.2,0},{0.4,255}}));
  AnimArray* an4_G0R2= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,255},{0.1,255},{0.3,0}}));
  AnimArray* an4_G0B2= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0},{0.1,0},{0.3,255}}));
  AnimArray* an4_G1R0= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,255},{0.4,255},{0.6,0}}));
  AnimArray* an4_G1B0= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0},{0.4,0},{0.6,255}}));
  AnimArray* an4_G1R1= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,255},{0.3,255},{0.5,0}}));
  AnimArray* an4_G1B1= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0},{0.3,0},{0.5,255}}));
  AnimArray* an4_G1R2= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,255},{0.25,255},{0.45,0}}));
  AnimArray* an4_G1B2= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0},{0.25,0},{0.45,255}}));
  AnimArray* an4_G2R0= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0},{0.1,0},{0.3,255},{0.75,255},{0.85,0}}));
  AnimArray* an4_G2B0= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0}}));
  AnimArray* an4_G2R1= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0},{0.25,0},{0.45,255},{0.7,255},{0.8,0}}));
  AnimArray* an4_G2B1= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0}}));
  AnimArray* an4_G2R2= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0},{0.2,0},{0.4,255},{0.65,255},{0.75,0}}));
  AnimArray* an4_G2B2= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,255},{0.2,255},{0.4,0},{0.65,0},{0.75,255}}));
  AnimArray* an4_G3R0= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0},{0.1,0},{0.3,255},{0.6,255},{0.7,0}}));
  AnimArray* an4_G3B0= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,255},{0.1,255},{0.3,0},{0.6,0},{0.7,255}}));
	for(int i=0;i<100;i++)Serial.println((int) an4_G3B0->data[i]);
  AnimArray* an4_G3R1= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0}}));
  AnimArray* an4_G3B1= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,255}}));
  AnimArray* an4_G3R2= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0}}));
  AnimArray* an4_G3B2= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,255}}));

  AnimArray* an4_G4R2= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,0},{0.2,0},{0.4,255},{0.8,255},{1,0}}));
  AnimArray* an4_G4B2= new AnimArray(TpeAnimation::animStepToArray(vector<AnimStep>{{0,255}}));

AnimLed animation_data_led4_G0_0 = {an4_G0R0,an4_G0B0};
AnimLed animation_data_led4_G0_1 = {an4_G0R1,an4_G0B1};
AnimLed animation_data_led4_G0_2 = {an4_G0R2,an4_G0B2};

AnimLed animation_data_led4_G1_0 = {an4_G1R0,an4_G1B0};
AnimLed animation_data_led4_G1_1 = {an4_G1R1,an4_G1B1};
AnimLed animation_data_led4_G1_2 = {an4_G1R2,an4_G1B2};

AnimLed animation_data_led4_G2_0 = {an4_G2R0,an4_G2B0};
AnimLed animation_data_led4_G2_1 = {an4_G2R1,an4_G2B1};
AnimLed animation_data_led4_G2_2 = {an4_G2R2,an4_G2B2};

AnimLed animation_data_led4_G3_0 = {an4_G3R0,an4_G3B0};
AnimLed animation_data_led4_G3_1 = {an4_G3R1,an4_G3B1};
AnimLed animation_data_led4_G3_2 = {an4_G3R2,an4_G3B2};

AnimLed animation_data_led4_G4_0 = {nullptr,nullptr};
AnimLed animation_data_led4_G4_1 = {an4_G4R2,an4_G4B2};



  AnimGroup animation_data_group4_0 = {animation_data_led4_G0_0, animation_data_led4_G0_1,  animation_data_led4_G0_2};
  AnimGroup animation_data_group4_1 = {animation_data_led4_G1_0, animation_data_led4_G1_1,  animation_data_led4_G1_2};
  AnimGroup animation_data_group4_2 = {animation_data_led4_G2_0, animation_data_led4_G2_1,  animation_data_led4_G2_2};
  AnimGroup animation_data_group4_3 = {animation_data_led4_G3_0, animation_data_led4_G3_1,  animation_data_led4_G3_2};
  AnimGroup animation_data_group4_4 = {animation_data_led4_G4_0, animation_data_led4_G4_0,  animation_data_led4_G4_1};

  Anim animation_data4 = {
    animation_data_group4_0,
    animation_data_group4_1,
    animation_data_group4_2,
    animation_data_group4_3,
    animation_data_group4_4
  };
anim4 = new TpeAnimation(animation_data4); // Soir

	manager.changeAnimation(animDflt, 1, true, false);

}

void loop() {
	manager.loop();
	if (irrecv.decode(&results)) {

		bool knowCommand = true;

		Serial.print("IR : ");
		Serial.println(results.value, HEX);

		switch(results.value) {
		case 0xFFA25D://power
			manager.changeAnimation(animPwr, 1500, false);
			break;
		case 0xFF6897://0

			break;
		case 0xFF30CF://1
			manager.changeAnimation(anim1, 8000, false, false);
			break;
		case 0xFF18E7://2
			manager.changeAnimation(anim2, 5000, false);
			break;
		case 0xFF7A85://3
			manager.changeAnimation(anim3, 6000, false);
			break;

    case 0xFF10EF://4
      manager.changeAnimation(anim4, 10000, false);
        break;
    case 0xFF38C7://5

			break;
		case 0xFF5AA5://6

			break;
		case 0xFF42BD://7

			break;
		case 0xFF4AB5://8

			break;
		case 0xFF52AD://9

			break;
		case 0xFF02FD://PlayPose
			manager.playPause();
			break;
		case 0xFFB04F://Rept
			manager.setAnimationLoop(true);
			break;
		case 0xFFE21D://Stop
			manager.setAnimationLoop(false);
			break;
    case 0xFFC23D:// >>
      manager.accelerate(1.25);
  			break;
    case 0xFF22DD:// <<
      manager.accelerate(0.8);
      			break;
		default://n'est pas une commande connue
			knowCommand = false;
		}

		if (results.value != 0xFF && results.value != 0xFFFF && results.value != 0xFFFFFFFF) {
			if(knowCommand == true) {
				digitalWrite(pinCheck, HIGH);
				digitalWrite(pinWarning, LOW);
			}else{
				digitalWrite(pinWarning, HIGH);
				digitalWrite(pinCheck, LOW);
			}
		}
		irrecv.resume();
	}
}
