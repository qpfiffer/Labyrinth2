#include "main.h"

// Constructors:
playerStats::playerStats() {
  int i;
  for (i=0;i<3;i++) {
    globRot[i]=0;
    globPos[i]=0;
  }
  moveSpeed = 0.05;         // The camera's movement speed
}

configInfo::configInfo() {
  // Video defaults:
  width=640;
  height=480;
  fullscreen=0;
  vsync=0;
}
// ---
int configInfo::readConfig() {
  config.open("config.txt", ifstream::in);
  char temp[25];
  while (config.good()) { // EOF, badbit and failbit
    // cout << (char) config.get();
    config.getline(temp, 24, '=');
    //cout<<temp<<"\n";
    if (strcmp(temp, "width") == 0) {
      config.getline(temp, 10, '\n');
      width=atoi(temp);
    }
    if (strcmp(temp, "height") == 0) {
      config.getline(temp, 10, '\n');
      height=atoi(temp);
    }
    if (strcmp(temp, "fullscreen") == 0) {
      config.getline(temp, 10, '\n');
      fullscreen=atoi(temp);
    }
    if (strcmp(temp, "vsync") == 0) {
      config.getline(temp, 10, '\n');
      vsync=atoi(temp);
    }
  }
  config.close();

  return 0;
}

void configInfo::printVars() {
  cout<<"Width: "<<width<<" Height: "<<height<<" Fullscreen: "<<fullscreen<<endl;
}

int configInfo::setupVideo(SDL_Surface *screen) {
  // Setting up video:
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Unable to init video: %s\n", SDL_GetError());
    return 1;
  }
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Turns double-buffering on
  const SDL_VideoInfo *vidInfo = SDL_GetVideoInfo();
  
  if (fullscreen == 1)
    screen = SDL_SetVideoMode(width, height, vidInfo->vfmt->BitsPerPixel, SDL_OPENGL | SDL_FULLSCREEN);
  else
    screen = SDL_SetVideoMode(width, height, vidInfo->vfmt->BitsPerPixel, SDL_OPENGL);
  
  vidInfo = SDL_GetVideoInfo(); // Call it again because we changed current_w and current_h
  // OpenGL init:
  glEnable(GL_TEXTURE_2D); // Enable 2D textures
  glViewport(0, 0, vidInfo->current_w, vidInfo->current_h);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION); // Load the Porjection matrix (camera stuff, basically)
  glLoadIdentity(); // Reset that matrix
  float aspect = (float)vidInfo->current_w / (float)vidInfo->current_h; // The aspect ratio
  gluPerspective(50.0, aspect, 0.1, 100.0); //
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glMatrixMode(GL_MODELVIEW); // Switch back to the good 'ole modelview matrix
  glEnable(GL_DEPTH_TEST); //Not sure why we want this enabled
  glDisable(GL_CULL_FACE); //Draw front AND back of polygons
  glLoadIdentity(); // Blank GL_MODELVIEW
  // ---
  return 0;

}
int initIO(SDL_Surface *screen) {
  // Read in data from config file:
  configInfo mainConfig;
  mainConfig.readConfig();
  if (mainConfig.setupVideo(screen) == 1)
    return 1;
  
  // Keyboard/mouse:
  SDL_ShowCursor(SDL_DISABLE); // Hide the mouse cursor
  SDL_WM_GrabInput(SDL_GRAB_ON); //Makes it so mouse events happen outside of the screen.
  return 0;
}

static void draw(playerStats *mainPlayerObj) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); // Clear modelview for good measure. THAT'LL SHOW THAT GUY
  glClearColor(1,1,0,0); // Set the default fill to yellow
  // Mouse rotation stuff:
  /*while (1) {
    if (mainPlayerObj->globRot[0] > 360)
      mainPlayerObj->globRot[0]-=360;
    if (mainPlayerObj->globRot[1] > 360)
      mainPlayerObj->globRot[1]-=360;
    if (mainPlayerObj->globRot[0] < 360 &&
	mainPlayerObj->globRot[1] < 360)
      break;
      }*/
  glRotatef(mainPlayerObj->globRot[1], 1, 0, 0);
  glRotatef(mainPlayerObj->globRot[0], 0, 1, 0);
  // Global movement:
  glTranslatef(-mainPlayerObj->globPos[0], -mainPlayerObj->globPos[1], -mainPlayerObj->globPos[2]);
  //cout<<"globRot[0]="<<mainPlayerObj->globRot[0]<<", globRot[1]="<<mainPlayerObj->globRot[1]<<endl;  
  // So we have somthing to look at:
  glColor3f(1,0,1);
  drawPlane(50, 50);
  glColor3f(1,0,0);
  glTranslatef(0,0,-5);
  drawCube(1,1,1);
  glColor3f(0,1,1);
  glTranslatef(-2,0,2);
  drawCube(1,1,1);

  SDL_GL_SwapBuffers();
}

static void mainLoop(playerStats *mainPlayerObj) {
  SDL_Event event;
  float frnt_back=0, lft_rht=0; // Flags for movement
  float xrotrad, yrotrad; // For movement
  /*
  // ANTI-SIGSEGV
  printf(" globRot[1]: %f, glotbPos[1]: %f, moveSpeed: %f\n", mainPlayerObj->globRot[1], mainPlayerObj->globPos[1], mainPlayerObj->moveSpeed);
  exit(1);*/
  while (1) {
    while(SDL_PollEvent(&event)) { // Keep going until there are no more pending events
      switch (event.type) {
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym) { // Coolest union of structures ever. Holds every event EVER.
	case SDLK_ESCAPE:
	  exit(0);
	  break; // Redundant, but whatever.
	case SDLK_w:
	  frnt_back = mainPlayerObj->moveSpeed; // Flag the forward key as pressed, repeat as necesssary
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
	  break;
	}
	break; //Gets out of KEYDOWN?
      case SDL_KEYUP:
	switch (event.key.keysym.sym) {
	case SDLK_w:
	  if (frnt_back > 0)
	    frnt_back = 0; // Flag the forward key as pressed, repeat as necesssary
	  cout<<"X: "<<mainPlayerObj->globPos[0]<<" Y: "<<mainPlayerObj->globPos[2]<<endl;
	  break;
	case SDLK_s:
	  if (frnt_back < 0)
	    frnt_back = 0;
	  cout<<"X: "<<mainPlayerObj->globPos[0]<<" Y: "<<mainPlayerObj->globPos[2]<<endl;
	  break;
	case SDLK_a:
	  if (lft_rht > 0)
	    lft_rht = 0;
	  cout<<"X: "<<mainPlayerObj->globPos[0]<<" Y: "<<mainPlayerObj->globPos[2]<<endl;
	  break;
	case SDLK_d:
	  if (lft_rht < 0)
	    lft_rht = 0;
	  cout<<"X: "<<mainPlayerObj->globPos[0]<<" Y: "<<mainPlayerObj->globPos[2]<<endl;
	  break;
	default:
	  // If it is a key we dont have an action for, just:
	  break;
	}
      case SDL_MOUSEMOTION:
	// Rotate the camera
	mainPlayerObj->globRot[0]+=event.motion.xrel;
	mainPlayerObj->globRot[1]+=event.motion.yrel;
      	break;
      case SDL_QUIT:
	exit(0);
	break;
      }
    }
    // Debug showing movement flag values:
    if (frnt_back == mainPlayerObj->moveSpeed) {
      // If it is w:
      yrotrad = (mainPlayerObj->globRot[1] / 180 * 3.141592654f);
      xrotrad = (mainPlayerObj->globRot[0] / 180 * 3.141592654f); 
      mainPlayerObj->globPos[0] += float(sin(yrotrad)) ;
      mainPlayerObj->globPos[2] -= float(cos(yrotrad)) ;
      mainPlayerObj->globPos[1] -= float(sin(xrotrad)) ;
    }
    else if (frnt_back == -mainPlayerObj->moveSpeed) {
      // If it is s:
      yrotrad = (mainPlayerObj->globRot[1] / 180 * 3.141592654f);
      xrotrad = (mainPlayerObj->globRot[0] / 180 * 3.141592654f); 
      mainPlayerObj->globPos[0] -= float(sin(yrotrad)) ;
      mainPlayerObj->globPos[2] += float(cos(yrotrad)) ;
      mainPlayerObj->globPos[1] += float(sin(xrotrad)) ;
    }
    if (lft_rht == mainPlayerObj->moveSpeed) {
      // If it is a:
      yrotrad = (mainPlayerObj->globRot[1] / 180 * 3.141592654f);
      mainPlayerObj->globPos[0] -= float(cos(yrotrad)) * 0.2;
      mainPlayerObj->globPos[2] -= float(sin(yrotrad)) * 0.2;
    }
    else if (lft_rht == -mainPlayerObj->moveSpeed) {
      // If it is d:
      yrotrad = (mainPlayerObj->globRot[1] / 180 * 3.141592654f);
      mainPlayerObj->globPos[0] += float(cos(yrotrad)) * 0.2;
      mainPlayerObj->globPos[2] += float(sin(yrotrad)) * 0.2;
    }
    //printf("frnt_back: %f || left_rht: %f\n", frnt_back, lft_rht);
    //mainPlayerObj->globPos[1] += frnt_back;
    //mainPlayerObj->globPos[0] += lft_rht;
    // Prints the position of the player:
    //printf("x: %f y: %f z: %f\n", globPos[0], globPos[1], globPos[2]);
    draw(mainPlayerObj); // Updates the screen
    //SDL_Delay(50); // Wait 50ms, probably not necessary
  }
}

int main(int argv, char *argc[]) {
  SDL_Surface mainWindow;
  playerStats mainPlayerObj;
  
  if (initIO(&mainWindow) == 1) // Kbd, mouse, video, sound, etc.
    return 1;
  mainLoop(&mainPlayerObj);

  return 0;
}
