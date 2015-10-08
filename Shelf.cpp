#include "Shelf.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventView.h"
#include "Points.h"
#include "Block.h"

// default constructor
Shelf::Shelf(df::Position pos, bool bottomShelf){
	if (bottomShelf){
		setType("BottomShelf");
		this->bottomShelf = bottomShelf;
	}
	else
		setType("Shelf");
	setPosition(pos);
	setSolidness(df::SOFT);
}

int Shelf::eventHandler(df::Event *p_e){
	if (bottomShelf && p_e->getType() == DF_COLLISION_EVENT){
		return eventCollision(static_cast <df::EventCollision *> (p_e));
	}
	return 0;
}

int Shelf::eventCollision(df::EventCollision *p_e){
	if (p_e->getObject1()->getType() == BLOCK_TYPE ||
		p_e->getObject2()->getType() == BLOCK_TYPE){
		setPosition(df::Position(getPosition().getX(), getPosition().getY() - 1));
		moveCount++;

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