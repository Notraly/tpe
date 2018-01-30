#include <Arduino.h>
#include "./LedRGB.h"

LedRGB led1 = LedRGB(2,3,-1);
LedRGB led2 = LedRGB(5,6,7);


void setup() {
    // put your setup code here, to run once:
    led1.init();
    led2.init();
}

void loop() {
    // put your main code here, to run repeatedly:
}
