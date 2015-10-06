#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "Object.h"
#include "EventCollision.h"

class Block : public df::Object {
private:
	const float FALL_VELOCITY = 0.2;
	bool isAtBottomShelf = false;

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

	void setIsAtBottomShelf(bool new_isAtBottomShelf = true);

	bool blockIsAtBottomShelf();
};
#endif