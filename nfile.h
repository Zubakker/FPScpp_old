#ifndef CAMERA_H
#define CAMERA_H

#include "tdm.h"

using namespace std;

class Camera {
     public:
          Camera (float X, float Y, float Z); //, vector <TDM> windows);
          void Set_screen( TDM window );
          
          vector <float> position;
          TDM screen;
};

#endif
