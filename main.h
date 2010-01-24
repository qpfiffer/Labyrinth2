#include "SDL.h"
#include "SDL_opengl.h"

#include <iostream>
#include <cstdio>
#include <string>

#include "shape.h"
using namespace std;

class playerStats {
 public:
  playerStats();
  float globRot[3]; // The camera's rotation at all times
  float globPos[3]; // The camera's position at all times
  float moveSpeed;         // The camera's movement speed
};

int initIO(SDL_Surface *screen); // Sound, video, keyboard, mouse, etc.
static void draw(playerStats *mainPlayerObj);
static void mainLoop(playerStats *mainPlayerObj);
