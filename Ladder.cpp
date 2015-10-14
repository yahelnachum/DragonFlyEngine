// game engine includes
#include "GraphicsManager.h"

// IHOP includes
#include "Ladder.h"


// constructor for Ladder needs length of section of Ladder
Ladder::Ladder(df::Position init_pos, int init_length){
	setPosition(init_pos);
	length = init_length;
	setType("Ladder");
}

// get the length of the section of Ladder
int Ladder::getLength() const {
	return length;
}

// set the length of the section of Ladder
void Ladder::setLength(int new_length){
	length = new_length;
}

// return true if position falls on Ladder, false otherwise
bool Ladder::onMapObject(df::Position pos) const{
	int x = pos.getX();
	int y = pos.getY();

	if (x == this->getPosition().getX() &&
		y >= this->getPosition().getY() &&
		y <= this->getPosition().getY() + length -1) {
		return true;
	}
	return false;
}

void Ladder::draw() {
	df::GraphicsManager &gm = df::GraphicsManager::getInstance();

	int x = getPosition().getX();
	int y = getPosition().getY();

	for (int i = 0; i < length; i++) {
		gm.drawCh(df::Position(x, y + i), LADDER_CHAR, df::Color::WHITE);
	}
}