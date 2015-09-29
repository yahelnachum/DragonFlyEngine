// system includes
#include <string>

// game engine includes
#include "LogManager.h"
#include "GraphicsManager.h"
#include "GameManager.h"

#include "EventStep.h"
#include "EventOut.h"
#include "EventKeyboard.h"

#include "Utility.h"

// tester includes
#include "Bus.h"

// constructor to set velocity
Bus::Bus(){
	setType("Bus");
	setSolidness(df::SOFT);
}

// overloaded constructor to set initial position and altitude.
Bus::Bus(df::Position pos, int alt){
	setType("Bus");
	setSolidness(df::SOFT);
	setPosition(pos);
	setAltitude(alt);
}

// defines how to draw the bus
void Bus::draw(){
	int x = getPosition().getX();
	int y = getPosition().getY();

	// multiline drawing of a bus
	df::GraphicsManager::getInstance().drawString(df::Position(x, y - 1), "  --------+", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
	df::GraphicsManager::getInstance().drawString(df::Position(x, y),     " /        |", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
	df::GraphicsManager::getInstance().drawString(df::Position(x, y + 1), "/         |", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
	df::GraphicsManager::getInstance().drawString(df::Position(x, y + 2), "|         |", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
	df::GraphicsManager::getInstance().drawString(df::Position(x, y + 3), "o---------o", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
}

// Handle event (default is to ignore everything).
// Return 0 if ignored, else 1 if handled.
int Bus::eventHandler(df::Event *p_e){
	
	// if out of bounds then end game
	if (p_e->getType() == DF_OUT_EVENT){
		df::GameManager::getInstance().setGameOver();
		return 1;
	}

	// if the space key is pressed then set the velocity of the bus to start moving
	else if (p_e->getType() == df::DF_KEYBOARD_EVENT && ((df::EventKeyboard *) p_e)->getKeyboardAction() == df::EventKeyboardAction::KEY_PRESSED && ((df::EventKeyboard *) p_e)->getKey() == df::Input::SPACE){
		setXVelocity(-0.1);
		return 1;
	}
	return 0;
}