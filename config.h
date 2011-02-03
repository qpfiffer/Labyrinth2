#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

class configInfo {
public:
    configInfo();      // Constructor (duh)
    
    int readConfig();  // Reads configuration file
    void printVars();  // Prints out vars for debuggings

    // "Get" functions:
    // DrawMode is an int because I hate dealing with extern.
    int getCurrentDrawMode() { return currentDrawMode; }
    int getCurrentFPS() { return fps; }
    float getMouseSense() { return mouse_sense; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    int getFullscreen() { return fullscreen; }
    int getVsync() { return vsync; }

    // "Set" functions
    void setCurrentDrawMode(int type) { currentDrawMode=type; }
private:
    int currentDrawMode;
    ifstream config;   // Config file fstream handler
    int width, height; // Screen width and height
    int fullscreen;
    int vsync;
    int fps;
    float mouse_sense;
};

class logFile {
public:
    logFile();

    int readLogFile();
    int closeLogfile();

    ofstream log;
};
#endif
