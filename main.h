#ifndef _MAIN_H_
#define _MAIN_H_
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>

enum videoDrawMode { menu, game };
class configInfo;
class subRoom;
class logFile;

class Player {
public:
    Player();
    ~Player();

    float inline getMoveSpeed() { return moveSpeed; }
    // Rotation stuff:
    float inline getXRot() { return globRot[0]; }
    float inline getYRot() { return globRot[1]; }
    float inline getZRot() { return globRot[2]; }

    void inline setXRot(float newRot) { globRot[0] = newRot; };
    void inline setYRot(float newRot) { globRot[1] = newRot; };
    void inline setZRot(float newRot) { globRot[2] = newRot; };
    // Position stuff:
    float inline getXPos() { return globPos[0]; }
    float inline getYPos() { return globPos[1]; }
    float inline getZPos() { return globPos[2]; }

    void inline setXPos(float newPos) { globPos[0] = newPos; };
    void inline setYPos(float newPos) { globPos[1] = newPos; };
    void inline setZPos(float newPos) { globPos[2] = newPos; };

private:
    float *globRot; // The camera's rotation at all times
    float *globPos; // The camera's position at all times
    float moveSpeed;  // The camera's movement speed
};

class Game {
public:
    Game();
    ~Game();

    void setCurrentDrawMode(videoDrawMode type);
    
    void draw (SDL_Surface *screen);
    void drawCurrentRoom();
    void mainLoop (SDL_Surface *screen);

    int initIO(SDL_Surface *screen);
    int setupVideo(SDL_Surface *screen);  // Communicates settings to SDL
private:
    configInfo *mInfo;
    logFile *mLogFile;
    Player *mPlayer;
    subRoom *currentRoom;
};

//string itos(int convMe);
#endif
