// game engine includes
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameManager.h"

// IHOP includes
#include "Hero.h"
#include "EventHeroPosition.h"
#include "MapManager.h"

// default constructor
Hero::Hero(){
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
	setType("Hero");
	setPosition(df::Position(df::GraphicsManager::getInstance().getHorizontal() / 2,
							 df::GraphicsManager::getInstance().getVertical()   / 2));

	// set slowdown
	move_slowdown = 0;
	move_countdown = move_slowdown;

	// send out initial hero position event
	EventHeroPosition *e = new EventHeroPosition();
	e->setHeroPosition(getPosition());
	df::WorldManager::getInstance().onEvent(e);
}

// event handler
int Hero::eventHandler(df::Event *p_e){
	// if its a keyboard event then process in keyboardInput() function
	if (p_e->getType() == df::DF_KEYBOARD_EVENT){
		keyboardInput(static_cast <const df::EventKeyboard *> (p_e));
	}
	return 0;
}

// process keyboardInput to move hero or quit game
int Hero::keyboardInput(const df::EventKeyboard *p_e){
	// if escape is pressed then quit game
	if (p_e->getKeyboardAction() == df::KEY_PRESSED && p_e->getKey() == df::Input::ESCAPE){
		df::GameManager::getInstance().setGameOver();
	}

	// if wasd keys are pressed then move in the appropriate direction
	if (p_e->getKeyboardAction() == df::KEY_DOWN){
		switch (p_e->getKey()){
		case df::Input::A:
			move(-1, 0);
			return 1;
			break;
		case df::Input::D:
			move(1, 0);
			return 1;
			break;
		case df::Input::W:
			move(0, -1);
			return 1;
			break;
		case df::Input::S:
			move(0, 1);
			return 1;
			break;
		}
	}
	return 0;
}

// move hero with the given deltas
void Hero::move(int dx, int dy) {
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
	MapManager &mm = MapManager::getInstance();

	// If stays on window, allow move.
	if ((new_pos.getY() > 0) &&
		(new_pos.getY() < world_manager.getBoundary().getVertical()) &&
		mm.onMap(new_pos)){
		world_manager.moveObject(this, new_pos);

		// send out new hero position event to enemies
		EventHeroPosition *e = new EventHeroPosition();
		e->setHeroPosition(getPosition());
		df::WorldManager::getInstance().onEvent(e);
	}
}
