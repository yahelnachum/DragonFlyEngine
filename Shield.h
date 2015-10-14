#ifndef __SHIELD_H__
#define __SHIELD_H__

#include "Object.h"
#include "Power.h"
#include "EventHeroPosition.h"

class Shield : public df::Object {

private:
	int shield_countdown = 0;					// count down of time left for power
	int shield_count = DEFAULT_POWER_COUNT;		// time left for power

public:

	// default constructor
	Shield(df::Position pos);

	// event handler for shield
	int eventHandler(df::Event *p_e);

	// used to follow heros position
	int setHeroPosition(EventHeroPosition *p_e);

	// used to calculate position relative to hero
	void move(df::Position pos);

	// if collision event then go to this function
	int eventCollision(const df::EventCollision *p_e);
};

#endif