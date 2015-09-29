#ifndef __RETICLE_H__
#define __RETICLE_H__

// game engine includes
#include "Object.h"

class Reticle : public df::Object {

public:
	// default constructor
	Reticle();

	// Handle event (default is to ignore everything).
	// Return 0 if ignored, else 1 if handled.
	int eventHandler(df::Event *p_e);

	// how to draw the reticle on the screen
	void draw();
};
#endif