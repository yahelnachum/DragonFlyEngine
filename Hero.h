#ifndef __HERO_H__
#define __HERO_H__

// game engine includes
#include "MapObject.h"
#include "EventKeyboard.h"
#include "EventCollision.h"
#include "Power.h"
#include "Weapon.h"

// constant defined type
#define HERO_TYPE "hero"

class Hero : public MapObject {
private:
	PowerUp power;
	int power_countdown = 0;
	// countdowns for moving
	int move_countdown = 0;
	int move_slowdown = 0;
	int lives = 3;
	df::Position initialPosition;

	Direction wep_direction;
public:
	// constructor
	Hero(df::Position pos);

	// event handler
	int eventHandler(df::Event *p_e);

	// takes a input from keyboard and moves according to the keys
	int keyboardInput(const df::EventKeyboard *p_e);

	// if collision event then go to this function
	int eventCollision(const df::EventCollision *p_e);

	void activatePower();

	// moves the hero by that delta
	void move(int dx, int dy);

	// get current powerUp of hero
	Power getPower() const;

	// set current powerUp of hero
	void setPower(Power new_power);

	void resetPosition();
};
#endif