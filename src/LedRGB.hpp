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

class LedRGB {
private:
  float r, g, b;
  byte pinR, pinG, pinB;
public:
    void init();
    void setValue(float red, float green, float blue); // Setteur = modif valeurs
    int getRed(); // Getteur = récup valeur
    int getGreen();
    int getBlue();
    LedRGB(byte pinRed, byte pinGreen, byte pinBlue); // Constructeur
    ~LedRGB(); // Destructeur
protected:

};


#endif /* LedRGB_hpp */
