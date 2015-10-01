#include "EventHeroPosition.h"

EventHeroPosition::EventHeroPosition(){
	setType(EVENT_HERO_POSITION);
	heroPosition = df::Position();
}

void EventHeroPosition::setHeroPosition(df::Position pos){
	heroPosition = pos;
}
df::Position EventHeroPosition::getHeroPosition(){
	return heroPosition;
}