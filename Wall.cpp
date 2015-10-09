// game engine includes
#include "GraphicsManager.h"

// IHOP includes
#include "Wall.h"


// constructor for Ladder needs length of section of Ladder
Wall::Wall(df::Position init_pos, int init_length){
	setPosition(init_pos);
	length = init_length;
	setType("Wall");
}

// get boolean corresponding to if the wall is active
bool Wall::getActive() const {
	return active;
}

// set boolean corresponding to if the wall is active
void Wall::setActive(bool new_active){
	active = new_active;
}

// get the length of the section of Ladder
int Wall::getLength() const {
	return length;
}

// set the length of the section of Ladder
void Wall::setLength(int new_length){
	length = new_length;
}

// return true if position falls on Ladder, false otherwise
bool Wall::onMapObject(df::Position pos) const{
	if (active) {
		int x = pos.getX();
		int y = pos.getY();

		if (x == this->getPosition().getX() &&
			y >= this->getPosition().getY() &&
			y <= this->getPosition().getY() + length) {
			return true;
		}
	}
	return false;
}

void Wall::draw() {
	if (active) {
		df::GraphicsManager &gm = df::GraphicsManager::getInstance();

		int x = getPosition().getX();
		int y = getPosition().getY();

		for (int i = 0; i < length; i++) {
			gm.drawCh(df::Position(x, y + i), WALL_CHAR, df::Color::RED);
		}
	}
}