#include "main.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

string itos(int convMe) {
    string converted;
    stringstream out;
    out<<convMe;
    converted = out.str();
    return converted;
}
// Constructors:
playerStats::playerStats() {
    // Log file should be made first so other classes can use it
    myLogFile = new logFile;
    myLogFile->readLogFile();

    int i;
    for (i=0; i<3; i++) {
        globRot[i]=0;
        if (i==1) {
            globPos[i]=-1;
        } else {
            globPos[i]=0;
        }
    }
    moveSpeed = 0.1f;         // The camera's movement speed

    currentRoom = new subRoom(this);
}

int initIO(SDL_Surface *screen, playerStats *mainPlayerObj) {
    // Read in data from config file:
    mainPlayerObj->readConfig();
    if (mainPlayerObj->setupVideo(screen) == 1)
        return 1;

    mainPlayerObj->printVars();
    // Keyboard/mouse:
    return 0;
}

static void draw(SDL_Surface *screen, playerStats *mainPlayerObj) {   
	if (mainPlayerObj->getCurrentDrawMode() == game) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity(); // Clear modelview for good measure. THAT'LL SHOW THAT GUY
        glClearColor(1,1,0,0); // Set the default fill to yellow
        // Mouse rotation stuff:
        // This little loop breaks everything after a little while. I wouldn't enable it.
        /*while (1) {
          if (mainPlayerObj->globRot[0] > 360)
            mainPlayerObj->globRot[0]-=360;
          if (mainPlayerObj->globRot[1] > 360)
            mainPlayerObj->globRot[1]-=360;
          if (mainPlayerObj->globRot[0] < 360 &&
          mainPlayerObj->globRot[1] < 360)
            break;
            }*/
        glRotatef(mainPlayerObj->globRot[0], 1, 0, 0);
        glRotatef(mainPlayerObj->globRot[1], 0, 1, 0);
        // Global movement:
        glTranslatef(mainPlayerObj->globPos[0], mainPlayerObj->globPos[1], mainPlayerObj->globPos[2]);
        //cout<<"globRot[0]="<<mainPlayerObj->globRot[0]<<", globRot[1]="<<mainPlayerObj->globRot[1]<<endl;
        // Draw the current room:
        mainPlayerObj->currentRoom->drawRoom();

		

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

static void mainLoop(SDL_Surface *screen, playerStats *mainPlayerObj) {
    SDL_Event event;
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
        if (accumulator >= (1/(mainPlayerObj->getCurrentFPS()*CLOCKS_PER_SEC))) {
            while(SDL_PollEvent(&event)) { // Keep going until there are no more pending events
                switch (event.type) {
                case SDL_KEYDOWN:
                    // Coolest union of structures ever. Holds every event EVER.
                    switch (event.key.keysym.sym) { 
                    case SDLK_ESCAPE:
                        mainPlayerObj->myLogFile->closeLogfile();
                        delete mainPlayerObj->currentRoom;
                        delete mainPlayerObj->myLogFile;
                        exit(0);
                        break; // Redundant, but whatever.
                    case SDLK_w:
                        // Flag the forward key as pressed, repeat as necesssary
                        frnt_back = mainPlayerObj->moveSpeed; 
                        break;
                    case SDLK_s:
                        frnt_back = -(mainPlayerObj->moveSpeed);
                        break;
                    case SDLK_a:
                        lft_rht = mainPlayerObj->moveSpeed;
                        break;
                    case SDLK_d:
                        lft_rht = -(mainPlayerObj->moveSpeed);
                        break;
                    default:
                        // If it is a key we dont have an action for, just:
						cout<<"GOT A  RANDOM KEY: "<<event.key.keysym.sym<<endl;
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
						if (mainPlayerObj->globRot[0] + (event.motion.yrel/mainPlayerObj->GetMouseSense()) > -90 && 
							mainPlayerObj->globRot[0] + (event.motion.yrel/mainPlayerObj->GetMouseSense()) < 90)
							mainPlayerObj->globRot[0] += (event.motion.yrel/mainPlayerObj->GetMouseSense());
                        mainPlayerObj->globRot[1]+=(event.motion.xrel/mainPlayerObj->GetMouseSense());
                    }
                    break;
                case SDL_QUIT:
                    exit(0);
                    break;
                }
            }
            // Debug showing movement flag values:
            if (frnt_back == mainPlayerObj->moveSpeed) {
                // If it is w:
                yrotrad = (float)(mainPlayerObj->globRot[1] / 180 * M_PI);
                xrotrad = (float)(mainPlayerObj->globRot[0] / 180 * M_PI);
                mainPlayerObj->globPos[0] -= float(sin(yrotrad)) * mainPlayerObj->moveSpeed;
                mainPlayerObj->globPos[2] += float(cos(yrotrad)) * mainPlayerObj->moveSpeed;
                mainPlayerObj->globPos[1] += float(sin(xrotrad)) * mainPlayerObj->moveSpeed;
            }
			if (frnt_back == -mainPlayerObj->moveSpeed) {
                // If it is s:
                yrotrad = (float)(mainPlayerObj->globRot[1] / 180 * M_PI);
                xrotrad = (float)(mainPlayerObj->globRot[0] / 180 * M_PI);
                mainPlayerObj->globPos[0] += float(sin(yrotrad)) * mainPlayerObj->moveSpeed;
                mainPlayerObj->globPos[2] -= float(cos(yrotrad)) * mainPlayerObj->moveSpeed;
                mainPlayerObj->globPos[1] -= float(sin(xrotrad)) * mainPlayerObj->moveSpeed;
            }
            if (lft_rht == mainPlayerObj->moveSpeed) {
                // If it is a:
                yrotrad = (float)(mainPlayerObj->globRot[1] / 180 * M_PI);
                mainPlayerObj->globPos[0] += float(cos(yrotrad)) * mainPlayerObj->moveSpeed;
                mainPlayerObj->globPos[2] += float(sin(yrotrad)) * mainPlayerObj->moveSpeed;
            }
			if (lft_rht == -mainPlayerObj->moveSpeed) {
                // If it is d:
                yrotrad = (float)(mainPlayerObj->globRot[1] / 180 * M_PI);
                mainPlayerObj->globPos[0] -= float(cos(yrotrad)) * mainPlayerObj->moveSpeed;
                mainPlayerObj->globPos[2] -= float(sin(yrotrad)) * mainPlayerObj->moveSpeed;
            }
            accumulator -= (1/(mainPlayerObj->getCurrentFPS()*CLOCKS_PER_SEC));
			//cout<<"globRot[0]="<<mainPlayerObj->globRot[0]<<", globRot[1]="<<mainPlayerObj->globRot[1]<<endl;

        }
        //printf("frnt_back: %f || left_rht: %f\n", frnt_back, lft_rht);
        //mainPlayerObj->globPos[1] += frnt_back;
        //mainPlayerObj->globPos[0] += lft_rht;
        // Prints the position of the player:
        //printf("x: %f y: %f z: %f\n", globPos[0], globPos[1], globPos[2]);
        draw(screen, mainPlayerObj); // Updates the screen
        //SDL_Delay(50); // Wait 50ms, probably not necessary
    }
}

int main(int argv, char *argc[]) {
    srand(time(NULL));

	// I don't know why, but this fixes everything. Goddamn.
    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 16, SDL_DOUBLEBUF | SDL_HWSURFACE);
    playerStats mainPlayerObj;
    
    // For temporary debugging:
	int menuDisplay;
	if (argc[1] == NULL)
		menuDisplay = 0;
    else
		menuDisplay = atoi(argc[1]);
    if (menuDisplay == 1)
        mainPlayerObj.changeCurrentDrawMode(menu);
    else
        mainPlayerObj.changeCurrentDrawMode(game);

    if (initIO(screen, &mainPlayerObj) == 1) // Kbd, mouse, video, sound, etc.
        return 1;
    mainLoop(screen, &mainPlayerObj);

    return 0;
}
