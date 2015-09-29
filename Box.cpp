// game engine includes
#include "Box.h"

// Create box with (0,0) for the corner, and 0 for horiz and vert.
df::Box::Box(){
	corner = df::Position(0,0);
	horizontal = 0;
	vertical = 0;
}

// Create box with an upper-left corner, horiz and vert sizes.
df::Box::Box(df::Position init_corner, int init_horizontal, int init_vertical){
	corner = init_corner;
	horizontal = init_horizontal;
	vertical = init_vertical;
}

// Get upper left corner of box.
df::Position df::Box::getCorner() const{
	return corner;
}

// Set upper left corner of box.
void df::Box::setCorner(df::Position new_corner){
	corner = new_corner;
}

// Get horizontal size of box.
int df::Box::getHorizontal() const{
	return horizontal;
}

// Set horizontal size of box.
void df::Box::setHorizontal(int new_horizontal){
	horizontal = new_horizontal;
}

// Get vertical size of box.
int df::Box::getVertical() const{
	return vertical;
}

// Set vertical size of box.
void df::Box::setVertical(int new_vertical){
	vertical = new_vertical;
}