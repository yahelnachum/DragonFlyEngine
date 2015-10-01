#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Object.h"
#include "EventHeroPosition.h"

class Enemy : public df::Object {
private:
	int move_countdown = 0;
	int move_slowdown = 0;
	df::Position heroPosition;
public:
	Enemy();
	int eventHandler(df::Event *p_e);
	int setHeroPosition(EventHeroPosition *p_e);
	int makeMove();
	void move(int dx, int dy);
};
#endif