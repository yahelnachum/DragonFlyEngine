#ifndef __HERO_H__
#define __HERO_H__

// game engine includes
#include "Object.h"
#include "EventKeyboard.h"

// constant defined type
#define HERO_TYPE "hero"

class Hero : public df::Object {
private:
	// countdowns for moving
	int move_countdown = 0;
	int move_slowdown = 0;
public:
	// constructor
	Hero();

	// event handler
	int eventHandler(df::Event *p_e);

	// takes a input from keyboard and moves according to the keys
	int keyboardInput(const df::EventKeyboard *p_e);

	// moves the hero by that delta
	void move(int dx, int dy);
};
#endif