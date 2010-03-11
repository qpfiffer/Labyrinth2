#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "SDL.h"
#include "SDL_opengl.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

enum videoDrawMode { menu, game };

class configInfo {
 public:
  configInfo();      // Constructor (duh)
  int readConfig();  // Reads configuration file
  int setupVideo(SDL_Surface *screen);  // Communicates settings to SDL
  void printVars();  // Prints out vars for debuggings
  const void changeCurrentDrawMode(videoDrawMode type); // change the current draw mode
  const videoDrawMode getCurrentDrawMode();
  const int getCurrentFPS();
 private:
  videoDrawMode currentDrawMode;
  ifstream config;   // Config file fstream handler
  int width, height; // Screen width and height
  int fullscreen;
  int vsync;
  int fps;
};
#endif
