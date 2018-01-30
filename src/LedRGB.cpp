//
//  LedRGB.cpp
//
//  Created by <author> on 19/01/2018.
//
//

#include "LedRGB.h"

LedRGB::LedRGB(byte pinRed, byte pinGreen, byte pinBlue)  {
	pinR = pinRed;
	pinG = pinGreen;
	pinB = pinBlue;

	color = {0,0,0};

	enable = false;
}
LedRGB::~LedRGB() {

}
void LedRGB::init(){
	if (pinR != -1) pinMode(pinR, OUTPUT);
  if (pinG != -1) pinMode(pinG, OUTPUT);
	if (pinB != -1) pinMode(pinB, OUTPUT);
	setEnable(true);
}
void LedRGB::changePinsValue(){
	changePinValue(pinR, color.red);
	changePinValue(pinG, color.green);
	changePinValue(pinB, color.blue);
}
void LedRGB::changePinValue(byte pin, float color){
	if (pin != -1) {
		if (color > 0.5 ) { // digitalWrite(pin, color > 0.5 ? HIGH : LOW);
			digitalWrite(pin, HIGH);
		} else {
			digitalWrite(pin, LOW);
		}
	}
}

Color LedRGB::getColor(){ return color; }
float LedRGB::getRed(){ return color.red; }
float LedRGB::getGreen(){	return color.green; }
float LedRGB::getBlue(){ return color.blue; }
void LedRGB::setValue(float red, float green, float blue){ setValue({red,green,blue}); }
void LedRGB::setValue(Color c){
	color = c;
	if(enable) changePinsValue();
}

bool LedRGB::isEnable()const{ return enable; }
void LedRGB::setEnable(const bool &enable){
	this->enable = enable;
	if(enable) changePinsValue();
}
