#ifndef WALL_H
#define WALL_H

#include <utility>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;


class Wall {
    public:
        // ================ functions ================
        Wall (vector <vector <float> > points, string color);
        // ================ variables ================
        vector <vector <float> > points; // every subvector is {x, y, z}
        vector <float> function; // Here will be A, B, C and D needed \
            // to define a plane in 3D space like A*x + B*y + C*z + D = 0
        string COLOR; // It should be one of 8, not "Bright ..." all colors: \
            // red, gre, bla, blu, yel, mag, cya, whi. See TDM func in tdm.cpp
        float distance; // distance from Camera. Only Camera functions define it
};

#endif
