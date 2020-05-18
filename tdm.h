#ifndef TDM_H
#define TDM_H

#include <utility>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;


class TDM {
    public:

        // ====================== functions ==========================
        TDM (int x, int y);
        TDM ();
        void window_render();
        void draw_line(pair <float, float> p1, pair <float, float> p2,
             string color);
        void draw_polygon4(vector <pair <float, float> > points, string color);
             // ^ draw a four point polygon (quadrangle)
        void draw_text(string text, string color);
        void draw_point(pair <float, float> coords, string color);
        void fill_screen(string color);
        bool check_point(pair <float, float> point); 
             // ^ checks if point coords are on the screen

        // ====================== variables ==========================
        int WIDTH, HEIGHT;
        vector <vector <pair <string, string>> > window;
        map <string, string> COLORS;
        map <string, string> BGCOLORS;
        string BLOCK;
        string HALF;
        string CLEAR_SCREEN;
};

#endif
