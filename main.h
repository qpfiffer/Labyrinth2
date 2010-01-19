#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include <cstdio>
#include <string>

#include "shape.h"
using namespace std;

int initIO(SDL_Surface *screen); // Sound, video, keyboard, mouse, etc.
static void draw();
static void mainLoop();
