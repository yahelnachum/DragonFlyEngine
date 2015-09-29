// game engine includes
#include "LogManager.h"
#include "GraphicsManager.h"
#include "WorldManager.h"

#include "EventStep.h"
#include "EventOut.h"

// testing includes
#include "Ball.h"

// default constructor
Ball::Ball(){
	setType("Ball");
}

// overloaded constructor to take in initial velocity and position
Ball::Ball(float xVelocity, float yVelocity, df::Position pos){
	setType("Ball");
	setXVelocity(xVelocity);
	setYVelocity(yVelocity);
	setSolidness(df::HARD);
	setPosition(pos);
}

// how to draw the ball on the screen
void Ball::draw(){
	df::GraphicsManager::getInstance().drawString(getPosition(), " _ ", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
	df::GraphicsManager::getInstance().drawString(df::Position(getPosition().getX(), getPosition().getY()+1), "(_)", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
}

// Handle event (default is to ignore everything).
// Return 0 if ignored, else 1 if handled.
int Ball::eventHandler(df::Event *p_e){

	// if out then mark for delete
	if (p_e->getType() == DF_OUT_EVENT){
		df::WorldManager::getInstance().markForDelete(this);
		return 1;
	}
	return 0;
}