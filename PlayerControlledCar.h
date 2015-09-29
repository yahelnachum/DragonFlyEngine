#ifndef __PLAYER_CONTROLLED_CAR_H__
#define __PLAYER_CONTROLLED_CAR_H__

// game engine includes
#include "Car.h"

class PlayerControlledCar : public Car {
public:
	// default constructor
	PlayerControlledCar();

	// Handle event (default is to ignore everything).
	// Return 0 if ignored, else 1 if handled.
	int eventHandler(df::Event *p_e);
};
#endif