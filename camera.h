#ifndef CAMERA_H
#define CAMERA_H

#include <utility>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <fstream>
#include <algorithm>

#include "wall.h"
#include "tdm.h"

using namespace std;


class Camera {
    public:

        // ================ functions ================
        Camera(float X, float Y, float Z, TDM* window); // camera init 
        void rotate_h(float angle); // rotate horizontaly add -pi to pi in float 
        void rotate_v(float angle); // rotate vertivally add -pi/2 to pi/2 in float 
        void move(float forward, float right, float up);
        vector <float> get_position() {return position;}; 
        void render(vector <Wall> printable); // render a vector of walls
        float calculate_distance(Wall wall); // distance between camera and wall
        vector <Wall> sort_walls(vector <Wall> to_sort);

        // ================ variables ================
        TDM* screen; // this is TDM class object needed to draw polygons
            // ^ TDM is my class written in tdm.h and tdm.cpp files
        vector <float> position; // vector of X Y and Z
        pair <float, float> view_angles; // pair {horizontal angl, vertical angl}
        float D_PI = M_PI * 2; // CONST two times the pi
        float H_PI = M_PI / 2.0; // CONST half the pi
        float SCREEN_DIST = 10; // distance from player to screen. It changes FOV
                    // ^ this value is temporary
        }; 

#endif
