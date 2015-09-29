#include "Points.h"
#include "EventStep.h"
#include "EventView.h"

Points::Points() {
	// set up object location, text, and color
	setLocation(df::TOP_RIGHT);
	setViewString(POINTS_STRING);
	setColor(df::YELLOW);

	// register for event

}

int Points::eventHandler(df::Event *p_e) {

	if (df::ViewObject::eventHandler(p_e)){
		return 1;
	}

	// step event, update value
	if (p_e->getType() == DF_STEP_EVENT) {
		if (static_cast <const df::EventStep *> (p_e)
			->getStepCount() % 30 == 0)
			setValue(getValue() + 1);
		return 1;
	}
	if (p_e->getType() == DF_VIEW_EVENT){
		df::EventView *ev = (df::EventView *) p_e;
		if (ev->getTag() == "points"){
			setValue(getValue() + ev->getDelta());
		}
	}

	return 0;
}