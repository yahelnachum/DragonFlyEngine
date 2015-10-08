#ifndef __EVENTPOWER_H__
#define __EVENTPOWER_H__

#include "Event.h"
#include "Power.h"

class EventPower : public df::Event {

#define DF_POWER_EVENT "__power__"

private:
	PowerUp power;

public:
	EventPower();

	EventPower(PowerUp init_power);

	void setPowerUp(PowerUp new_power);

	PowerUp getPowerUp() const;
};

#endif // !__EVENTPOWER_H__