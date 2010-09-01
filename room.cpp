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
        //fakeDoors[i].y = 0;
        fakeDoors[i].myWall = (rand() % 4 +1); // Pick a random wall
        // TODO: write a nice little random door chooser
        // here with sprintf. e.g. door_(rand).png
        fakeDoors[i].fDoorTex = "./textures/door_1.png";
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
    glGenTextures(1, &(fakeDoors[door].fDoorTexHandle[0]));
    getTextureHandle(fakeDoors[door].fDoorTex, fakeDoors[door].fDoorTexHandle);
}

// SUB-ROOM PUBLIC
void subRoom::drawRoom() {
    // COMPLEX ROOM DRAWING FUNCTION GOES HERE

    // Manage our doors, make sure they're setup
    int i;
    for (i=0;i<myDoors->numFakeDoors;i++) {
        if (myDoors->fakeDoors[i].fDoorTexHandle == 0) {
            // If the door picked a wall that isnt being drawn:
            while (!boolWallDrawState[myDoors->fakeDoors[i].myWall]) {
                // This is a shitty way to do this
                myDoors->fakeDoors[i].myWall = (rand() % 6); // Pick a new wall
            }
            // Generate the texture(s)
            myDoors->initFakeDoor(i);
            // Pick where to randomly put the door:
            if (myDoors->fakeDoors[i].myWall == WALL1 ||
                myDoors->fakeDoors[i].myWall == WALL2) {
                myDoors->fakeDoors[i].x = (rand() % (int)dimensions[1] + 1);
            }

            if (myDoors->fakeDoors[i].myWall == WALL3 ||
                myDoors->fakeDoors[i].myWall == WALL4) {
                myDoors->fakeDoors[i].x = (rand() % (int)dimensions[0] + 1);
            }
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
    delete myDoors;
}

doorContainer::~doorContainer() {
    delete [] fakeDoors;
    fakeDoors = 0;
    delete [] realDoors;
    realDoors = 0;
}