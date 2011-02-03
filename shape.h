#ifndef _SHAPE_H_
#define _SHAPE_H
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

int getTextureHandle(const char *name, GLuint *texture);

void drawPlaneTex(float x, float y, GLuint *texture, float repeatx, float repeaty);
void drawVertPlaneTex(float x, float y, GLuint *texture, float repeatx, float repeaty);
void drawPlane(float x, float y);
void drawVertPlane(float x, float y);

void drawCube(float x, float y, float z);
void inline drawface();
#endif
