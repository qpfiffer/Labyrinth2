#ifndef _SHAPE_H_
#define _SHAPE_H
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

class Graphics {
public:
	int getTextureHandle(const char *name, GLuint *texture);

	void drawPlaneTex(float x, float y, GLuint *texture, float repeatx, float repeaty);
	void drawVertPlaneTex(float x, float y, GLuint *texture, float repeatx, float repeaty);
	void drawPlane(float x, float y);
	void drawVertPlane(float x, float y);

	void drawCube(float x, float y, float z);
	void drawFace();
};
#endif
