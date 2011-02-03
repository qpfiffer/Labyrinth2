#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

class configInfo {
public:
    configInfo();      // Constructor (duh)
    ~configInfo();

    int readConfig();  // Reads configuration file
    std::string getStrVars();  // Prints out vars for debuggings

    // "Get" functions:
    // DrawMode is an int because I hate dealing with extern.
    int getCurrentFPS() { return fps; }
    int getCurrentDrawMode() { return currentDrawMode; }
    float getMouseSense() { return mouse_sense; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    int getFullscreen() { return fullscreen; }
    int getVsync() { return vsync; }

    // "Set" functions
    void setCurrentDrawMode(int type) { currentDrawMode=type; }
private:
    int currentDrawMode;
    ifstream *config;   // Config file fstream handler
    int width, height; // Screen width and height
    int fullscreen;
    int vsync;
    int fps;
    float mouse_sense;
};

class logFile {
public:
    logFile();
	~logFile();

    void Log(std::string text);
    void Warning(std::string text);
    void Error(std::string text);

private:
    ofstream log;
};
#endif
