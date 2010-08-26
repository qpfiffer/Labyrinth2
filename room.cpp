#include "room.h"
#define FLOOR 0
#define WALL1 0
#define WALL2 0
#define WALL3 0
#define WALL4 0
#define CEILING 0

// CONSTRUCTORS
subRoom::subRoom() {
    numDoors = rand() % 6 + 2;
    int i;
    for (i=0;i<6;i++) {
        if (i<3) {
            dimensions[i] = rand() % 10 + 1;
        }
        boolWallDrawState[i] = 1;
    }
}

subRoom::subRoom(playerStats *playerPassed) {
    playerHandle = playerPassed; // Store the player handle
    numDoors = rand() % 6 + 2;
    int i;
    for (i=0;i<6;i++) {
        if (i<3) {
            dimensions[i] = rand() % 10 + 1;
        }
        boolWallDrawState[i] = 1;
    }
    playerPassed->myLogFile->log<<"Room dimensions: "<<dimensions[0]<<dimensions[2]
                            <<dimensions[1]<<endl;
}
//---
overRoom::overRoom() {
}
//---
// PUBLIC METHODS
void subRoom::generateRoom() {
}

void subRoom::drawRoom() {
    // Start with the floor
    if (boolWallDrawState[FLOOR])
        drawPlane(dimensions[0], dimensions[1]);
    if (boolWallDrawState[CEILING]) {
        glPushMatrix();
        glTranslatef(0,dimensions[2], 0);
        drawPlane(dimensions[0], dimensions[1]);
        glPopMatrix();
    }
}