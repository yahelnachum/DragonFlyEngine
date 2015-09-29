// system includes
#include <windows.h>

// game engine includes
#include "Clock.h"

// Sets previous_time to current time.
df::Clock::Clock(){
	SYSTEMTIME time;
	GetSystemTime(&time);
	previous_time = (time.wSecond * 1000) + time.wMilliseconds;
}

// Return time elapsed since delta() was last called, -1 if error.
// Units are milliseconds.
long int df::Clock::delta(void){

	// get time now
	SYSTEMTIME time;
	GetSystemTime(&time);
	long int current_time = (time.wSecond * 1000) + time.wMilliseconds;
	long int delta = current_time - previous_time;

	// update previous time
	previous_time = current_time;

	return delta;
}

// Return time elapsed since delta() was last called.
// Units are milliseconds.
long int df::Clock::split(void) const{
	// get time now
	SYSTEMTIME time;
	GetSystemTime(&time);
	long int current_time = (time.wSecond * 1000) + time.wMilliseconds;

	// return elapsed time since last delta() call
	return (current_time - previous_time);
}