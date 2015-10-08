#include "Power.h"
#include "ResourceManager.h"
#include "LogManager.h"

Power::Power(PowerUp init_power, df::Position init_pos){
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

	// Setup "hero" sprite.
	df::Sprite *p_temp_sprite = resource_manager.getSprite("powerup");
	if (!p_temp_sprite) {
		log_manager.writeLog("Power::Power(): Warning! Sprite '%s' not found",
			"powerup");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}
	power = init_power;
	setPosition(init_pos);
	setSolidness(df::SOFT);
	setType("Power");
	setAltitude(3);
}

Power::~Power(){

}

// return the PowerUp type
PowerUp Power::getPowerUp() const{
	return power;
}

// event handler
int Power::eventHandler(df::Event *p_e){
	if (p_e->getType() == DF_COLLISION_EVENT){
		eventCollision(static_cast <const df::EventCollision *> (p_e));
	}
	return 0;
}

// if collision event then go to this function
int Power::eventCollision(const df::EventCollision *p_e){
	return 0;
}