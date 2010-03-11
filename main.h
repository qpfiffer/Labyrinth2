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
#include <ctime>

#include "shape.h"
#include "config.h"
using namespace std;

class playerStats: public configInfo {
 public:
  playerStats();
  float globRot[3]; // The camera's rotation at all times
  float globPos[3]; // The camera's position at all times
  float moveSpeed;  // The camera's movement speed
};

int initIO(SDL_Surface *screen, playerStats *mainPlayerObj); // Sound, video, keyboard, mouse, etc.
static void draw(SDL_Surface *screen, playerStats *mainPlayerObj);
static void mainLoop(SDL_Surface *screen, playerStats *mainPlayerObj);
