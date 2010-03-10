#include "config.h"

configInfo::configInfo() {
  // Video defaults:
  width=640;
  height=480;
  fullscreen=0;
  vsync=0;
  fps=60;
  currentDrawMode = menu;
}

const void configInfo::changeCurrentDrawMode(videoDrawMode type) {
  currentDrawMode = type;
}

const videoDrawMode configInfo::getCurrentDrawMode() {
  return currentDrawMode;
}

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
    if (strcmp(temp, "fps") == 0) {
      config.getline(temp, 10, '\n');
      fps=atoi(temp);
    }
  }
  config.close();

  return 0;
}

void configInfo::printVars() {
  cout<<"Width: "<<width<<" Height: "<<height<<" Fullscreen: "<<fullscreen<<endl;
  cout<<"Vsync: "<<vsync<<" Desired FPS: "<<fps<<endl;
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
  if (currentDrawMode == game) {
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
  }
  return 0;

}
