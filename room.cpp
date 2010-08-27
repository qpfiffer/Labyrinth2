#include "room.h"
#define FLOOR 0
#define WALL1 0 // -x, +z
#define WALL2 0 // +x, +z
#define WALL3 0 // +x, -z
#define WALL4 0 // -x, -z
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
    if (boolWallDrawState[FLOOR]) {
        glPushMatrix();
        //glColor3f((float)1/(rand()%255), (float)1/(rand()%255), (float)1/(rand()%255));
        glColor3f(1.0f, 0, 1.0f);
        drawPlane(dimensions[0], dimensions[1]);
        glPopMatrix();
    }
    
    // Walls will be drawn clockwise starting with the left
    // -, +
    if (boolWallDrawState[WALL1]) {
        glPushMatrix(); // SO USEFUL I LOVE YOU
        glColor3f(0, 1.0f, 0.25f);
        glTranslatef(-dimensions[0]/2, dimensions[2]/2, 0);
        glRotatef(90, 1,0,0);
        glRotatef(90, 0,0,1);
        drawPlane(dimensions[0], dimensions[2]);
        glPopMatrix();
    }
    //+, +
    if (boolWallDrawState[WALL2]) {
        glPushMatrix(); // SO USEFUL I LOVE YOU
        glColor3f(0, 1.0f, 0.25f);
        glTranslatef(dimensions[0]/2, dimensions[2]/2, 0);
        glRotatef(90, 1,0,0);
        glRotatef(90, 0,0,1);
        drawPlane(dimensions[0], dimensions[2]);
        glPopMatrix();
    }
    //+, -
    if (boolWallDrawState[WALL3]) {
        glPushMatrix(); // SO USEFUL I LOVE YOU
        glColor3f(0, 1.0f, 0.25f);
        glTranslatef(0, dimensions[2]/2, -dimensions[1]/2);
        glRotatef(90, 1,0,0);
        drawPlane(dimensions[0], dimensions[2]);
        glPopMatrix();
    }
    // -, -
    if (boolWallDrawState[WALL4]) {
        glPushMatrix(); // SO USEFUL I LOVE YOU
        glColor3f(0, 1.0f, 0.25f);
        glTranslatef(0, dimensions[2]/2, dimensions[1]/2);
        glRotatef(90, 1,0,0);
        drawPlane(dimensions[0], dimensions[2]);
        glPopMatrix();
    }

    if (boolWallDrawState[CEILING]) {
        glPushMatrix();
        glColor3f(0.5f, 0.75f, 0);
        glTranslatef(0,dimensions[2], 0);
        drawPlane(dimensions[0], dimensions[1]);
        glPopMatrix();
    }
}