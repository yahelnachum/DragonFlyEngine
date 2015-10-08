#include "EventPower.h"

EventPower::EventPower() {
	power = NONE;
	setType(DF_POWER_EVENT);
}

EventPower::EventPower(PowerUp init_power) {
	power = init_power;
}

void EventPower::setPowerUp(PowerUp new_power) {
	power = new_power;
}

PowerUp EventPower::getPowerUp() const {
	return power;
}