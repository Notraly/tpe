//
//  LedRGB.cpp
//
//  Created by <author> on 19/01/2018.
//
//

#include "LedRGB.hpp"

LedRGB::LedRGB(byte pinRed, byte pinGreen, byte pinBlue)  {
	pinR = pinRed;
	pinG = pinGreen;
	pinB = pinBlue;
}
LedRGB::~LedRGB() {

}
void LedRGB::init(){
	if (pinR != -1) {
    pinMode(pinR, OUTPUT);
  }
  if (pinG != -1) {
    pinMode(pinG, OUTPUT);
  }
	if (pinB != -1) {
    pinMode(pinB, OUTPUT);
  }

}

void LedRGB::setValue(float red, float green, float blue){
	r = red;
	g = green;
	b = blue;
}
int LedRGB::getRed(){
	// r étant une variable de l'objet
	return r;
}
int LedRGB::getGreen(){
	return g;
}
int LedRGB::getBlue(){
	return b;
}
