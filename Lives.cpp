// game engine includes
#include "EventStep.h"
#include "EventView.h"
#include "LogManager.h"

// IHOP includes
#include "Lives.h"

// constructor
Lives::Lives() {
	// set up object location, text, and color
	setLocation(df::TOP_LEFT);
	setViewString(LIVES_STRING);
	setColor(df::YELLOW);
	setValue(3);
}

// if event is given
int Lives::eventHandler(df::Event *p_e) {

	// if its a view object event then handle it there
	if (df::ViewObject::eventHandler(p_e)){
		return 1;
	}

	return 0;
}