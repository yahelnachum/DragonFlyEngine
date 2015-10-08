#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Object.h"
#include "EventHeroPosition.h"
#include "EventPower.h"
#include "Power.h"

class Enemy : public df::Object {
private:
	// slowdown 
	int move_countdown = 0;
	int move_slowdown = 0;

	int power_countdown = 0;
	int power_slowdown = 0;

	PowerUp power = NONE;
	// hero's current position
	df::Position heroPosition;
public:
	// default constructor
	Enemy();

	// event handler
	int eventHandler(df::Event *p_e);

	// set the hero's position
	int setHeroPosition(EventHeroPosition *p_e);

	// handle collision event
	int eventCollision(const df::EventCollision *p_e);

	// handle power events
	int handlePower(EventPower *p_e);

	// make a move based on the current hero position
	int makeMove();

	// move with the deltas given
	void move(int dx, int dy);
};
#endif