// system includes
#include <stdlib.h>

// game engine includes
#include "EventOut.h"
#include "EventCollision.h"
#include "EventKeyboard.h"

#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameManager.h"

// tester includes
#include "Saucer.h"

Saucer::Saucer(std::string spriteName){
	// Dragonfly managers needed for this method.
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Setup "saucer" sprite.
	df::Sprite *p_temp_sprite = resource_manager.getSprite(spriteName);
	if (!p_temp_sprite) {
		log_manager.writeLog("Saucer::Saucer(): Warning! Sprite '%s' not found",
			"saucer");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}

	this->spriteName = spriteName;
	// Set object type.
	setType("Saucer");

	// Set speed in horizontal direction.
	setXVelocity(-0.5); // 1 space left every 4 frames

	moveToStart();

}

Saucer::~Saucer(){

}
int Saucer::eventHandler(df::Event *p_e) {

	df::LogManager::getInstance().writeLog("id: %3d, x: %3d, y: %3d\n", getId(), getPosition().getX(), getPosition().getY());
	if (p_e->getType() == DF_OUT_EVENT) {
		df::LogManager::getInstance().writeLog("out event\n");
		out();
		return 1;
	}

	// collision event
	if (p_e->getType() == DF_COLLISION_EVENT) {

		return 1;
	}
	if (count == -1){
		moveToStart();
		count++;
	}
	if (p_e->getType() == df::DF_KEYBOARD_EVENT){
		df::GameManager::getInstance().setGameOver();
		df::WorldManager::getInstance().markForDelete(this);
	}

	return 0;
}

void Saucer::hit(const df::EventCollision *p_c) {

}

void Saucer::out() {
	df::LogManager::getInstance().writeLog("in out function\n");
	if (getPosition().getX() > 1)
		return;
	count = -1;
}

void Saucer::moveToStart() {

	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	df::Position temp_pos;

	// get boundary position
	int world_horiz = graphics_manager.getHorizontal();
	int world_vert = graphics_manager.getVertical();

	// x is off right side of window
	temp_pos.setX(world_horiz + 3 + rand() % world_horiz);

	// y is in vertical range.
	temp_pos.setY(rand() % (world_vert - 4) + 4);

	// move saucer to new position
	world_manager.moveObject(this, temp_pos);
}

