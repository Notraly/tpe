//
//  LedRGB.hpp
//
//  Created by <author> on 19/01/2018.
//
//

#ifndef LedRGB_hpp
#define LedRGB_hpp

#include <stdio.h>
#include <arduino.h>

struct Color{
  byte red,green,blue;
};

class LedRGB {
private:
  Color color;
  byte pinR, pinG, pinB;
  void changePinValue(byte pin, byte color);
  void changePinsValue();
  bool enable;
public:
  static const byte PWM_LOW_VALUE = 255;
  static const byte PWM_HIGH_VALUE = 0;

  void init();
  void setValue(byte red, byte green, byte blue); // Setteur = modif valeurs
  void setValue(Color c);
  float getRed(); // Getteur = récup valeur
  float getGreen();
  float getBlue();
  Color getColor();
  bool isEnable()const;
  void setEnable(const bool &enable);
  LedRGB(byte pinRed, byte pinGreen, byte pinBlue); // Constructeur
  ~LedRGB(); // Destructeur
protected:

};


#endif /* LedRGB_hpp */
