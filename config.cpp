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
configInfo::configInfo(): 
	currentDrawMode(0), config(new ifstream), width(800), height(600),
    fullscreen(0), vsync(0), fps(60), mouse_sense(1.0f) {
}

configInfo::~configInfo() {
	delete config;
}

logFile::logFile() {
	log.open("lab2.log", ifstream::out);
	if (log.good())
		Log("--- LOG START ---\n");
}

logFile::~logFile() {
	if (log.good())
        log.close();
	//delete log;
}
//PUBLIC METHODS

// CONFIG FILE
int configInfo::readConfig() {
    config->open("config.txt", ifstream::in);
    char temp[25];
    while (config->good()) { // EOF, badbit and failbit
        // cout << (char) config.get();
        config->getline(temp, 24, '=');
        //cout<<temp<<"\n";
        if (strcmp(temp, "width") == 0) {
            config->getline(temp, 10, '\n');
            width=atoi(temp);
        }
        if (strcmp(temp, "height") == 0) {
            config->getline(temp, 10, '\n');
            height=atoi(temp);
        }
        if (strcmp(temp, "fullscreen") == 0) {
            config->getline(temp, 10, '\n');
            fullscreen=atoi(temp);
        }
        if (strcmp(temp, "vsync") == 0) {
            config->getline(temp, 10, '\n');
            vsync=atoi(temp);
        }
        if (strcmp(temp, "fps") == 0) {
            config->getline(temp, 10, '\n');
            fps=atoi(temp);
        }
        if (strcmp(temp, "mouse_sense") == 0) {
            config->getline(temp, 10, '\n');
            mouse_sense=atof(temp);
        }
    }
    config->close();

    return 0;
}

std::string configInfo::getStrVars() {
    std::stringstream temp;
	temp<<"Width: "<<width<<" Height: "<<height<<" Fullscreen: "<<fullscreen<<std::endl;
    temp<<"Vsync: "<<vsync<<" Desired FPS: "<<fps<<std::endl;
	return temp.str();
}

// LOG FILE
void logFile::Log(std::string text) {
    if (log.good()) { // EOF, badbit and failbit
        log<<text<<endl;
    }
}
void logFile::Warning(std::string text) {
    if (log.good()) { // EOF, badbit and failbit
        log<<"WARNING: "<<text<<endl;
    }
}
void logFile::Error(std::string text) {
   	if (log.good()) { // EOF, badbit and failbit
        log<<"ERROR: "<<text<<endl;
    }
}
