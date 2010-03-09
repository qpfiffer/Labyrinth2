#include "SDL.h"
#include "SDL_opengl.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

#include "shape.h"
using namespace std;

class configInfo {
 public:
  configInfo();      // Constructor (duh)
  int readConfig();  // Reads configuration file
  int setupVideo(SDL_Surface *screen);  // Communicates settings to SDL
  void printVars();  // Prints out vars for debuggings
 private:
  ifstream config;   // Config file fstream handler
  int width, height; // Screen width and height
  int fullscreen;
  int vsync;
  int fps;
};

class playerStats: public configInfo {
 public:
  playerStats();
  float globRot[3]; // The camera's rotation at all times
  float globPos[3]; // The camera's position at all times
  float moveSpeed;  // The camera's movement speed
};

int initIO(SDL_Surface *screen, playerStats *mainPlayerObj); // Sound, video, keyboard, mouse, etc.
static void draw(playerStats *mainPlayerObj);
static void mainLoop(playerStats *mainPlayerObj);
