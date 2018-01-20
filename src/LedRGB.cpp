//
//  LedRGB.cpp
//
//  Created by <author> on 19/01/2018.
//
//

#include "LedRGB.hpp"

LedRGB::LedRGB()  {

}
LedRGB::~LedRGB() {

}
void LedRGB::setValue(int red, int green, int blue){
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
