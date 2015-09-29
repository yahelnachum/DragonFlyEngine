#ifndef __BULLET_H__
#define __BULLET_H__

// game engine include
#include "Object.h"

class Bullet : public df::Object {

private:

public:
	// default constructor
	Bullet();

	// constructor to give initial velocity and position
	Bullet(float xVelocity, float yVelocity, df::Position);

	// how to draw the bullet on the screen
	void draw();

	// Handle event (default is to ignore everything).
	// Return 0 if ignored, else 1 if handled.
	int eventHandler(df::Event *p_e);
};
#endif