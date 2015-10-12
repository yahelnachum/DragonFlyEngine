#ifndef __WEAPON_H__
#define __WEAPON_H__
#include "Object.h"
#include "EventCollision.h"

enum Direction {
	NONED = 0,
	NORTH,
	EAST,
	SOUTH,
	WEST,
};

class Weapon : public df::Object {

private:
	int exist_countdown = 0;
	int exist_slowdown = 5;
	Direction direction;

	// set weapon position based on hero position and direciton
	int setWeaponPosition(df::Position pos, Direction direction);

public:

	Weapon(df::Position init_pos, Direction init_direction);

	~Weapon();

	// event handler
	int eventHandler(df::Event *p_e);

	// handle collision event
	int eventCollision(const df::EventCollision *p_e);

};

#endif