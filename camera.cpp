#include "camera.h"


Camera::Camera(float X, float Y, float Z, TDM* window) {
    position.push_back(X);
    position.push_back(Y); // X, Y and Z of camera;
    position.push_back(Z);

    view_angles = make_pair(0.0, 0.0);      
    screen = window;
}

void Camera::rotate_h(float angle) {
    view_angles.first += angle;
    if (view_angles.first > M_PI)
        view_angles.first -= D_PI;
    else if (view_angles.first < -M_PI)
        view_angles.first += D_PI;
}

void Camera::rotate_v(float angle) {
    view_angles.second += angle;
    if (view_angles.second > H_PI)
        view_angles.second = H_PI;
    else if (view_angles.second < -H_PI)
        view_angles.second = -H_PI;
}


void Camera::move(float forward, float right, float up) {
    position[0] += forward * cos(view_angles.first) + \
        right * sin(view_angles.first);
    position[1] += forward * sin(view_angles.first) + \
        right * cos(view_angles.first);
    position[2] += up;
}


void Camera::render(vector <Wall> printable) {
    /* This function gets a vector of Walls that are sorted 
       by their distance to Camera position.
       Walls that are too far for them to be 
       displayed are not in this vector
    */
    // ====== LOGGING ======
    ofstream logs;
    logs.open("camera.log", fstream::app);
    // ====== LOGGING ======
    string FULLLINE = "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ ";
    float cx = position[0];
    float cy = position[1];
    float cz = position[2];
    for (auto& wall : printable) {
        vector <pair <float, float> > PRINT;
        for (auto& point : wall.points) {
             float x = point[0];
             float y = point[1];
             float z = point[2];

             // here I convert a 3D point to a 2D point

             
             float h_angle = atan2(x - cx, y - cy) - view_angles.first;
             float dx = tan(h_angle / 2) * SCREEN_DIST;
             if (h_angle > M_PI)
                 dx = 1000;
             if (h_angle < -M_PI)
                 dx = -1000;
             float v_angle = atan2(y - cy, z - cz) - view_angles.second - H_PI;
             float dy = tan(v_angle / 2) * SCREEN_DIST;
             if (v_angle > M_PI)
                 dy = 1000;
             if (v_angle < -M_PI)
                 dy = -1000;
             logs << "H ANGLE " << h_angle << " V ANGLE " << v_angle << endl;
             logs << "DX DY " << dx << " " << dy << endl;
             logs << " ======== " << endl;
             PRINT.push_back(make_pair(dx, dy));
        } 
        logs.close();
        if (calculate_distance(wall) < 6000)
                                    // ^this value is temporaty and will be changed
            screen -> draw_polygon4(PRINT, "Bright " + wall.COLOR); 
        else
            screen -> draw_polygon4(PRINT, wall.COLOR); 
    }
}


float Camera::calculate_distance(Wall wall) {
    /* The method I use to calc distance:
       variable function in class Wall is
       is a vector of A, B, C and D needed to define a 3D plane
       then I use some mathimatics formule to calculate distance 
    */
    float A = wall.function[0];
    float B = wall.function[1];
    float C = wall.function[2];
    float D = wall.function[3];

    float x = position[0];
    float y = position[1];
    float z = position[2];

    float DIST = abs(A*x + B*y + C*z + D) / sqrt(A*A + B*B + C*C);
    // cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ DIST" << DIST << endl;
    if (isnan(DIST))
        DIST = 99999999999999999999.0;

    return DIST;
}


vector <Wall> Camera::sort_walls(vector <Wall> to_sort) {
    vector <Wall> sorting;
    for (auto& wall : to_sort) {
        float dist = calculate_distance(wall);
        if (dist < 10000) {
            wall.distance = dist;
            sorting.push_back(wall);
        }
    }
    for (int i = 0; i < sorting.size(); ++i) {
        for (int j = i; j < sorting.size() - 1; ++j) {
            if (sorting[j].distance < sorting[j+1].distance) {
                Wall prowall = sorting[j];
                sorting[j] = sorting[j+1];
                sorting[j+1] = prowall;  
            }
        }
    }
    return sorting;
}
