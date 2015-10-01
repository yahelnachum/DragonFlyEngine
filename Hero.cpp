#include "GraphicsManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameManager.h"

// IHOP includes
#include "Hero.h"
#include "EventHeroPosition.h"


Hero::Hero(){
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

	setType("Hero");

	setPosition(df::Position(df::GraphicsManager::getInstance().getHorizontal() / 2,
							 df::GraphicsManager::getInstance().getVertical()   / 2));

	move_slowdown = 0;
	move_countdown = move_slowdown;

	EventHeroPosition *e = new EventHeroPosition();
	e->setHeroPosition(getPosition());
	df::WorldManager::getInstance().onEvent(e);
}

int Hero::eventHandler(df::Event *p_e){
	if (p_e->getType() == df::DF_KEYBOARD_EVENT){
		keyboardInput(static_cast <const df::EventKeyboard *> (p_e));
	}
	return 0;
}

int Hero::keyboardInput(const df::EventKeyboard *p_e){
	if (p_e->getKeyboardAction() == df::KEY_PRESSED && p_e->getKey() == df::Input::ESCAPE){
		df::GameManager::getInstance().setGameOver();
	}

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

void Hero::move(int dx, int dy) {
	// See if time to move.
	if (move_countdown > 0){
		move_countdown--;
		return;
	}
	move_countdown = move_slowdown;

	// If stays on window, allow move.
	df::Position new_pos(getPosition().getX() + dx, getPosition().getY() + dy);
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// If stays on window, allow move.
	if ((new_pos.getY() > 0) &&
		(new_pos.getY() < world_manager.getBoundary().getVertical())){
		world_manager.moveObject(this, new_pos);

		EventHeroPosition *e = new EventHeroPosition();
		e->setHeroPosition(getPosition());
		df::WorldManager::getInstance().onEvent(e);
	}
}
