#include "main.h"

// THINGS TO REMEMBER:
float globRot[3] = { 0, 0, 0 }; // The camera's rotation at all times
float globPos[3] = { 0, 0, 0 }; // The camera's position at all times
float moveSpeed = 0.05;         // The camera's movement speed

int initIO(SDL_Surface *screen) {
  // Setting up video:
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Unable to init video: %s\n", SDL_GetError());
    return 1;
  }
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Turns double-buffering on
  const SDL_VideoInfo *vidInfo = SDL_GetVideoInfo(); // Get information about the computer
  // and then use the Desktop's max res to make the game fullscreen
  // NOTE: changing the video mode with this destroys opengl state
  // Make sure to redo the state if it is ever changed
  screen = SDL_SetVideoMode(vidInfo->current_w, vidInfo->current_h, 
			    vidInfo->vfmt->BitsPerPixel, SDL_OPENGL | SDL_FULLSCREEN);
  // OpenGL init:
  glEnable(GL_TEXTURE_2D); // Enable 2D textures
  glViewport(0, 0, vidInfo->current_w, vidInfo->current_h);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION); // Load the Porjection matrix (camera stuff, basically)
  glLoadIdentity(); // Reset that matrix
  float aspect = (float)vidInfo->current_w / (float)vidInfo->current_h; // The aspect ratio
  gluPerspective(60.0, aspect, 0.1, 100.0); //
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glMatrixMode(GL_MODELVIEW); // Switch back to the good 'ole modelview matrix
  glEnable(GL_DEPTH_TEST); //Not sure why we want this enabled
  glDisable(GL_CULL_FACE); //Draw front AND back of polygons
  glLoadIdentity(); // Blank GL_MODELVIEW
  // ---
  // Keyboard/mouse:
  SDL_ShowCursor(SDL_DISABLE); // Hide the mouse cursor
  SDL_WM_GrabInput(SDL_GRAB_ON); //Makes it so mouse events happen outside of the screen.
  
  return 0;
}

static void draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); // Clear modelview for good measure. THAT'LL SHOW THAT GUY
  glClearColor(1,1,0,0); // Set the default fill to yellow
  // Mouse rotation stuff:
  //glRotatef(globRot[0], 0, 1, 0);
  //glRotatef(globRot[1], 1, 0, 0);
  drawPlane(50, 50);

  glTranslatef(0, -1, -5); // Move the camera back 2 units (Away from the screen)
  //glTranslatef(globPos[0], globPos[1], globPos[2]);
    
  SDL_GL_SwapBuffers();
}

static void mainLoop() {
  SDL_Event event;
  float frnt_back=0, lft_rht=0; // Flags for movement
  while (1) {
    while(SDL_PollEvent(&event)) { // Keep going until there are no more pending events
      switch (event.type) {
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym) { // Coolest union of structures ever. Holds every event EVER.
	case SDLK_ESCAPE:
	  exit(0);
	  break; // Redundant, but whatever.
	case SDLK_w:
	  frnt_back = moveSpeed; // Flag the forward key as pressed, repeat as necesssary
	  break;
	case SDLK_s:
	  frnt_back = -(moveSpeed);
	  break;
	case SDLK_a:
	  lft_rht = -(moveSpeed);
	  break;
	case SDLK_d:
	  lft_rht = moveSpeed;
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
	  break;
	case SDLK_s:
    if (frnt_back < 0)
	    frnt_back = 0;
	  break;
	case SDLK_a:
    if (lft_rht < 0)
	  lft_rht = 0;
	  break;
	case SDLK_d:
    if (lft_rht > 0)
	  lft_rht = 0;
	  break;
	default:
	  // If it is a key we dont have an action for, just:
	  break;
	}
      case SDL_MOUSEMOTION:
	// Rotate the camera
	globRot[0]+=event.motion.xrel;
	globRot[1]+=event.motion.yrel;
      	break;
      case SDL_QUIT:
	exit(0);
	break;
      }
    }
    // Debug showing movement flag values:
    //printf("frnt_back: %f || left_rht: %f\n", frnt_back, lft_rht);
    globPos[2] += frnt_back;
    globPos[0] += lft_rht;
    // Prints the position of the player:
    //printf("x: %f y: %f z: %f\n", globPos[0], globPos[1], globPos[2]);
    draw(); // Updates the screen
    SDL_Delay(50); // Wait 50ms, probably not necessary
  }
}

int main(int argv, char *argc[]) {
  SDL_Surface *mainWindow;
  //glutInit(argv, argc); // Because glut sucks
  initIO(mainWindow); // Kbd, mouse, video, sound, etc.
  
  mainLoop();

  return 0;
}
