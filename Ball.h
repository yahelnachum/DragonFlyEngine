#ifndef __BALL_H__
#define __BALL_H__

// game engine includes
#include "Object.h"

class Ball : public df::Object {

private:

public:
	// default constructor
	Ball();

	// overloaded constructor to take in initial velocity and position
	Ball(float xVelocity, float yVelocity, df::Position);

	// how to draw the ball on the screen
	void draw();

	// Handle event (default is to ignore everything).
	// Return 0 if ignored, else 1 if handled.
	int eventHandler(df::Event *p_e);
};
#endif