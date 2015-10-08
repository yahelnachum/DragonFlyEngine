// game engine includes
#include "ResourceManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventView.h"

// IHOP includes
#include "Shelf.h"
#include "Points.h"
#include "Block.h"

// default constructor
Shelf::Shelf(df::Position pos, bool bottomShelf){
	// set type if it is regular shelf or bottom shelf
	if (bottomShelf){
		setType("BottomShelf");
		this->bottomShelf = bottomShelf;
	}
	else
		setType("Shelf");

	// set other attributes
	setPosition(pos);
	setSolidness(df::SOFT);
}

// handle events
int Shelf::eventHandler(df::Event *p_e){
	// if its a bottom shelf and a collision event then handle it in eventCollision function
	if (bottomShelf && p_e->getType() == DF_COLLISION_EVENT){
		return eventCollision(static_cast <df::EventCollision *> (p_e));
	}
	return 0;
}

// handles collision events
int Shelf::eventCollision(df::EventCollision *p_e){
	// if collision is with block type then move bottom shelf up
	if (p_e->getObject1()->getType() == BLOCK_TYPE ||
		p_e->getObject2()->getType() == BLOCK_TYPE){
		setPosition(df::Position(getPosition().getX(), getPosition().getY() - 1));
		moveCount++;

		// if shelf has moved 4 times then add 50 points to score
		if (moveCount >= 4){
			df::EventView *e = new df::EventView();
			e->setTag(POINTS_STRING);
			e->setDelta(true);
			e->setValue(50);

			df::WorldManager::getInstance().onEvent(e);
		}
		return 1;
	}
	return 0;
}