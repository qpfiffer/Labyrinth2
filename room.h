#ifndef _ROOM_H
#define _ROOM_H
#include "main.h"


// A sub room is what a complex multiSimple is made out of
class playerStats;
class subRoom {
public:
    subRoom();
    subRoom(playerStats *playerPassed);

    void generateRoom();
    void drawRoom();

    void GetWallDrawState(int wall);
    void SetWallDrawState(int wall, int setting);
private:
    playerStats *playerHandle;
    int numDoors;
    // Lets do doors later. First we do rooms.
    // X, Y, Z
    float dimensions[3];
    // This specifies if we should avoid drawing a wall:
    int boolWallDrawState[6];
};
class overRoom {
public:
    overRoom();
};
#endif
