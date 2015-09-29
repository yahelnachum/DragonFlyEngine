#ifndef __BUS_H__
#define __BUS_H__

// game engine includes
#include "Object.h"

class Bus : public df::Object {
public:
	// default constructor
	Bus();

	// overloaded constructor to set initial position.
	Bus::Bus(df::Position pos, int alt);

	// how to draw the bus on the screen
	void draw();

	// Handle event (default is to ignore everything).
	// Return 0 if ignored, else 1 if handled.
	int eventHandler(df::Event *p_e);
};
#endif