// IHOP includes
#include "EventHeroPosition.h"

// default constructor
EventHeroPosition::EventHeroPosition(){
	// set attributes
	setType(EVENT_HERO_POSITION);
	heroPosition = df::Position();
}

// set hero's position
void EventHeroPosition::setHeroPosition(df::Position pos){
	heroPosition = pos;
}

// get hero's position
df::Position EventHeroPosition::getHeroPosition(){
	return heroPosition;
}