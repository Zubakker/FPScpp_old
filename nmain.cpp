#include <iostream>
#include <curses.h>
#include "tdm.h"

using namespace std;

int main() {
    TDM screen(132, 80);
    screen.window_render();
    float x1, x2, x3, x4, y1, y2, y3, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    vector <pair <float, float> > points;
    points.push_back(make_pair(x1, y1));
    points.push_back(make_pair(x2, y2));
    points.push_back(make_pair(x3, y3));
    points.push_back(make_pair(x4, y4));
    screen.draw_polygon4(points, "Red"); 
    /**/
    screen.window_render();
}

/*
-4.99992 8.74228e-07
5.00008 8.74228e-07
5.00008 -5
-4.99992 -5

-5 0
5 0
5 -5
-5 -5

-5 -5
5 -5
5 0
-5 0

-8.79989 -6.27833e-06
11.2001 -6.27833e-06
11.2001 -10
-8.79989 -10
*/
