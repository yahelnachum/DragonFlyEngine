#ifndef __HERO_H__
#define __HERO_H__

#include "Object.h"
#include "EventKeyboard.h"

class Hero : public df::Object {
private:
	int move_countdown = 0;
	int move_slowdown = 0;
public:
	Hero();
	int eventHandler(df::Event *p_e);
	int keyboardInput(const df::EventKeyboard *p_e);
	void move(int dx, int dy);
};
#endif