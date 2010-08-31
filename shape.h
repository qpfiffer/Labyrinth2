#ifndef _SHAPE_H_
#define _SHAPE_H
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_Image.h"
#include <cstdio>
#include <cstdlib>
#include <string>

GLuint getTextureHandle(const char *name);
void drawface();

void drawPlaneTex(float x, float y, GLuint texture);
void drawPlane(float x, float y);

void drawVertPlane(float x, float y);
void drawCube(float x, float y, float z);
#endif
