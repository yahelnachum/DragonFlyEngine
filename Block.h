#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "Object.h"
#include "EventCollision.h"

class Block : public df::Object {
private:
	// slowdown counters
	int move_countdown = 0;
	int move_slowdown = 0;
public:
	// default constructor
	Block();

	// event handler
	int eventHandler(df::Event *p_e);

	// if collision event then go to this function
	int eventCollision(df::EventCollision *p_e);
};
#endif