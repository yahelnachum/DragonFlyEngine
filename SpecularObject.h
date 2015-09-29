#ifndef __SPECULAR_OBJECT_H__
#define __SPECULAR_OBJECT_H__

// game engine includes
#include "Object.h"

class SpecularObject : public df::Object {

public:

	// default constructor
	SpecularObject();

	// overloaded constructor for setting initial position
	SpecularObject(df::Position pos);

	// how to draw the car on the screen
	void draw();
};
#endif