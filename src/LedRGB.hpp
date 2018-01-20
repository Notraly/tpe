//
//  LedRGB.hpp
//
//  Created by <author> on 19/01/2018.
//
//

#ifndef LedRGB_hpp
#define LedRGB_hpp

#include <stdio.h>

class LedRGB {
private:
  int r, g, b;
public:
    void setValue(int red, int green, int blue); // Setteur = modif valeurs
    int getRed(); // Getteur = récup valeur
    int getGreen();
    int getBlue();
    LedRGB(); // Constructeur
    ~LedRGB(); // Destructeur
protected:

};


#endif /* LedRGB_hpp */
