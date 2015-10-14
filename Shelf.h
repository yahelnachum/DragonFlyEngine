#ifndef __SHELF_H__
#define __SHELF_H__

// game engine includes
#include "MapObject.h"
#include "EventCollision.h"

class Shelf : public MapObject {
private:
	// count the number of blocks in the stack
	int moveCount = 0;

	// is this a bottom shelf
	bool bottomShelf = false;

public:
	// default constructor
	Shelf(df::Position pos, bool bottomShelf = false);

	// event handler
	int eventHandler(df::Event *p_e);

	// if collision event then go to this function
	int eventCollision(df::EventCollision *p_e);
};
#endif