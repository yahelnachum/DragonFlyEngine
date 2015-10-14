#include "Weapon.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "ResourceManager.h"
#include "Enemy.h"
#include "LogManager.h"

Weapon::Weapon(df::Position init_pos, Direction init_direction) {

	df::ResourceManager &rm = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	exist_countdown = exist_slowdown;

	// Setup "hero" sprite.
	df::Sprite *p_temp_sprite = rm.getSprite("weapon");
	if (!p_temp_sprite) {
		log_manager.writeLog("Weapon::Weapon(): Warning! Sprite '%s' not found",
			"weapon");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}
	setSolidness(df::SOFT);
	setType("Weapon");
	direction = init_direction;
	setWeaponPosition(init_pos, direction);
	setAltitude(4);
}

// event handler
int Weapon::eventHandler(df::Event *p_e) {
	if (p_e->getType() == DF_STEP_EVENT) {
		if (exist_countdown == 0) {
			df::WorldManager &wm = df::WorldManager::getInstance();
			wm.markForDelete(this);
		}
		else {
			exist_countdown--;
		}
		return 1;
	}
	if (p_e->getType() == DF_COLLISION_EVENT){
		eventCollision(static_cast <df::EventCollision *> (p_e));
		return 1;
	}
	return 0;
}

// handle collision event
int Weapon::eventCollision(const df::EventCollision *p_e) {
	if (p_e->getObject1()->getType().compare("Enemy") == 0){
		Enemy *enemy = (Enemy*)p_e->getObject1();

		df::WorldManager &wm = df::WorldManager::getInstance();
		wm.markForDelete(enemy);
		return 1;
	}
	if (p_e->getObject2()->getType().compare("Enemy") == 0) {
		Enemy *enemy = (Enemy*)p_e->getObject2();
		df::WorldManager &wm = df::WorldManager::getInstance();
		wm.markForDelete(enemy);
		return 1;
	}
	return 0;
}

int Weapon::setWeaponPosition(df::Position pos, Direction direction) {
	df::WorldManager &wm = df::WorldManager::getInstance();
	if (direction == NORTH) {
		df::Position new_pos = df::Position(pos.getX() + 1, pos.getY() - 2);
		setSpriteIndex(0);
		wm.moveObject(this, new_pos);
		return 0;
	}
	if (direction == EAST) {
		df::Position new_pos = df::Position(pos.getX() + 3, pos.getY());
		setSpriteIndex(1);
		wm.moveObject(this, new_pos);
		return 0;
	}
	if (direction == SOUTH) {
		df::Position new_pos = df::Position(pos.getX() + 1, pos.getY() + 3);
		setSpriteIndex(2);
		wm.moveObject(this, new_pos);
		return 0;
	}
	if (direction == WEST) {
		df::Position new_pos = df::Position(pos.getX() - 2, pos.getY());
		setSpriteIndex(3);
		wm.moveObject(this, new_pos);
		return 0;
	}

	return -1;
}