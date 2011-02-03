#include "config.h"
// VC2k10 memory leak checking
#ifdef _DEBUG
#include <ostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

//CONSTRUCTORS
configInfo::configInfo(): width(800), height(600),
    fullscreen(0),
    vsync(0),
    fps(60),
    currentDrawMode(0),
    mouse_sense(1.0f)  {
}

logFile::logFile() {   
}
//PUBLIC METHODS

// CONFIG FILE
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
        if (strcmp(temp, "mouse_sense") == 0) {
            config.getline(temp, 10, '\n');
            mouse_sense=atof(temp);
        }
    }
    config.close();

    return 0;
}

void configInfo::printVars() {
    cout<<"Width: "<<width<<" Height: "<<height<<" Fullscreen: "<<fullscreen<<endl;
    cout<<"Vsync: "<<vsync<<" Desired FPS: "<<fps<<endl;
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