#include "Floor.h"
#include "GraphicsManager.h"
#include "LogManager.h"

// constructor for floor needs length of section of floor
Floor::Floor(df::Position init_pos, int init_length){
	setPosition(init_pos);
	length = init_length;
	setType("Floor");
}

// get the length of the section of floor
int Floor::getLength() const {
	return length;
}

// set the length of the section of floor
void Floor::setLength(int new_length){
	length = new_length;
}

// return true if position falls on floor, false otherwise
bool Floor::onMapObject(df::Position pos) const{

	int x = pos.getX();
	int y = pos.getY();
		
	if (y == this->getPosition().getY() &&
		x >= this->getPosition().getX() &&
		x <= this->getPosition().getX() + length) {
		return true;
	}
	return false;
}

void Floor::draw() {
	df::GraphicsManager &gm = df::GraphicsManager::getInstance();

	int x = getPosition().getX();
	int y = getPosition().getY();

	for (int i = 0; i < length; i++) {
		gm.drawCh(df::Position(x + i, y), FLOOR_CHAR, df::Color::WHITE);
	}
}