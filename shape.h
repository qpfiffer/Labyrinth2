#ifndef _SHAPE_H_
#define _SHAPE_H
#include "SDL.h"
#include "SDL_opengl.h"
#include <cstdio>
#include <cstdlib>

void drawface();
void drawPlane(float x, float y);
void drawVertPlane(float x, float y);
void drawCube(float x, float y, float z);
#endif
