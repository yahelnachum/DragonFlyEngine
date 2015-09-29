// system includes
#include <stdarg.h>
#include <iostream>
#include <ctime>

// game engine includes
#include "LogManager.h"
#include "GameManager.h"

// constructor, set type of manager
df::LogManager::LogManager(){
	setType("LogManager");
}

// overloaded constructor
df::LogManager::LogManager(LogManager const&){
	setType("LogManager");
}

// destructor
df::LogManager::~LogManager(){

}

// Get the one and only instance of the LogManager.
df::LogManager &df::LogManager::getInstance(){
	static LogManager log_manager;
	return log_manager;
}

// Start up the LogManager (open logfile "dragonfly.log").
int df::LogManager::startUp(){
	
	fopen_s(&p_f, df::LOGFILE_NAME.c_str(), "w");
	return df::Manager::startUp();
}

// Shut down the LogManager (close logfile).
void df::LogManager::shutDown(){
	fclose(p_f);
	df::Manager::shutDown();
}

// Set flush of logfile after each write.
void df::LogManager::setFlush(bool do_flush){
	df::LogManager::do_flush = do_flush;
}

// Write to logfile. Supports printf() formatting.
// Return number of bytes written, -1 if error.
int df::LogManager::writeLog(const char *fmt, ...){
	// get current time to add to log file
	time_t t = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &t);
	
	// print message
	fprintf(p_f, "%02d:%02d:%02d %4d  ", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, df::GameManager::getInstance().getGameLoop());
	
	// print rest of arguements
	va_list args;
	va_start(args, fmt);
	vfprintf(p_f, fmt, args);
	va_end(args);
	
	// after each write it flushes buffer if bool is set to true
	if (do_flush)
		fflush(p_f);
	return 0;
}