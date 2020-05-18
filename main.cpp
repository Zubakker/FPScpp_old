#include <iostream>
#include "tdm.h"
#include "camera.h"
#include "wall.h"
#include <SDL2/SDL.h>
#include <fstream>
#include <vector>

using namespace std;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 250;
int SCREEN_X = 1100;
int SCREEN_Y = 10;
SDL_Window* gWindow;
SDL_Surface* gScreenSurface;
vector <bool> KEYS = {0,0,0,0,0,0,0,0};
int KEY_W = 0;
int KEY_A = 1;
int KEY_S = 2;
int KEY_D = 3;
int KEY_UP = 4;
int KEY_LEFT = 5;
int KEY_RIGHT = 6;
int KEY_DOWN = 7;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SCREEN_X, SCREEN_Y, 
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
};

void close() {
    //Deallocate surface
    SDL_FreeSurface( gScreenSurface );
    gScreenSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
};

int main(int argc, char* argv[]) {
    if ( !init() ) {
        cout << "~FAILED TO INIT\n";
        close();
        return 0;
    }
    SDL_SetWindowGrab( gWindow, SDL_TRUE );
    SDL_SetRelativeMouseMode( SDL_TRUE );
    
    TDM screen(114, 70);
    int len;
    ifstream input("walls.txt");
    input >> len;
    vector <Wall> WALLS;
    for (int i = 0; i < len; ++i) {
        vector <vector <float> > points;
        float x, y, z;
        for (int j = 0; j < 4; ++j) {
            input >> x >> y >> z;
            vector <float> point = {x, y, z};
            points.push_back(point);
        }
        string color;
        input >> color;
        Wall wall(points, color);
        WALLS.push_back(wall);
    }
    Camera PLAYER(0, 0, 30, &screen);
    vector <Wall> printable;

    // Main loop flag & event handler
    bool quit = false;
    SDL_Event e;
    
    // While application is running
    ofstream logs;
    logs.open("debug.log", fstream::app);
    int N = 0;
    while( !quit ) {
        N++;
        screen.fill_screen("Yellow");
        printable = PLAYER.sort_walls(WALLS);
        cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ N " << N << endl;
        PLAYER.render(printable);
        // logs << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ M> " << N << endl;
        screen.window_render();
        cout << "ANGLES " << PLAYER.view_angles.first << " " << PLAYER.view_angles.second << endl;
        if (KEYS[0] + KEYS[1] + KEYS[2] + KEYS[3] == 2) {
            float forward = 0.7 * KEYS[KEY_UP] - 0.7 * KEYS[KEY_DOWN];
            float right = 0.7 * KEYS[KEY_RIGHT] - 0.7 * KEYS[KEY_LEFT];
            PLAYER.move(forward, right, 0);
        } 
        else if (KEYS[KEY_UP])
            PLAYER.move(1, 0, 0);
        else if (KEYS[KEY_DOWN])
            PLAYER.move(-1, 0, 0);
        else if (KEYS[KEY_RIGHT])
            PLAYER.move(0, 1, 0);
        else if (KEYS[KEY_LEFT])
            PLAYER.move(0, -1, 0);

        while( SDL_PollEvent( &e ) != 0 ) {
	    if( e.type == SDL_QUIT ) {
	        quit = true;
	    }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
                    KEYS[KEY_UP] = true;
                if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
                    KEYS[KEY_LEFT] = true;
                if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
                    KEYS[KEY_RIGHT] = true;
                if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
                    KEYS[KEY_DOWN] = true;
            }
            if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
                    KEYS[KEY_UP] = false;
                if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
                    KEYS[KEY_LEFT] = false;
                if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
                    KEYS[KEY_RIGHT] = false;
                if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
                    KEYS[KEY_DOWN] = false;
            }
            if (e.type == SDL_MOUSEMOTION) {
                float DEG = 0.00175;
                PLAYER.rotate_h(e.motion.xrel * DEG);
                PLAYER.rotate_v(e.motion.yrel * DEG);
            }
        }
    }
}
