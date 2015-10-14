#ifndef __POWER_H__
#define __POWER_H__

#include "Object.h"
#include "EventCollision.h"

const int DEFAULT_POWER_COUNT = 300;

enum PowerUp {
	NONE = 0,
	SPEED,
	SHIELD,
	KILL,
	RANGE,
	SLOWENEMY,
};

class Power : public df::Object {

private:
	PowerUp power;

public:

	Power(PowerUp init_power, df::Position init_pos);

	// return the PowerUp type
	PowerUp getPowerUp() const;

	// event handler
	int eventHandler(df::Event *p_e);

	// if collision event then go to this function
	int eventCollision(const df::EventCollision *p_e);
};

#endif