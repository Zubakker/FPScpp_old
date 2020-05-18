#include "wall.h"

using namespace std;

Wall::Wall(vector <vector <float> > point, string color) {
    /* In this part I calculate coeficents
       A, B, C, D needed for defining a 3D plane
    */
    float x1 = point[0][0];
    float x2 = point[1][0];
    float x3 = point[2][0];

    float y1 = point[0][1];
    float y2 = point[1][1];
    float y3 = point[2][1];

    float z1 = point[0][2];
    float z2 = point[1][2];
    float z3 = point[2][2];

    float A = (y2*z3 - y3*z2 - y1*z3 + y3*z1 + y1*z2 - y2*z1);
    float B = (x1*z3 - x1*z2 - x2*z3 + x2*z1 + x3*z2 - x3*z1);
    float C = (x1*y2 - x1*y3 - x2*y1 + x2*y3 + x3*y1 - x3*y2);
    float D = 0 - (A*x1 + B*y1 + C*z1);
    // float D = (x1*y3*z2 - x2*y3*z1 + x3*y2*z1);

    function.push_back(A);
    function.push_back(B);
    function.push_back(C);
    function.push_back(D);

    points = point;
    COLOR = color;
}
