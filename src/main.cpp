#include <Arduino.h>
#include "./LedRGB.hpp"

struct ColorRB{
  int red, blue;
};

struct Leds{
  byte pinRed[3];
  byte pinBlue[3];
  byte pinGroup[5];

  ColorRB leds[5][3];
};


void coco();

void setup() {
  coco();
    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
}
