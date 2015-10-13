// game engine includes
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "EventStep.h"

// IHOP includes
#include "Hero.h"
#include "EventHeroPosition.h"
#include "MapManager.h"
#include "Shield.h"
#include "EventPower.h"
#include "Weapon.h"
#include "StartScreen.h"

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
	setType(HERO_TYPE);
	setPosition(df::Position(df::GraphicsManager::getInstance().getHorizontal() / 2,
							 df::GraphicsManager::getInstance().getVertical()   / 2 + 2));
	initialPosition = getPosition();
	// set slowdown
	move_slowdown = 0;
	move_countdown = move_slowdown;
	setAltitude(4);

	// set starting direction
	wep_direction = EAST;

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
	if (p_e->getType() == DF_COLLISION_EVENT){
		eventCollision(static_cast <const df::EventCollision *> (p_e));
	}
	if (p_e->getType() == DF_STEP_EVENT) {
		if (power_countdown == 0) {
			power = NONE;
		}
		else {
			power_countdown--;
		}
	}
	return 0;
}

// process keyboardInput to move hero or quit game
int Hero::keyboardInput(const df::EventKeyboard *p_e){
	// if escape is pressed then quit game
	if (p_e->getKeyboardAction() == df::KEY_PRESSED && p_e->getKey() == df::Input::ESCAPE){
		
	}

	// if wasd keys are pressed then move in the appropriate direction
	if (p_e->getKeyboardAction() == df::KEY_DOWN){
		switch (p_e->getKey()){
		case df::Input::A:
			move(-1, 0);
			wep_direction = WEST;
			return 1;
			break;
		case df::Input::D:
			move(1, 0);
			wep_direction = EAST;
			return 1;
			break;
		case df::Input::W:
			move(0, -1);
			wep_direction = NORTH;
			return 1;
			break;
		case df::Input::S:
			move(0, 1);
			wep_direction = SOUTH;
			return 1;
			break;
		case df::Input::SPACE:
			new Weapon(getPosition(), wep_direction);
			return 1;
			break;
		}
	}
	return 0;
}

int Hero::eventCollision(const df::EventCollision *p_e) {
	// if collider is hero then start falling down screen
	if (p_e->getObject1()->getType().compare("Power") == 0){
		Power *newPower = (Power*) p_e->getObject1();
		power = newPower->getPowerUp();
		power_countdown = DEFAULT_POWER_COUNT;
		activatePower();
		newPower->~Power();
		return 1;
	}
	if (p_e->getObject2()->getType().compare("Power") == 0) {
		Power *newPower = (Power*)p_e->getObject2();
		power = newPower->getPowerUp();
		power_countdown = DEFAULT_POWER_COUNT;
		activatePower();
		newPower->~Power();
		return 1;
	}
	if (p_e->getObject1()->getType().compare("Enemy") == 0 || p_e->getObject2()->getType().compare("Enemy") == 0) {
		if (power != SHIELD) {
			df::ResourceManager::getInstance().getSound("screaming")->play();
			if (lives > 1){
				lives--;
				resetPosition();
			}
			else{
				StartScreen::removeAllObjectsExceptThis();
			}
		}
		else {
			power_countdown = 10;
		}
	}
	return 0;
}

void Hero::activatePower() {
	switch (power) {
	case SHIELD:
		new Shield(getPosition());
		break;
	case SPEED:
		break;
	default:
		EventPower *ep = new EventPower(power);
	}
}

// move hero with the given deltas
void Hero::move(int dx, int dy) {
	// See if time to move.
	if (move_countdown > 0){
		move_countdown--;
		if (power == SPEED && !(move_countdown > 0)) {
			move_countdown--;
		}
		if (power == SPEED && !(move_countdown > 0)) {
			move_countdown--;
		}
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
		mm.onMap(df::Position(new_pos.getX(), new_pos.getY()+1))){
		world_manager.moveObject(this, new_pos);

		// send out new hero position event to enemies
		EventHeroPosition *e = new EventHeroPosition();
		e->setHeroPosition(getPosition());
		df::WorldManager::getInstance().onEvent(e);
	}
}

void Hero::resetPosition(){
	setPosition(initialPosition);
}