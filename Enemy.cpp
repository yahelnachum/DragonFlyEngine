// system includes
#include <cmath>
#include <iostream>

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
#include "MapManager.h"
#include "MapObject.h"
#include "Position.h"
#include "TreeNode.h"

// default constructor
Enemy::Enemy(df::Position pos){
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
	setPosition(pos);

	// set slowdown
	move_slowdown = 4;
	move_countdown = move_slowdown;

	// set initial hero position
	heroPosition = df::Position(40, 5);
	int counterOfPath = 0;

	// get path to hero
	TreeNode *base = new TreeNode(df::Position(getPosition().getX(), getPosition().getY() + 1));
	pathToHero = TreeNode::pathToPosition(base, heroPosition, &sizeOfPath, 3, false);

	setSolidness(df::HARD);

	// set slowdown
	moveSlowdown = 5;
	updatePathSlowdown = 50;
}

// handle events
int Enemy::eventHandler(df::Event *p_e){

	df::LogManager &lm = df::LogManager::getInstance();
	lm.writeLog("EVENT WITH IN ENEMY %s\n\n", p_e->getType().c_str());

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

		if (updatePathSlowdown < 0){
			// get path to hero
			TreeNode *base = new TreeNode(df::Position(getPosition().getX(), getPosition().getY() + 1));
			pathToHero = TreeNode::pathToPosition(base, heroPosition, &sizeOfPath, 3, false);
			updatePathSlowdown = 50;
			counterOfPath = 0;
		}
		updatePathSlowdown--;
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
	// if slowdown done then go to next position in path array
	if (counterOfPath < sizeOfPath && moveSlowdown <= 0){
		setPosition(df::Position(getPosition().getX(), getPosition().getY() + 1));
		df::Position nextPos = getPosition().getNextAdjacentPosition(pathToHero[counterOfPath]);
		df::WorldManager::getInstance().moveObject(this, df::Position(nextPos.getX(), nextPos.getY() - 1));
		if (pathToHero[counterOfPath].equalTo(nextPos)){
			counterOfPath++;
		}
		moveSlowdown = 5;
		return 1;
	}
	// else decrement slowdown
	else{
		moveSlowdown--;
	}
	if (counterOfPath >= sizeOfPath){
		TreeNode *base = new TreeNode(df::Position(getPosition().getX(), getPosition().getY() + 1));
		pathToHero = TreeNode::pathToPosition(base, heroPosition, &sizeOfPath, 3, true);
		counterOfPath = 0;
		updatePathSlowdown = 50;
	}
	return 0;
}

// check if map allows move to position
bool Enemy::mapAllowsMove(int dx, int dy){
	// get new position
	df::Position pos(getPosition().getX() + dx, getPosition().getY() + dy + 1);

	// if map allows then return true
	if (MapManager::getInstance().onMap(pos)){
		return true;
	}
	// else return false
	return false;
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

// calculate new path to hero based on new position
void Enemy::calculatePath(){
	
}
