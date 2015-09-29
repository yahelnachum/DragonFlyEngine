// game engine include
#include "GraphicsManager.h"

#include "SpecularObject.h"

// default constructor
SpecularObject::SpecularObject(){
	setType("SpecularObject");
	setSolidness(df::SPECTRAL);
}

// overloaded constructor for setting initial position
SpecularObject::SpecularObject(df::Position pos){
	setType("SpecularObject");
	setSolidness(df::SPECTRAL);
	setPosition(pos);
}

// how to draw the car on the screen
void SpecularObject::draw(){
	int x = getPosition().getX();
	int y = getPosition().getY();

	// multiline drawing of a car
	df::GraphicsManager::getInstance().drawString(df::Position(x, y), "+--+", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
	df::GraphicsManager::getInstance().drawString(df::Position(x, y+1),	"|  |", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
	df::GraphicsManager::getInstance().drawString(df::Position(x, y+2), "+--+", df::Justification::LEFT_JUSTIFIED, df::Color::YELLOW);
}