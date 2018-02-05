//
//  Util.hpp
//
//  Created by Egaro555 on 30/01/2018.
//
//

#ifndef Util_h
#define Util_h

// ===================================================================== INLUDE

#include <stdio.h>
#include <vector>
#include <arduino.h>

// --------------------------------------------------------------------- Struct
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

// ---------------------------------------------------------------------- const

class Util {
private: //============================================================ PRIVATE
  // -------------------------------------------------------------------- const
  // --------------------------------------------------------------- attributes
  // -------------------------------------------------------------- Constuctors
  Util(); // INSTANTATION IMPOSIBLE
  // ---------------------------------------------------------------- Destuctor
  ~Util();
  // ----------------------------------------------------------------- methodes
  // END PRIVATE
public: //============================================================== PUBLIC
  // ----------------------------------------------------------------- Methodes
  // static vector<LedsGroup> genGroupvector(byte** pinsLedsRGB, byte* pinGroups);
  // ------------------------------------------------------- Getteurs/Sertteurs
  // END PUBLIC
protected: //======================================================== PROTECTED

};


#endif /* Util_h */
