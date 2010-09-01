#ifndef _ROOM_H
#define _ROOM_H
#include "main.h"

// Wu-tang clan ain't nothin t'fuck with
class playerStats;

struct door {
    int x;
    int y;
    int myWall;
    // Fake doors:
    char *fDoorTex;
    GLuint fDoorTexHandle[1];
    // Real doors:
    // ---
    // CODE GOES HERE
    // ---
};

class doorContainer {
public:
    doorContainer();
    ~doorContainer();

    int numRealDoors;
    int numFakeDoors;

    void initFakeDoor(int door);
    
    // Dynamic arrays:
    door *realDoors;
    door *fakeDoors;
};

class subRoom {
public:
    subRoom();
    subRoom(playerStats *playerPassed);
    ~subRoom();

    void createChildRoom();
    void drawRoom();

    int GetWallDrawState(int wall);
    void SetWallDrawState(int wall, int setting);

    float *GetGlobalCenter();
    void SetGlobalCenter(float *newGlobalCenter); // Is an array better?
private:
    float *myGlobalCenter; // X, Y, Z offset of the current room
    playerStats *playerHandle;
    doorContainer *myDoors;
    // Lets do doors later. First we do rooms.
    // X, Y, Z
    float dimensions[3];
    // This specifies if we should avoid drawing a wall:
    int boolWallDrawState[6];
    // Holds handles to textures that the room uses.
    // (floor, wall and ceiling)
    GLuint roomTextures[3];
};

class overRoom {
public:
    overRoom();
};
#endif
