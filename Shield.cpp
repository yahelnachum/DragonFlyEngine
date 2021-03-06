#include "Shield.h"
#include "EventStep.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "WorldManager.h"

Shield::Shield(df::Position pos){

	df::ResourceManager &rm = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	shield_countdown = shield_count;

	// Setup "hero" sprite.
	df::Sprite *p_temp_sprite = rm.getSprite("shield");
	if (!p_temp_sprite) {
		log_manager.writeLog("Shield::Shield(): Warning! Sprite '%s' not found",
			"shield");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}
	setSolidness(df::SOFT);
	setType("Shield");
	df::Position hpos(pos.getX(), pos.getY() - 1);
	setPosition(hpos);
	setAltitude(1);
}

int Shield::eventHandler(df::Event *p_e){

	if (p_e->getType() == EVENT_HERO_POSITION){
		setHeroPosition(static_cast <EventHeroPosition *> (p_e));
		return 1;
	}
	if (p_e->getType() == DF_COLLISION_EVENT){
		eventCollision(static_cast <const df::EventCollision *> (p_e));
		return 1;
	}
	if (p_e->getType() == DF_STEP_EVENT) {
		if (shield_countdown == 0) {
			df::WorldManager &wm = df::WorldManager::getInstance();
			wm.markForDelete(this);
		}
		else {
			shield_countdown--;
		}
		return 1;
	}
	return 0;
}

int Shield::setHeroPosition(EventHeroPosition *p_e) {
	move(p_e->getHeroPosition());
	return 0;
}

void Shield::move(df::Position pos) {
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::Position hpos(pos.getX(), pos.getY() - 1);
	world_manager.moveObject(this, hpos);

}

// if collision event then go to this function
int Shield::eventCollision(const df::EventCollision *p_e){
	// if collider is hero then start falling down screen
	if (p_e->getObject1()->getType().compare("Enemy") == 0){
		Enemy *enemy = (Enemy*)p_e->getObject1();
		df::WorldManager &wm = df::WorldManager::getInstance();
		wm.markForDelete(enemy);
		wm.markForDelete(this);
		return 1;
	}
	if (p_e->getObject2()->getType().compare("Enemy") == 0) {
		Enemy *enemy = (Enemy*)p_e->getObject2();
		df::WorldManager &wm = df::WorldManager::getInstance();
		wm.markForDelete(enemy);
		wm.markForDelete(this);
		return 1;
	}
	return 0;
}