#include "room.h"
#define FLOOR 0
#define WALL1 1 // -x, +z
#define WALL2 2 // +x, +z
#define WALL3 3 // +x, -z
#define WALL4 4 // -x, -z
#define CEILING 5

// CONSTRUCTORS
// We probably shouldn't be calling the default constructor
subRoom::subRoom() {
    myGlobalCenter = new float[3];
    numDoors = rand() % 6 + 2;
    int i;
    for (i=0;i<6;i++) {
        if (i<3) {
            dimensions[i] = (float)(rand() % 10 + 2);
        }
        boolWallDrawState[i] = 1;
        myGlobalCenter[i] = 0.0f;
    }
    roomTextures[0] = getTextureHandle("./textures/dev_orange.png");
    // Because I've got nothing else to use:
    roomTextures[1] = getTextureHandle("./textures/blacktop.png");
    roomTextures[2] = getTextureHandle("./textures/face.png");
}

subRoom::subRoom(playerStats *playerPassed) {
    playerHandle = playerPassed; // Store the player handle
    myGlobalCenter = new float[3];
    numDoors = rand() % 6 + 2;
    int i;
    for (i=0;i<6;i++) {
        if (i<3) {
            dimensions[i] = (float)(rand() % 10 + 2);
        }
        boolWallDrawState[i] = 1;
        myGlobalCenter[i] = 0.0f;
    }
    roomTextures[0] = getTextureHandle("./textures/dev_orange.png");
    // Because I've got nothing else to use:
    roomTextures[1] = getTextureHandle("./textures/blacktop.png");
    roomTextures[2] = getTextureHandle("./textures/face.png");
    playerPassed->myLogFile->log<<"Room dimensions: "<<dimensions[0]<<", "<<dimensions[1]
                            <<", "<<dimensions[2]<<endl;
    playerPassed->myLogFile->log<<"Room texture values:"<<roomTextures[0]<<", "<<roomTextures[1]
                            <<", "<<roomTextures[2]<<endl;
}
//---
overRoom::overRoom() {
}
//---
// PUBLIC METHODS
//Will come back to this. Should work on overRooms first.
/*
void subRoom::createChildRoom() {
    subRoom *pHandle;
    int i=0;
    // Iterate through our list of child rooms until
    // we get a free one
    while (pHandle == NULL && i < 6) {
        pHandle = childRoom[i];
        i++;
    }
    if (i == 6) {
        // DESTROY OLD CHILD
        // CLOSE DOOR
        // TAKE SPOT
        pHandle = childRoom

}*/

void subRoom::drawRoom() {
    // Make sure we are where we are supposed to be:
    glTranslatef(myGlobalCenter[0], myGlobalCenter[1], myGlobalCenter[2]);
    /*
    dimensions[0] = 3;
    dimensions[1] = 8;
    dimensions[2] = 3;
    */
    // Start with the floor
    if (boolWallDrawState[FLOOR]) {
        glPushMatrix();
        //glColor3f((float)1/(rand()%255), (float)1/(rand()%255), (float)1/(rand()%255));
        if (roomTextures[0] != -1) {
            drawPlaneTex(dimensions[0], dimensions[1], roomTextures[0]);
        } else {
            glColor3f(1.0f, 0, 1.0f);
            drawPlane(dimensions[0], dimensions[1]);
        }
        glPopMatrix();
    }
    
    // Walls will be drawn clockwise starting with the left
    // -, +
    if (boolWallDrawState[WALL1]) {
        glPushMatrix(); // SO USEFUL I LOVE YOU
        glTranslatef(-dimensions[0]/2, dimensions[2]/2, 0);
        glRotatef(90, 1,0,0);
        glRotatef(90, 0,0,1);
        if (roomTextures[1] != -1) {
            drawPlaneTex(dimensions[1], dimensions[2], roomTextures[1]);
        } else {
            glColor3f(1.0f, 0, 0.25f);
            drawPlane(dimensions[1], dimensions[2]);
        }
        glPopMatrix();
    }
    //+, +
    if (boolWallDrawState[WALL2]) {
        glPushMatrix(); // SO USEFUL I LOVE YOU
        
        glTranslatef(dimensions[0]/2, dimensions[2]/2, 0);
        glRotatef(90, 1,0,0);
        glRotatef(90, 0,0,1);
        if (roomTextures[1] != -1) {
            drawPlaneTex(dimensions[1], dimensions[2], roomTextures[1]);
        } else {
            glColor3f(1.0f, 0, 0.25f);
            drawPlane(dimensions[1], dimensions[2]);
        }
        glPopMatrix();
    }
    //+, -
    if (boolWallDrawState[WALL3]) {
        glPushMatrix(); // SO USEFUL I LOVE YOU
        
        glTranslatef(0, dimensions[2]/2, -dimensions[1]/2);
        glRotatef(90, 1,0,0);
        if (roomTextures[1] != -1) {
            drawPlaneTex(dimensions[0], dimensions[2], roomTextures[1]);
        } else {
            glColor3f(0, 1.0f, 0.25f);
            drawPlane(dimensions[0], dimensions[2]);
        }

        glPopMatrix();
    }
    // -, -
    if (boolWallDrawState[WALL4]) {
        glPushMatrix(); // SO USEFUL I LOVE YOU
        
        glTranslatef(0, dimensions[2]/2, dimensions[1]/2);
        glRotatef(90, 1,0,0);
        if (roomTextures[1] != -1) {
            drawPlaneTex(dimensions[0], dimensions[2], roomTextures[1]);
        } else {
            glColor3f(0, 1.0f, 0.25f);
            drawPlane(dimensions[0], dimensions[2]);
        }
        glPopMatrix();
    }

    if (boolWallDrawState[CEILING]) {
        glPushMatrix();
        
        glTranslatef(0,dimensions[2], 0);
        if (roomTextures[2] != -1) {
            drawPlaneTex(dimensions[0], dimensions[1], roomTextures[2]);
        } else {
            glColor3f(0.5f, 0.75f, 0);
            drawPlane(dimensions[0], dimensions[1]);
        }
        glPopMatrix();
    }
}

int subRoom::GetWallDrawState(int wall) {
    return boolWallDrawState[wall];
}

void subRoom::SetWallDrawState(int wall, int setting) {
    if (setting != 0 && setting != 1) {
        // Fail silently
        return;
    } else {
        boolWallDrawState[wall] = setting;
        return;
    }
}

float *subRoom::GetGlobalCenter() {
    return myGlobalCenter;
}

void subRoom::SetGlobalCenter(float *newGlobalCenter) {
    myGlobalCenter = newGlobalCenter;
}

// DECONSTRUCTORS
subRoom::~subRoom() {
    delete [] myGlobalCenter;
}