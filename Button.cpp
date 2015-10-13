#include "Button.h"
#include "ResourceManager.h"
#include "LogManager.h"

Button::Button(){
	wall_count = 0;

	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Setup "button" sprite.
	df::Sprite *p_temp_sprite = resource_manager.getSprite("button");
	if (!p_temp_sprite) {
		log_manager.writeLog("Button::Button(): Warning! Sprite '%s' not found",
			"button");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(0);
	}

	setSolidness(df::SOFT);
}

Button::~Button(){

}

// event handler
int Button::eventHandler(df::Event *p_e) {
	if (p_e->getType() == DF_COLLISION_EVENT){
		eventCollision(static_cast <df::EventCollision *> (p_e));
		return 1;
	}
	return 0;
}

// handle collision event
int Button::eventCollision(const df::EventCollision *p_e){
	static bool activated = false;
	if ((p_e->getObject1()->getType().compare("hero") == 0 || p_e->getObject2()->getType().compare("hero") == 0) && !activated) {
		deactivateWalls();
		setSpriteIndex(1);
		df::ResourceManager::getInstance().getSound("buttonclick")->play();
		activated = true;
	}
	return 0;
}

int Button::addWall(Wall *new_wall){
	if (wall_count < MAX_WALL_COUNT) {
		p_wall[wall_count] = new_wall;
		wall_count++;
		return 0;
	}
	return -1;
}

int Button::removeWall(Wall *rem_wall){
	for (int i = 0; i < wall_count - 1; i++) {
		if (p_wall[i] == rem_wall) {
			p_wall[i]->~Wall();
			for (int j = i; j < MAX_WALL_COUNT - 2; j++) {
				p_wall[j] = p_wall[j + 1];
				return 0;
			}
		}
	}
	return -1;
}

void Button::activateWalls(){
	for (int i = 0; i < wall_count; i++) {
		p_wall[i]->setActive(true);
	}
}

void Button::deactivateWalls(){
	for (int i = 0; i < wall_count; i++) {
		p_wall[i]->setActive(false);
	}
}