#include "tdm.h" 

using namespace std;

//          ===FUNCTIONS===
TDM::TDM() {
    BLOCK = "█";
    HALF = "▀";
};


TDM::TDM(int x, int y) {
    BLOCK = "█";
    HALF = "▀";
    CLEAR_SCREEN = "\033[0;0f";
    // CLEAR_SCREEN = "\033[2J";
    COLORS = {
        {"Black", "\033[30m"},
        {"Red", "\033[31m"},
        {"Green", "\033[32m"},
        {"Yellow", "\033[33m"},
        {"Blue", "\033[34m"},
        {"Magenta", "\033[35m"},
        {"Cyan", "\033[36m"},
        {"White", "\033[37m"},
        {"Reset", "\033[0m"},
    
        {"Bright Black", "\033[30;1m"},
        {"Bright Red", "\033[31;1m"},
        {"Bright Green", "\033[32;1m"},
        {"Bright Yellow", "\033[33;1m"},
        {"Bright Blue", "\033[34;1m"},
        {"Bright Magenta", "\033[35;1m"},
        {"Bright Cyan", "\033[36;1m"},
        {"Bright White", "\033[37;1m"},
        {"Reset", "\033[0m"}
    };
    BGCOLORS = {
        {"Black", "\033[40m"},
        {"Red", "\033[41m"},
        {"Green", "\033[42m"},
        {"Yellow", "\033[43m"},
        {"Blue", "\033[44m"},
        {"Magenta", "\033[45m"},
        {"Cyan", "\033[46m"},
        {"White", "\033[47m"},
    
        {"Bright Black", "\033[40;1m"},
        {"Bright Red", "\033[41;1m"},
        {"Bright Green", "\033[42;1m"},
        {"Bright Yellow", "\033[43;1m"},
        {"Bright Blue", "\033[44;1m"},
        {"Bright Magenta", "\033[45;1m"},
        {"Bright Cyan", "\033[46;1m"},
        {"Bright White", "\033[47;1m"}
    };
    WIDTH = x;
    HEIGHT = y;
    for (int i = 0; i < (y / 2); ++i) {
        vector <pair <string, string>> line(x, make_pair(COLORS["Black"], 
                                 BGCOLORS["Yellow"]));
        window.push_back(line);
    };
};

void TDM::window_render() {
    cout << CLEAR_SCREEN;
    cout << COLORS["Reset"];
    string line;
    for (int i = 0; i < window.size(); ++i) {
        line = "";
        for (int j = 0; j < window[0].size(); ++j) {
            line += window[i][j].second;
            line += window[i][j].first;
            line += HALF; /**/
        }
        cout << line << COLORS["Reset"] << endl;
    }
};

void TDM::draw_point(pair <float, float> coords, string color) {
    int x = round(coords.first + WIDTH / 2);
    int y = round(coords.second + HEIGHT / 2);
    pair <string, string> point;
    if (y % 2 == 0) {
        point = window[y / 2][x];
        point.first = COLORS[color];
    } 
    else {
        point = window[y / 2][x];
        point.second = BGCOLORS[color];
    } 
    window[y / 2][x] = point;
    
};

void TDM::draw_line(pair <float, float> p1,
        pair <float, float> p2, string color) {
    float x, y, x1, x2, y1, y2, dx, dy, step;
    x1 = p1.first;
    y1 = p1.second;
    x2 = p2.first;
    y2 = p2.second;
    dx = (x2 - x1);
    dy = (y2 - y1);
    if (abs(dx) >= abs(dy))
        step = abs(dx);
    else
        step = abs(dy);
    dx /= step;
    dy /= step;
    x = x1;
    y = y1;
    
    if ((x1 > WIDTH && x2 > WIDTH) || 
            (y1 > HEIGHT && y2 > HEIGHT) ||
            (x1 < 0 && x2 < 0) ||
            (y1 < 0 && y2 < 0)) 
        return;
    for (int i = 0; i <= step; ++i) {
        draw_point(make_pair(x, y), color);
        x += dx;
        y += dy;
    }
    // draw_point(make_pair(x, y), color);
}

void TDM::draw_polygon4(vector <pair <float, float> > points, string color) {
    string FULL =  "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ ";
    // ----------------LOGGING----------------
    ofstream logs;
    logs.open("debug.log", fstream::app);
    // ----------------LOGGING----------------
    pair <float, float> p1, p2, p3, p4;
     logs << "TOCHKI" << endl;
    p1 = points[0];
     logs << FULL << p1.first << " " << p1.second << "<<<<<<" << endl;
    p2 = points[1];
     logs << FULL << p2.first << " " << p2.second << "<<<<<<" << endl;
    p3 = points[2];
     logs << FULL << p3.first << " " << p3.second << "<<<<<<" << endl;
    p4 = points[3];
     logs << FULL << p4.first << " " << p4.second << "<<<<<<" << endl;
    
    if (check_point(p1) && check_point(p2) &&
            check_point(p3) && check_point(p4))
        return;
    points.push_back(p1);
    // -----------------Drawing borders-----------------
    vector <pair <int, int> > borders;
    for (int j = 0; j < 4; ++j) {
        pair <float, float> point1 = points[j];
        pair <float, float> point2 = points[j + 1];
       
        float step;
        float dx = point2.first - point1.first;
        float dy = point2.second- point1.second;
        if (abs(dx) >= abs(dy))
            step = abs(dx);
        else
            step = abs(dy);

        dx /= step;
        dy /= step;
        float x = point1.first;
        float y = point1.second;
        logs << "DX " << dx << " DY " << dy << endl;
        for (int i = 0; i <= step; ++i) {
            if (!check_point(make_pair(x, y)))
                draw_point(make_pair(x, y), "Red");
            logs << " Coords: " << x << " " << y << endl;
            borders.push_back(make_pair(round(x), round(y)));
            x += dx;
            y += dy;
        }
        // logs << "X " << x << " " << point2.first << endl;
        // logs << "Y " << y << " " << point2.second << endl;
        if (!check_point(point2))
            draw_point(point2, color); 
        
    }
    logs.close();
    // ============== Calculating the middle point =============
    float k1 = (p1.second - p3.second) / (p1.first - p3.first); float k2 = (p2.second - p4.second) / (p2.first - p4.first);
    if (isnan(k1))
        k1 = 32767.0;
    if (isnan(k2))
        k2 = 32767.0;

    float b1 = (p1.second - k1 * p1.first);
    float b2 = (p2.second - k2 * p2.first);

    pair <float, float> middle;
    middle.first = (b2 - b1) / (k1 - k2);
    if (isnan(middle.first))
        middle.first = 32767;
    middle.second = k1 * middle.first + b1;
    // ======= Coloring inside of polygon with BFS algorithm =======
    vector <pair <int, int> > To_color; 
    int tkindx = 0; // index for To_color vector
    if (!check_point(middle))
        To_color.push_back(make_pair(round(middle.first), round(middle.second)));
    logs.close(); 
    while (tkindx != To_color.size()) {
        pair <int, int> point = To_color[tkindx];
        draw_point(point, "Red");

        vector <int> xes = {-1, 0, 1, 0};
        vector <int> yes = {0, -1, 0, 1};
        for (int i = 0; i < 4; ++i) {
            // logs.open("debug.log", fstream::app);
            // logs << "ПЕРЕД ДРУГИМ ФОРОМ" << point.first + xes[i] << " " << point.second + yes[i] << endl;
            // logs.close(); 
            pair <int, int> this_point (point.first + xes[i], 
                                            point.second + yes[i]);
            if (find(To_color.begin(), To_color.end(), 
                     this_point) == To_color.end() && 
                find(borders.begin(), borders.end(), 
                     this_point) == borders.end() && !check_point(this_point)) {
                    To_color.push_back(make_pair(point.first + xes[i], 
                                                 point.second + yes[i]) );
            }
        } 
        ++tkindx;
    }    
}

void TDM::fill_screen(string color) {
    window.clear();

    for (int i = 0; i < (HEIGHT / 2); ++i) {
        vector <pair <string, string>> line(WIDTH, make_pair(COLORS[color], 
                                 BGCOLORS[color]));
        window.push_back(line);
    };
}

bool TDM::check_point(pair <float, float> point) {
    if (round(point.first + WIDTH / 2) < 0 || 
            round(point.first + WIDTH / 2) >= WIDTH ||
            round(point.second + HEIGHT / 2) < 0 || 
            round(point.second + HEIGHT / 2 >= HEIGHT))
        return true;
    return false;
}
