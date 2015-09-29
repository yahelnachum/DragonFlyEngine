#ifndef __CAR_H__
#define __CAR_H__

// game engine includes
#include "Object.h"

class Car : public df::Object {

public:

	// default constructor
	Car();

	// overloaded constructor for setting initial position
	Car(df::Position pos, int alt);

	// Handle event (default is to ignore everything).
	// Return 0 if ignored, else 1 if handled.
	int eventHandler(df::Event *p_e);
};
#endif