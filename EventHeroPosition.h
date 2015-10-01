#ifndef __EVENT_HERO_POSITION_H__
#define __EVENT_HERO_POSITION_H__

// game engine include
#include "Event.h"
#include "Position.h"

// string type
#define EVENT_HERO_POSITION "__event_hero_position"

class EventHeroPosition : public df::Event {
private:
	df::Position heroPosition;
public:
	// default constructor
	EventHeroPosition();

	void setHeroPosition(df::Position pos);
	df::Position getHeroPosition();
};
#endif