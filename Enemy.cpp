// system includes
#include <cmath>

// game engine includes
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameManager.h"

#include "EventCollision.h"
#include "EventStep.h"

// IHOP includes
#include "Enemy.h"
#include "EventHeroPosition.h"
#include "EventPower.h"

// default constructor
Enemy::Enemy(){
	// Dragonfly managers needed for this method.
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Setup "hero" sprite.
	df::Sprite *p_temp_sprite = resource_manager.getSprite("hero");
	if (!p_temp_sprite) {
		log_manager.writeLog("Hero::Hero(): Warning! Sprite '%s' not found",
			"hero");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}

	// set attributes
	setType("Enemy");
	setPosition(df::Position(3,3));

	// set slowdown
	move_slowdown = 4;
	move_countdown = move_slowdown;

	// set initial hero position
	heroPosition = df::Position(3,3);
}

// handle events
int Enemy::eventHandler(df::Event *p_e){
	// if event is event hero position then set heros new position
	if (p_e->getType() == EVENT_HERO_POSITION){
		df::LogManager::getInstance().writeLog("got eventheroposition\n");
		setHeroPosition(static_cast <EventHeroPosition *> (p_e));
	}

	if (p_e->getType() == DF_COLLISION_EVENT){
		eventCollision(static_cast <df::EventCollision *> (p_e));
	}
	// if its a step event then make a move based on heros current position
	if (p_e->getType() == DF_STEP_EVENT){
		makeMove();
		if (power_countdown != 0) {
			power_countdown--;
		}
		else {
			if (power != NONE){
				if (power == SLOWENEMY) {
					move_slowdown = move_slowdown / 2;
				}
				power = NONE;
			}
		}
	}

	if (p_e->getType() == DF_POWER_EVENT) {
		handlePower(static_cast <EventPower *> (p_e));
	}
	return 0;
}

int Enemy::eventCollision(const df::EventCollision *p_e) {
	if (p_e->getObject1()->getType().compare("Shield") == 0 || p_e->getObject2()->getType().compare("Shield") == 0) {
		// TODO die
	}
	return 0;
}

// set heros position
int Enemy::setHeroPosition(EventHeroPosition *p_e){
	heroPosition = p_e->getHeroPosition();
	return 1;
}


int Enemy::handlePower(EventPower *p_e) {
	power = p_e->getPowerUp();
	if (power == SLOWENEMY) {
		move_slowdown = move_slowdown * 2;
		power_slowdown = DEFAULT_POWER_COUNT / 2;
		power_countdown = power_slowdown;
	}
	return 0;
}

// make a move based on hero's current position
int Enemy::makeMove(){

	// get the difference between hero's and enemy's position
	int delta_x = heroPosition.getX() - getPosition().getX();
	int delta_y = heroPosition.getY() - getPosition().getY();

	// check to see which change is bigger, x or y
	if (abs(delta_x) > abs(delta_y)){
		// move x if it is bigger
		if (delta_x < 0)
			move(-1, 0);
		else
			move(1, 0);
		return 1;
	}
	else if (abs(delta_y) > abs(delta_x)){
		// move y if it is bigger
		if (delta_y < 0)
			move(0, -1);
		else
			move(0, 1);
		return 1;
	}
	else if (abs(delta_x) == abs(delta_y) && abs(delta_x) > 0){
		if (delta_x < 0)
			move(-1, 0);
		else
			move(1, 0);
		return 1;
	}

	return 0;
}

// move the enemy with the given deltas
void Enemy::move(int dx, int dy) {
	// See if time to move.
	if (move_countdown > 0){
		move_countdown--;
		return;
	}
	// reset countdown
	move_countdown = move_slowdown;

	// If stays on window, allow move.
	df::Position new_pos(getPosition().getX() + dx, getPosition().getY() + dy);
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// If stays on window, allow move.
	if ((new_pos.getY() > 0) &&
		(new_pos.getY() < world_manager.getBoundary().getVertical())){
		world_manager.moveObject(this, new_pos);
	}
}
