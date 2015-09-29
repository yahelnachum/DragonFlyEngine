// game engine includes
#include "GraphicsManager.h"
#include "LogManager.h"

#include "EventMouse.h"
#include "Utility.h"

// tester includes
#include "Reticle.h"

// default constructor
Reticle::Reticle(){
	setType("Reticle");
	setSolidness(df::SPECTRAL);

	// put above the rest of the objects
	setAltitude(4);
}

// Handle event (default is to ignore everything).
// Return 0 if ignored, else 1 if handled.
int Reticle::eventHandler(df::Event *p_e){

	// if mouse moved then move reticle to there
	if (p_e->getType() == df::DF_MOUSE_EVENT && ((df::EventMouse *)p_e)->getMouseAction() == df::MOVED){
		df::EventMouse *me = (df::EventMouse *)p_e;
		df::Position pos = df::Position(me->getMousePosition().getX(), me->getMousePosition().getY());
		pos = df::GraphicsManager::getInstance().pixelsToSpaces(pos);
		pos = df::Utility::viewToWorld(pos);
		setPosition(pos);
		return 1;
	}
	return 0;
}

// how to draw the reticle on the screen
void Reticle::draw(){
	df::GraphicsManager::getInstance().drawString(getPosition(), "+", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
}