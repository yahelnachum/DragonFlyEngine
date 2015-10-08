#ifndef __SHIELD_H__
#define __SHIELD_H__

#include "Object.h"
#include "Power.h"
#include "EventHeroPosition.h"

class Shield : public df::Object {
private:
	int shield_countdown = 0;
	int shield_count = DEFAULT_POWER_COUNT;

public:

	Shield(df::Position pos);

	~Shield();

	int eventHandler(df::Event *p_e);

	int setHeroPosition(EventHeroPosition *p_e);

	// if collision event then go to this function
	int eventCollision(const df::EventCollision *p_e);
};

#endif