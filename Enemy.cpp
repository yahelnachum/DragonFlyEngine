// system includes
#include <cmath>

// game engine includes
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameManager.h"

#include "EventStep.h"

// IHOP includes
#include "Enemy.h"
#include "EventHeroPosition.h"
#include "MapManager.h"
#include "MapObject.h"
#include "Position.h"
#include "TreeNode.h"

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
	setPosition(df::Position(3,5));

	// set slowdown
	move_slowdown = 4;
	move_countdown = move_slowdown;

	// set initial hero position
	heroPosition = df::Position(40,5);
	int counterOfPath = 0;
	
	// get path to hero
	TreeNode *base = new TreeNode(getPosition());
	pathToHero = TreeNode::pathToPosition(base, heroPosition, &sizeOfPath, 100);
	std::printf("counter: %d, sizeofPath %d\n", counterOfPath, sizeOfPath);
	for (int i = 0; i < sizeOfPath; i++){
		std::printf("x: %d, y: %d\n", pathToHero[i].getX(), pathToHero[i].getY());
	}

	// set slowdown
	moveSlowdown = 10;
}

// handle events
int Enemy::eventHandler(df::Event *p_e){
	// if event is event hero position then set heros new position
	if (p_e->getType() == EVENT_HERO_POSITION){
		df::LogManager::getInstance().writeLog("got eventheroposition\n");
		setHeroPosition(static_cast <EventHeroPosition *> (p_e));
	}
	// if its a step event then make a move based on heros current position
	if (p_e->getType() == DF_STEP_EVENT){
		makeMove();
	}
	return 0;
}

// set heros position
int Enemy::setHeroPosition(EventHeroPosition *p_e){
	heroPosition = p_e->getHeroPosition();
	return 1;
}

// make a move based on hero's current position
int Enemy::makeMove(){
	// if slowdown done then go to next position in path array
	if (counterOfPath < sizeOfPath && moveSlowdown <= 0){
		setPosition(df::Position(pathToHero[counterOfPath].getX(), pathToHero[counterOfPath].getY() - 1));
		counterOfPath++;
		moveSlowdown = 10;
		return 1;
	}	
	// else decrement slowdown
	else{
		moveSlowdown--;
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