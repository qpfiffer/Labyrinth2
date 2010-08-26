#include "config.h"

//CONSTRUCTORS
configInfo::configInfo() {
    // Video defaults:
    width=800;
    height=600;
    fullscreen=0;
    vsync=0;
    fps=60;
    currentDrawMode = menu;
}

logFile::logFile() {   
}
//PUBLIC METHODS

// CONFIG FILE
const int configInfo::getCurrentFPS() {
    return fps;
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

    const SDL_VideoInfo *vidInfo = SDL_GetVideoInfo();
    if (fullscreen == 1 && currentDrawMode == game) {
		//cout<<"Called on 1"<<endl;
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        screen = SDL_SetVideoMode(width, height, 16, SDL_OPENGL | SDL_FULLSCREEN);
	}
    else if (fullscreen == 0 && currentDrawMode == game) {
		//cout<<"Called on 2"<<endl;
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        screen = SDL_SetVideoMode(width, height, 16, SDL_OPENGL);
	}
	else if (currentDrawMode == menu) {
		//cout<<"Called on 3"<<endl;
		screen = SDL_SetVideoMode(width, height, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	}
	if (screen == NULL)
		cout<<"Unable to setup SDL_Surface."<<endl;

    vidInfo = SDL_GetVideoInfo(); // Call it again because we changed current_w and current_h
	//cout<<"From SDL_Surface pointer: Width: "<<screen->w<<" Height: "<<screen->h<<endl;
	//cout<<"From VideoInfo: Screen w: "<<(int)vidInfo->current_w<<" Screen h: "<<(int)vidInfo->current_h<<endl;
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

        // AA
        GLfloat values[2];
        glGetFloatv (GL_LINE_WIDTH_GRANULARITY, values);
        glGetFloatv (GL_LINE_WIDTH_RANGE, values);
        glEnable (GL_POLYGON_SMOOTH);
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
        glLineWidth (1.5); 
        // End AA

        glLoadIdentity(); // Blank GL_MODELVIEW
	    SDL_ShowCursor(SDL_DISABLE); // Hide the mouse cursor
    	SDL_WM_GrabInput(SDL_GRAB_ON); //Makes it so mouse events happen outside of the screen.
        // ---
    }
    return 0;

}

// LOG FILE
int logFile::readLogFile() {
    log.open("lab2.log", ifstream::out);
    return 0;
}

/*
void logFile::Log(string text) {
    while (log.good()) { // EOF, badbit and failbit
        log<<text<<endl;
    }
}
void logFile::Warning(string text) {
    while (log.good()) { // EOF, badbit and failbit
        log<<"WARNING: "<<text<<endl;
    }
}
void logFile::Error(string text) {
    while (log.good()) { // EOF, badbit and failbit
        log<<"ERROR: "<<text<<endl;
    }
}*/

int logFile::closeLogfile() {
    if (log.good())
        log.close();
    return 0;
}