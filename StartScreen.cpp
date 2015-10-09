#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

#include "EventKeyboard.h"

#include "StartScreen.h"

// default constructor
StartScreen::StartScreen(){
	// Dragonfly managers needed for this method.
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Setup "hero" sprite.
	df::Sprite *p_temp_sprite = resource_manager.getSprite("startscreen");
	if (!p_temp_sprite) {
		log_manager.writeLog("StartScreen::StartScreen(): Warning! Sprite '%s' not found",
			"startscreen");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(10);
	}

	// set attributes
	setType("StartScreen");
	setPosition(df::Position(df::GraphicsManager::getInstance().getHorizontal() / 2,
		df::GraphicsManager::getInstance().getVertical() / 2));

}

// event handler
int StartScreen::eventHandler(df::Event *p_e){
	if (p_e->getType() == df::DF_KEYBOARD_EVENT){
		df::EventKeyboard *e = static_cast <df::EventKeyboard *> (p_e);
		if (e->getKey() == df::Input::RETURN && e->getKeyboardAction() == df::KEY_PRESSED){

		}
	}

	return 0;
}