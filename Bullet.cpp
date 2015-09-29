// game engine includes
#include "LogManager.h"
#include "GraphicsManager.h"
#include "WorldManager.h"

#include "EventStep.h"
#include "EventOut.h"

// tester includes
#include "Bullet.h"

// default constructor
Bullet::Bullet(){
	setType("Bullet");
}

// constructor to give initial velocity and position
Bullet::Bullet(float xVelocity, float yVelocity, df::Position pos){
	setType("Bullet");
	setXVelocity(xVelocity);
	setYVelocity(yVelocity);
	setSolidness(df::SOFT);
	setPosition(pos);
}

// how to draw the bullet on the screen
void Bullet::draw(){
	df::GraphicsManager::getInstance().drawString(getPosition(), ">-->", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
}

// Handle event (default is to ignore everything).
// Return 0 if ignored, else 1 if handled.
int Bullet::eventHandler(df::Event *p_e){

	// if out of bounds then change velocity to bring back into bounds
	if (p_e->getType() == DF_OUT_EVENT){
		df::WorldManager::getInstance().markForDelete(this);
		return 1;
	}
	return 0;
}