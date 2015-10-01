#include "GraphicsManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameManager.h"

// IHOP includes
#include "Block.h"
#include "EventCollision.h"


Block::Block(){
	// Dragonfly managers needed for this method.
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Setup "saucer" sprite.
	df::Sprite *p_temp_sprite = resource_manager.getSprite("hero");
	if (!p_temp_sprite) {
		log_manager.writeLog("Hero::Hero(): Warning! Sprite '%s' not found",
			"hero");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}

	setType("Block");
	setSolidness(df::SOFT);
	setPosition(df::Position(50,2));

	move_slowdown = 0;
	move_countdown = move_slowdown;
}

int Block::eventHandler(df::Event *p_e){
	df::LogManager::getInstance().writeLog("event type: %s\n", p_e->getType().c_str());
	if (p_e->getType() == DF_COLLISION_EVENT){
		eventCollision(static_cast <df::EventCollision *> (p_e));
		df::LogManager::getInstance().writeLog("COLISION EVENT IN BLOCK\n");
	}
	return 0;
}

int Block::eventCollision(df::EventCollision *p_e){
	if (p_e->getObject1()->getType().compare("Hero") == 0 ||
		p_e->getObject2()->getType().compare("Hero") == 0){
		setYVelocity(0.2);
		return 1;
	}
	return 0;
}