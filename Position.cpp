#include <cmath>

// game engine includes
#include "Position.h"

// Create object at 2d location (x,y).
df::Position::Position(int init_x, int init_y){
	x = init_x;
	y = init_y;
}

// Default 2d (x,y) location is (0,0).
df::Position::Position(){
	x = 0;
	y = 0;
}

// Get/set horizontal coordinate.
void df::Position::setX(int new_x){
	x = new_x;
}

int df::Position::getX() const{
	return x;
}

// Get/set vertical coordinate.
void df::Position::setY(int new_y){
	y = new_y;
}

int df::Position::getY() const{
	return y;
}

// Set horizontal & vertical coordinates.
void df::Position::setXY(int new_x, int new_y){
	x = new_x;
	y = new_y;
}

bool df::Position::equalTo(df::Position pos){
	if (this->getX() == pos.getX() && this->getY() == pos.getY()){
		return true;
	}
	return false;
}

int df::Position::getManhattanDistance(df::Position pos){
	return abs(pos.getX() - getX()) + abs(pos.getY() - getY());
}