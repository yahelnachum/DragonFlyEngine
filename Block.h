#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "Object.h"
#include "EventCollision.h"

class Block : public df::Object {
private:
	int move_countdown = 0;
	int move_slowdown = 0;
public:
	Block();
	int eventHandler(df::Event *p_e);
	int eventCollision(df::EventCollision *p_e);
};
#endif