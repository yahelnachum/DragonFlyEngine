// game engine includes
#include "EventStep.h"

// Create base event.
df::EventStep::EventStep(){
	setType(DF_STEP_EVENT);
}

// overloaded constructor to add initial step count
df::EventStep::EventStep(int init_step_count){
	setType(DF_STEP_EVENT);
	step_count = init_step_count;
}

// sets step count to given value
void df::EventStep::setStepCount(int new_step_count){
	step_count = new_step_count;
}

// returns current step count
int df::EventStep::getStepCount() const{
	return step_count;
}