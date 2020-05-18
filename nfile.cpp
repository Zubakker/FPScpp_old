#include "nfile.h"

Camera::Camera(float X, float Y, float Z) { //, vector <TDM> windows) {
    position.push_back(X);
    position.push_back(Y);
    position.push_back(Z);
  
    //screen = windows[0];
}

void Camera::Set_screen( TDM window ){
    TDM screen = window;
}
