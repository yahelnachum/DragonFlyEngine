#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Object.h"
#include "EventHeroPosition.h"

class Enemy : public df::Object {
private:
	// slowdown 
	int move_countdown = 0;
	int move_slowdown = 0;

	// hero's current position
	df::Position heroPosition;
public:
	// default constructor
	Enemy();

	// event handler
	int eventHandler(df::Event *p_e);

	// set the hero's position
	int setHeroPosition(EventHeroPosition *p_e);

	// make a move based on the current hero position
	int makeMove();

	bool mapAllowsMove(int dx, int dy);

	// move with the deltas given
	void move(int dx, int dy);
};
#endif