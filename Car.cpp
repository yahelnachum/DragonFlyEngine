// system includes
#include <string>

// game engine includes
#include "LogManager.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"

#include "EventStep.h"
#include "EventKeyboard.h"

#include "Utility.h"

// tester includes
#include "Car.h"

// constructor to set initial velocity
Car::Car(){
	setType("Car");
	setSolidness(df::HARD);

	df::Sprite *p_temp_sprite = df::ResourceManager::getInstance().getSprite("saucer");
	if (!p_temp_sprite) {
		df::LogManager::getInstance().writeLog("nothing\n");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}
}

// overloaded constructor for setting initial position, and altitude
Car::Car(df::Position pos, int alt){
	setType("Car");
	setPosition(pos);
	setAltitude(alt);
	setSolidness(df::HARD);

	df::Sprite *p_temp_sprite = df::ResourceManager::getInstance().getSprite("saucer");
	if (!p_temp_sprite) {
		df::LogManager::getInstance().writeLog("nothing\n");
	}
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(4);
	}
}

// Handle event (default is to ignore everything).
// Return 0 if ignored, else 1 if handled.
int Car::eventHandler(df::Event *p_e){

	// if the space key is pressed then set the velocity of the car to start moving
	if (p_e->getType() == df::DF_KEYBOARD_EVENT && ((df::EventKeyboard *) p_e)->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && ((df::EventKeyboard *) p_e)->getKey() == df::Input::SPACE){
		setXVelocity(0.1);
		return 1;
	}
	return 0;
}