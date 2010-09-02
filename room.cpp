#include "room.h"
#define FLOOR 0
#define WALL1 1 // -x, +z
#define WALL2 2 // +x, +z
#define WALL3 3 // +x, -z
#define WALL4 4 // -x, -z
#define CEILING 5

// CONSTRUCTORS:
// ---------------------------
// DOOR CONTAINER CONSTRUCTORS
doorContainer::doorContainer() {
    numRealDoors = 0; // to be implimented later
    numFakeDoors = (rand() % 4 + 1); 
    fakeDoors = new door[numFakeDoors];
    int i;
    for(i=0;i<numFakeDoors;i++) {
        fakeDoors[i].x = 0;
        fakeDoors[i].texturesGenerated = false;
        fakeDoors[i].myWall = (rand() % 5 +1); // Pick a random wall
        
        string temp = "./textures/door_";
        temp+=itos((rand() % 5 + 1));
        temp+=".png";
        printf("String is: %s\n", temp);
        fakeDoors[i].fDoorTex = temp;
        // Make sure the texture handle is null:
        fakeDoors[i].fDoorTexHandle[0] = 0;
    }
}

// SUB-ROOM CONSTRUCTORS
subRoom::subRoom() {
    myGlobalCenter = new float[3];
    int i;
    for (i=0;i<6;i++) {
        if (i<3) {
            roomTextures[i] = 0;
            dimensions[i] = (float)(rand() % 10 + 2);
        }
        boolWallDrawState[i] = 1;
        myGlobalCenter[i] = 0.0f;
    }
}

subRoom::subRoom(playerStats *playerPassed) {
    playerHandle = playerPassed; // Store the player handle
    myGlobalCenter = new float[3];
    myDoors = new doorContainer;
    int i;
    for (i=0;i<6;i++) {
        if (i<3) {
            roomTextures[i] = 0;
            dimensions[i] = (float)(rand() % 10 + 2);
        }
        boolWallDrawState[i] = 1;
        myGlobalCenter[i] = 0.0f;
    }
    playerPassed->myLogFile->log<<"Room dimensions: "<<dimensions[0]<<", "<<dimensions[1]
                            <<", "<<dimensions[2]<<endl;
    playerPassed->myLogFile->log<<"Room texture values:"<<roomTextures[0]<<", "<<roomTextures[1]
                            <<", "<<roomTextures[2]<<endl;
}

overRoom::overRoom() {
}

// PUBLIC METHODS
//----------------------
// DOOR CONTAINER PUBLIC
void doorContainer::initFakeDoor(int door) {
    if (!fakeDoors[door].texturesGenerated) {
        glGenTextures(1, &(fakeDoors[door].fDoorTexHandle[0]));
        fakeDoors[door].texturesGenerated = true;
    }
    getTextureHandle(fakeDoors[door].fDoorTex.c_str(), fakeDoors[door].fDoorTexHandle);
}

void doorContainer::drawDoors(float dimensions[3]) {
    // Fake doors first
    // 1. Textured polys
    // 2. Door frame (to come later)
    int i;
    for (i=0;i<numFakeDoors;i++) {
        glPushMatrix();
        // Assume we are in the center of the room
        switch (fakeDoors[i].myWall) {
            case WALL1:
                // Move over to slightly in front of the wall
                glTranslatef((-dimensions[0]/2)+0.05f, 0, 0);
                // Move to the 0 position on that wall
                glTranslatef(0, 0, -dimensions[1]/2);
                // Move the door up so it is on the floor
                glTranslatef(0, 1, 0);
                // Move it into the correct place
                glTranslatef(0,0,(float)fakeDoors[i].x);
                // rotate it so it is facing the right way
                glRotatef(90, 0, 1, 0);
                drawVertPlane(1, 2);
                //drawPlaneTex(1, 2, fakeDoors[i].fDoorTexHandle);
                break;
            case WALL2:
                // This is WALL1 all together
                glTranslatef(dimensions[0]/2-0.05f, 1, -dimensions[2]/2);
                glTranslatef(0,0,(float)fakeDoors[i].x);
                glRotatef(90, 1,0,0);
                glRotatef(90, 0,0,1);
                drawPlaneTex(1, 2, fakeDoors[i].fDoorTexHandle);
                break;
            case WALL3:
                glTranslatef(-dimensions[0], 1, -dimensions[1]/2);
                //glTranslatef(dimensions[0]/2+0.1f, 1, -dimensions[2]/2);
                glTranslatef((float)fakeDoors[i].x,0,0);
                glRotatef(90, 1,0,0);
                glRotatef(90, 0,0,1);
                drawPlaneTex(1, 2, fakeDoors[i].fDoorTexHandle);
                break;
            case WALL4:
                glTranslatef(-dimensions[0], 1, dimensions[1]/2);
                //glTranslatef(dimensions[0]/2+0.1f, 1, dimensions[2]/2);
                glTranslatef((float)fakeDoors[i].x,0,0);
                glRotatef(90, 1,0,0);
                glRotatef(90, 0,0,1);
                drawPlaneTex(1, 2, fakeDoors[i].fDoorTexHandle);
                break;
        }
        glPopMatrix();
    }
}

// SUB-ROOM PUBLIC
void subRoom::drawRoom() {
    // COMPLEX ROOM DRAWING FUNCTION GOES HERE
    
    // Manage our doors, make sure they're setup
    int i;
    // DEBUG:
    for (i=3;i<5;i++) {
        boolWallDrawState[i] = 0;
    }
    for (i=0;i<myDoors->numFakeDoors;i++) {
        if (!myDoors->fakeDoors[i].texturesGenerated) {
            // If the door picked a wall that isnt being drawn:
            while (!boolWallDrawState[myDoors->fakeDoors[i].myWall]) {
                // This is a shitty way to do this
                myDoors->fakeDoors[i].myWall = (rand() % 2 + 1); // Pick a new wall
            }
            // Generate the texture(s)
            myDoors->initFakeDoor(i);
            // Pick where to randomly put the door:
            if (myDoors->fakeDoors[i].myWall == WALL1 ||
                myDoors->fakeDoors[i].myWall == WALL2) {
                myDoors->fakeDoors[i].x = (rand() % (int)(dimensions[1]-1) + 1);
            }

            if (myDoors->fakeDoors[i].myWall == WALL3 ||
                myDoors->fakeDoors[i].myWall == WALL4) {
                myDoors->fakeDoors[i].x = (rand() % (int)(dimensions[0]-1) + 1);
            }
            playerHandle->myLogFile->log<<"Door "<<i<<" generated at "<<myDoors->fakeDoors[i].x
                                        <<" on WALL"<<myDoors->fakeDoors[i].myWall<<endl;
            playerHandle->myLogFile->log<<"    Uses texture "<<myDoors->fakeDoors[i].fDoorTex<<endl;
        }
    }

    // Check to see if we have generated our textures yet:
    if (roomTextures[0] == 0) { // (Only check one, we do them all at once.
        glGenTextures( 3, &roomTextures[0] );
         // Prepare the texture
        getTextureHandle("./textures/dev_orange.png", &roomTextures[1]);
        // Because I've got nothing else to use:
        getTextureHandle("./textures/blacktop.png", &roomTextures[0]);
        getTextureHandle("./textures/face.png", &roomTextures[2]);
        printf("GLError: %i\n", glGetError());
    }
    
    // Make sure we are where we are supposed to be:
    glTranslatef(myGlobalCenter[0], myGlobalCenter[1], myGlobalCenter[2]);

    // Draw some fake doors:
    myDoors->drawDoors(dimensions);
    
    // Start with the floor
    if (boolWallDrawState[FLOOR]) {
        glPushMatrix();
        //glColor3f((float)1/(rand()%255), (float)1/(rand()%255), (float)1/(rand()%255));
        if (roomTextures[0] != -1) {
            drawPlaneTex(dimensions[0], dimensions[1], &roomTextures[0]);
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
            drawPlaneTex(dimensions[1], dimensions[2], &roomTextures[1]);
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
            drawPlaneTex(dimensions[1], dimensions[2], &roomTextures[1]);
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
            drawPlaneTex(dimensions[0], dimensions[2], &roomTextures[1]);
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
            drawPlaneTex(dimensions[0], dimensions[2], &roomTextures[1]);
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
            drawPlaneTex(dimensions[0], dimensions[1], &roomTextures[2]);
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
    /*if (myGlobalCenter) {
        delete [] myGlobalCenter;
        myGlobalCenter = 0;
    }*/
    //delete myDoors;
}

doorContainer::~doorContainer() {
    /*delete [] fakeDoors;
    fakeDoors = 0;
    delete [] realDoors;
    realDoors = 0;*/
}