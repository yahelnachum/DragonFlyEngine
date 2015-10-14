#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"

#include "EventKeyboard.h"

#include "StartScreen.h"
#include "MapManager.h"
#include "Lives.h"
#include "Points.h"

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
		setSpriteSlowdown(5);
	}

	// set attributes
	setType("StartScreen");
	setPosition(df::Position(df::GraphicsManager::getInstance().getHorizontal() / 2,
		df::GraphicsManager::getInstance().getVertical() / 2));
	setSolidness(df::SPECTRAL);

	df::ResourceManager::getInstance().getMusic("backgroundMusic")->play();
}

// event handler
int StartScreen::eventHandler(df::Event *p_e){
	if (p_e->getType() == df::DF_KEYBOARD_EVENT){
		df::EventKeyboard *e = static_cast <df::EventKeyboard *> (p_e);
		if (e->getKey() == df::Input::RETURN && e->getKeyboardAction() == df::KEY_PRESSED){
			if (state == 0){
				setPosition(df::Position(df::GraphicsManager::getInstance().getHorizontal(),
					df::GraphicsManager::getInstance().getVertical()));

				new Points();
				new Lives();

				MapManager::getInstance().loadMap1();

				state++;
			}
		}
		else if (e->getKey() == df::Input::ESCAPE && e->getKeyboardAction() == df::KEY_PRESSED){
			if (state == 0){
				df::GameManager::getInstance().setGameOver();
			}
			else{
				setPosition(df::Position(df::GraphicsManager::getInstance().getHorizontal() / 2,
					df::GraphicsManager::getInstance().getVertical() / 2));
				state--;
				removeAllObjectsExceptThis();
			}
		}
	}

	return 0;
}

void StartScreen::removeAllObjectsExceptThis(){
	df::ObjectList ol = df::WorldManager::getInstance().getAllObjects();
	df::ObjectListIterator oli = df::ObjectListIterator(&ol);
	while (!oli.isDone()){
		if (oli.currentObject()->getType() != "StartScreen")
			df::WorldManager::getInstance().removeObject(oli.currentObject());
		else{
			oli.currentObject()->setPosition(df::Position(df::GraphicsManager::getInstance().getHorizontal() / 2,
				df::GraphicsManager::getInstance().getVertical() / 2));
			(static_cast <StartScreen *> (oli.currentObject()))->state = 0;
		}
		oli.next();
	}
}