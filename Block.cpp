// game engine includes
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "MapManager.h"

// IHOP includes
#include "Block.h"
#include "EventCollision.h"
#include "Hero.h"

// constructor
Block::Block(df::Position pos){
	// Dragonfly managers needed for this method.
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Setup "block" sprite.
	df::Sprite *p_temp_sprite = resource_manager.getSprite("block");
	if (!p_temp_sprite) {
		log_manager.writeLog("Block::Block(): Warning! Sprite '%s' not found",
			"block");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	// set attributes
	setType(BLOCK_TYPE);
	setSolidness(df::SOFT);
	setPosition(pos);

	// set slowdown
	move_slowdown = 0;
	move_countdown = move_slowdown;
}

// handle events
int Block::eventHandler(df::Event *p_e){
	
	// if collision event
	if (p_e->getType() == DF_COLLISION_EVENT){
		eventCollision(static_cast <df::EventCollision *> (p_e));
	}
	return 0;
}

// if collision event
int Block::eventCollision(df::EventCollision *p_e){
	// if collider is hero then start falling down screen
	if (p_e->getObject1()->getType().compare(HERO_TYPE) == 0 ||
		p_e->getObject2()->getType().compare(HERO_TYPE) == 0){
		setYVelocity(FALL_VELOCITY);
		return 1;
	}
	// if collided with shelf then stop falling
	else if (p_e->getObject1()->getType().compare("Shelf") == 0 ||
		p_e->getObject2()->getType().compare("Shelf") == 0){
		setYVelocity(0.0);
		return 1;
	}
	// if collided with block then go to block collision function
	else if (p_e->getObject1()->getType().compare(BLOCK_TYPE) == 0 &&
		p_e->getObject2()->getType().compare(BLOCK_TYPE) == 0){
		if (p_e->getObject1() == this){
			return blockCollision(static_cast <Block *>(p_e->getObject2()));
		}
		else{
			return blockCollision(static_cast <Block *>(p_e->getObject1()));
		}
	}
	// if collided with bottom shelf then stop and change to at bottom shelf
	else if (p_e->getObject1()->getType().compare("BottomShelf") == 0 ||
		p_e->getObject2()->getType().compare("BottomShelf") == 0){
		MapManager &mm = MapManager::getInstance();
		mm.addStackToCounter();
		setYVelocity(0.0);
		setIsAtBottomShelf();
		return 1;
	}
	return 0;
}

// if collision with block
int Block::blockCollision(Block *p_e){
	// if is falling then stop falling
	if (getYVelocity() > 0.0){
		setYVelocity(0.0);
	}
	// if it is stationary then start falling
	else if (!isAtBottomShelf){
		setYVelocity(FALL_VELOCITY);
	}
	return 1;
}

// set block to is at bottom shelf
void Block::setIsAtBottomShelf(bool new_isAtBottomShelf){
	isAtBottomShelf = new_isAtBottomShelf;
}

// get if the block is at the bottom shelf
bool Block::blockIsAtBottomShelf(){
	return isAtBottomShelf;
}