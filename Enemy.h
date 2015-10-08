#ifndef __ENEMY_H__
#define __ENEMY_H__

// game engine includes
#include "Object.h"
#include "EventHeroPosition.h"

class Enemy : public df::Object {
private:
	// slowdown counters
	int move_countdown = 0;
	int move_slowdown = 0;

	
	df::Position heroPosition;	// hero's current position
	df::Position *pathToHero;	// path to get to hero
	int sizeOfPath;				// size of the path to get to hero
	int counterOfPath;			// counter for the path to get to hero
	int moveSlowdown;			// slowdown counter for the path to get to hero
public:
	// default constructor
	Enemy();

	// event handler
	int eventHandler(df::Event *p_e);

	// set the hero's position
	int setHeroPosition(EventHeroPosition *p_e);

	// make a move based on the current hero position
	int makeMove();

	// check if the move is allowed by the map
	bool mapAllowsMove(int dx, int dy);

	// move with the deltas given
	void move(int dx, int dy);

	// calculate the path to the hero
	void calculatePath();
};
#endif