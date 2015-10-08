#ifndef __BLOCK_H__
#define __BLOCK_H__

// game engine includes
#include "Object.h"
#include "EventCollision.h"

// constant type definition
#define BLOCK_TYPE "block"

class Block : public df::Object {
private:
	const float FALL_VELOCITY = 0.2;	// falling velocity
	bool isAtBottomShelf = false;		// if block is at the bottom shelf

	// slowdown counters
	int move_countdown = 0;
	int move_slowdown = 0;
public:
	// default constructor
	Block(df::Position pos);

	// event handler
	int eventHandler(df::Event *p_e);

	// if collision event then go to this function
	int eventCollision(df::EventCollision *p_e);

	// if block collision occurs
	int blockCollision(Block *p_e);

	// set is at bottom shelf boolean
	void setIsAtBottomShelf(bool new_isAtBottomShelf = true);

	// get if the block is at the bottom shelf
	bool blockIsAtBottomShelf();
};
#endif