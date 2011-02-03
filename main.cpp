#include "main.h"
#include "shape.h"
#include "config.h"
#include "world.h"
#include "room.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

// VC2k10 memory leak checking
#ifdef _DEBUG
#include <ostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

//string itos(int convMe) {
//    string converted;
//    stringstream out;
//    out<<convMe;
//    converted = out.str();
//    return converted;
//}
// Constructors:
Player::Player(): globRot(new float[3]),
    globPos(new float[3]), moveSpeed(0.05f){
    int i;
    for (i=0; i<3; i++) {
        globRot[i]=0;
        if (i==1) {
            globPos[i]=-2;
        } else {
            globPos[i]=0;
        }
    }
}

Player::~Player() {
    delete []globRot;
    delete []globPos;
}

Game::Game(): mInfo(new configInfo), mLogFile(new logFile), 
    mPlayer(new Player), currentRoom(new subRoom(mLogFile)) {
}

Game::~Game() {
    delete mInfo;
    delete mLogFile;
    delete mPlayer;
    delete currentRoom;
}

int Game::initIO(SDL_Surface *screen) {
    // Read in data from config file:
    mInfo->readConfig();
    if (setupVideo(screen) == 1)
        return 1;

    mLogFile->Log(mInfo->getStrVars());
    // Keyboard/mouse:
    return 0;
}

int Game::setupVideo(SDL_Surface *screen) {
    // Setting up video:
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to init video: %s\n", SDL_GetError());
        return 1;
    }

    const SDL_VideoInfo *vidInfo = SDL_GetVideoInfo();
    if (mInfo->getFullscreen() == 1 && mInfo->getCurrentDrawMode() == game) {
		//cout<<"Called on 1"<<endl;
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        screen = SDL_SetVideoMode(mInfo->getWidth(), mInfo->getHeight(), 16, SDL_OPENGL | SDL_FULLSCREEN);
	}
    else if (mInfo->getFullscreen() == 0 && mInfo->getCurrentDrawMode() == game) {
		//cout<<"Called on 2"<<endl;
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        screen = SDL_SetVideoMode(mInfo->getWidth(), mInfo->getHeight(), 16, SDL_OPENGL);
	}
	else if (mInfo->getCurrentDrawMode() == menu) {
		//cout<<"Called on 3"<<endl;
		screen = SDL_SetVideoMode(mInfo->getWidth(), mInfo->getHeight(), 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	}
	if (screen == NULL)
		cout<<"Unable to setup SDL_Surface."<<endl;

    std::stringstream tempSS;
    vidInfo = SDL_GetVideoInfo(); // Call it again because we changed current_w and current_h
	tempSS<<"From SDL_Surface pointer: Width: "<<screen->w<<" Height: "<<screen->h<<endl;
	tempSS<<"From VideoInfo: Screen w: "<<(int)vidInfo->current_w
		  <<" Screen h: "<<(int)vidInfo->current_h<<endl;
	mLogFile->Log(tempSS.str());
	
    if (mInfo->getCurrentDrawMode() == game) {
        // OpenGL init:
        glEnable(GL_TEXTURE_2D); // Enable 2D textures
        glShadeModel(GL_SMOOTH);
        glViewport(0, 0, vidInfo->current_w, vidInfo->current_h);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION); // Load the Porjection matrix (camera stuff, basically)
        glLoadIdentity(); // Reset that matrix
        float aspect = (float)vidInfo->current_w / (float)vidInfo->current_h; // The aspect ratio
        gluPerspective(50.0, aspect, 0.1, 100.0); //
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        glMatrixMode(GL_MODELVIEW); // Switch back to the good 'ole modelview matrix
        glEnable(GL_DEPTH_TEST); //Not sure why we want this enabled
        glDepthFunc(GL_LEQUAL);  // This has to to with the above
        glDisable(GL_CULL_FACE); //Draw front AND back of polygons

        // AA
        /*GLfloat values[2];
        glGetFloatv (GL_LINE_WIDTH_GRANULARITY, values);
        glGetFloatv (GL_LINE_WIDTH_RANGE, values);
        glEnable (GL_POLYGON_SMOOTH);
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
        glLineWidth (1.5); */
        // End AA

        glLoadIdentity(); // Blank GL_MODELVIEW
	    SDL_ShowCursor(SDL_DISABLE); // Hide the mouse cursor
    	SDL_WM_GrabInput(SDL_GRAB_ON); //Makes it so mouse events happen outside of the screen.
        SDL_WM_SetCaption("Labyrinth THREE","Labyrinth THREE");
        // ---
    }
    return 0;

}

void Game::drawCurrentRoom() {
    currentRoom->drawRoom();
}

void Game::draw (SDL_Surface *screen) {   
	if (mInfo->getCurrentDrawMode() == game) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity(); // Clear modelview for good measure. THAT'LL SHOW THAT GUY
        glClearColor(1.0f,1.0f,1.0f,1.0f); // Set the default fill to yellow
        glColor3f(1.0f, 1.0f, 1.0f); // Make sure our color is set to white
		// Mouse rotation stuff:
        // This little loop breaks everything after a little while. I wouldn't enable it.
        // NEW NOTE: Consider using modulo here, if it becomes a problem.
		/*while (1) {
          if (mainPlayerObj->globRot[0] > 360)
            mainPlayerObj->globRot[0]-=360;
          if (mainPlayerObj->globRot[1] > 360)
            mainPlayerObj->globRot[1]-=360;
          if (mainPlayerObj->globRot[0] < 360 &&
          mainPlayerObj->globRot[1] < 360)
            break;
            }*/
        glRotatef(mPlayer->getXRot(), 1, 0, 0);
        glRotatef(mPlayer->getYRot(), 0, 1, 0);
        // Global movement:
        glTranslatef(mPlayer->getXPos(), mPlayer->getYPos(), mPlayer->getZPos());
        //cout<<"globRot[0]="<<mainPlayerObj->globRot[0]<<", globRot[1]="<<mainPlayerObj->globRot[1]<<endl;
        // Draw the current room:
		drawCurrentRoom();

		Graphics tempG;
		tempG.drawFace();
	
        SDL_GL_SwapBuffers();
    } else {
        // Render a PNG. Temporary.
        SDL_Surface *image, *temp;
        temp = IMG_Load("textures/main_menu_top.png");
        if (temp == NULL) {
            printf("Unable to load image: %s\n", SDL_GetError());
            exit(1);
        }
        image = SDL_DisplayFormatAlpha(temp);
        SDL_FreeSurface(temp);

        SDL_Rect src, dest;

        src.x = 0;
        src.y = 0;
        src.w = image->w;
        src.h = image->h;
		
		// Put it in the middle of the page
		int placement = (SDL_GetVideoSurface()->w - image->w)/2;
		if (placement >= 0)
        	dest.x = placement; 
		else
			dest.x = 0;        
		dest.y = 0;
		
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 130, 70, 220));		
		//cout<<"Screen w: "<<screen->w<<" Screen h:"<<screen->h<<endl;
		// "Only the x and y in destRect are used, w and h are ignored."
        if (SDL_BlitSurface(image, NULL, SDL_GetVideoSurface(), &dest) == -1)
			cout<<"Something went wrong with blitsurface."<<endl;
		
		temp = IMG_Load("textures/menu.png");
        if (temp == NULL) {
            printf("Unable to load image: %s\n", SDL_GetError());
            exit(1);
        }
		SDL_FreeSurface(image);
		image = SDL_DisplayFormatAlpha(temp);
		
		src.w = 227;
		src.h = image->h;

		placement = SDL_GetVideoSurface()->w/2 - image->w/4; // woo woo
        dest.x = placement; // Until we implement scaling, this will center justify the image      
		dest.y = SDL_GetVideoSurface()->h - image->h;
		
        if (SDL_BlitSurface(image, &src, SDL_GetVideoSurface(), &dest) == -1)
			cout<<"Something went wrong with blitsurface."<<endl;
        SDL_Flip(screen);
        //SDL_Delay(2500);

        SDL_FreeSurface(image);
    }
}

void Game::mainLoop (SDL_Surface *screen) {
    SDL_Event event;
    bool QUIT_FLAG = false;
    float frnt_back=0, lft_rht=0; // Flags for movement
    float xrotrad=0.0f, yrotrad=0.0f; // For movement
    // For fixing the timestep:
    clock_t currentTime, newTime, deltaTime;
    currentTime=clock(); // Set current time to... the current time.
    clock_t accumulator = 0;
    // To get the desired framerate (60), we divide 1 by that number. 1/60 = 60 FPS

    while (1) {
        // MORE TIMESTEPPING NONSENSE!
        newTime=clock(); // Set new time as the currentTime (as of this loop)
        deltaTime = newTime - currentTime; // Get how much time has passed
        accumulator += deltaTime;
        //cout<<"Accum: "<<accumulator<<endl;
        if (accumulator >= (1/(mInfo->getCurrentFPS()*CLOCKS_PER_SEC))) {
            while(SDL_PollEvent(&event)) { // Keep going until there are no more pending events
                switch (event.type) {
                case SDL_KEYDOWN:
                    // Coolest union of structures ever. Holds every event EVER.
                    switch (event.key.keysym.sym) { 
                    case SDLK_ESCAPE:
                        QUIT_FLAG = true;
                        break; // Redundant, but whatever.
                    case SDLK_w:
                        // Flag the forward key as pressed, repeat as necesssary
                        frnt_back = mPlayer->getMoveSpeed(); 
                        break;
                    case SDLK_s:
                        frnt_back = -(mPlayer->getMoveSpeed());
                        break;
                    case SDLK_a:
                        lft_rht = mPlayer->getMoveSpeed();
                        break;
                    case SDLK_d:
                        lft_rht = -(mPlayer->getMoveSpeed());
                        break;
                    default:
                        // If it is a key we dont have an action for, just:
						//cout<<"GOT A  RANDOM KEY: "<<event.key.keysym.sym<<endl;
                        break;
                    }
                    break; //Gets out of KEYDOWN?
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                    case SDLK_w:
                        if (frnt_back > 0)
                            frnt_back = 0; // Flag the forward key as pressed, repeat as necesssary
                        //cout<<"X: "<<mainPlayerObj->globPos[0]<<" Y: "<<mainPlayerObj->globPos[2]<<endl;
                        break;
                    case SDLK_s:
                        if (frnt_back < 0)
                            frnt_back = 0;
                        //cout<<"X: "<<mainPlayerObj->globPos[0]<<" Y: "<<mainPlayerObj->globPos[2]<<endl;
                        break;
                    case SDLK_a:
                        if (lft_rht > 0)
                            lft_rht = 0;
                        //cout<<"X: "<<mainPlayerObj->globPos[0]<<" Y: "<<mainPlayerObj->globPos[2]<<endl;
                        break;
                    case SDLK_d:
                        if (lft_rht < 0)
                            lft_rht = 0;
                        //cout<<"X: "<<mainPlayerObj->globPos[0]<<" Y: "<<mainPlayerObj->globPos[2]<<endl;
                        break;
                    default:
                        // If it is a key we dont have an action for, just:
                        break;
                    }
					break; // Glad we found that.
                case SDL_MOUSEMOTION:
                    // Rotate the camera
                    //cout<<"Xrel: "<<event.motion.xrel<<" Yrel: "<<event.motion.yrel<<endl;
                    if (event.motion.xrel < 100 && event.motion.yrel < 100) {
                        // Make sure we can't look in circles (exorcist neck breaking style):
						if (mPlayer->getXRot() + (event.motion.yrel/mInfo->getMouseSense()) > -90 && 
							mPlayer->getXRot() + (event.motion.yrel/mInfo->getMouseSense()) < 90) {
							mPlayer->setXRot(mPlayer->getXRot()+(event.motion.yrel/mInfo->getMouseSense()));
                        }

                        float newRot = mPlayer->getYRot() + (event.motion.xrel/mInfo->getMouseSense());
                        mPlayer->setYRot(newRot);
                    }
                    break;
                case SDL_QUIT:
                    QUIT_FLAG = true;
                    break;
                }
            }
            
            float newVal = 0.0f;
            // Debug showing movement flag values:
            if (frnt_back == mPlayer->getMoveSpeed()) {
                // If it is w:
                yrotrad = (float)(mPlayer->getYRot() / 180 * M_PI);
                xrotrad = (float)(mPlayer->getXRot() / 180 * M_PI);
                newVal = mPlayer->getXPos() - float(sin(yrotrad)) * mPlayer->getMoveSpeed();
                mPlayer->setXPos(newVal);
                newVal = mPlayer->getZPos() + float(cos(yrotrad)) * mPlayer->getMoveSpeed();
                mPlayer->setZPos(newVal);
                newVal = mPlayer->getYPos() + float(sin(xrotrad)) * mPlayer->getMoveSpeed();
                mPlayer->setYPos(newVal);
            }
			if (frnt_back == -mPlayer->getMoveSpeed()) {
                // If it is s:
                yrotrad = (float)(mPlayer->getYRot() / 180 * M_PI);
                xrotrad = (float)(mPlayer->getXRot() / 180 * M_PI);
                newVal = mPlayer->getXPos() + float(sin(yrotrad)) * mPlayer->getMoveSpeed();
                mPlayer->setXPos(newVal);
                newVal = mPlayer->getZPos() - float(cos(yrotrad)) * mPlayer->getMoveSpeed();
                mPlayer->setZPos(newVal);
                newVal = mPlayer->getYPos() - float(sin(xrotrad)) * mPlayer->getMoveSpeed();
                mPlayer->setYPos(newVal);
            }
            if (lft_rht == mPlayer->getMoveSpeed()) {
                // If it is a:
                yrotrad = (float)(mPlayer->getYRot() / 180 * M_PI);
                newVal = mPlayer->getXPos() + float(cos(yrotrad)) * mPlayer->getMoveSpeed();
                mPlayer->setXPos(newVal);
                newVal = mPlayer->getZPos() + float(sin(yrotrad)) * mPlayer->getMoveSpeed();
                mPlayer->setZPos(newVal);
            }
			if (lft_rht == -mPlayer->getMoveSpeed()) {
                // If it is d:
                yrotrad = (float)(mPlayer->getYRot() / 180 * M_PI);
                newVal = mPlayer->getXPos() - float(cos(yrotrad)) * mPlayer->getMoveSpeed();
                mPlayer->setXPos(newVal);
                newVal = mPlayer->getZPos() - float(sin(yrotrad)) * mPlayer->getMoveSpeed();
                mPlayer->setZPos(newVal);
            }
            accumulator -= (1/(mInfo->getCurrentFPS()*CLOCKS_PER_SEC));
            // Lets not fall through the floor:
            //float *tempGlobalCent = mainPlayerObj->currentRoom->GetGlobalCenter();
            //if (mainPlayerObj->globPos[1] > (tempGlobalCent[1]+1)) {
            //    mainPlayerObj->globPos[1]-=1;
            //}
			//cout<<"globRot[0]="<<mainPlayerObj->globRot[0]<<", globRot[1]="<<mainPlayerObj->globRot[1]<<endl;
        }
        if (QUIT_FLAG)
            break; // Break out and get rid of memory leaks and stuff
        // Else
        draw(screen); // Updates the screen

    }
}

void Game::setCurrentDrawMode(videoDrawMode type) {
    mInfo->setCurrentDrawMode((int)type);
}

int main(int argv, char *argc[]) {
    srand((int)time(NULL));
    Game *mGame = new Game;

	// Default screen init:
    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 16, SDL_DOUBLEBUF | SDL_HWSURFACE);
    //playerStats *mainPlayerObj = new playerStats;
    
    // For temporary debugging:
	int menuDisplay;
	if (argc[1] == NULL)
		menuDisplay = 0;
    else
		menuDisplay = atoi(argc[1]);
    if (menuDisplay == 1)
        mGame->setCurrentDrawMode(menu);
    else
        mGame->setCurrentDrawMode(game);

    if (mGame->initIO(screen) == 1) {// Kbd, mouse, video, sound, etc.
        //delete mainPlayerObj;
        return 1;
    }
    mGame->mainLoop(screen);
    SDL_Quit();
    delete mGame;

    return 0;
}
