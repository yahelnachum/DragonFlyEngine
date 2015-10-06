#ifndef __SHELF_H__
#define __SHELF_H__

#include "Object.h"
#include "EventCollision.h"

class Shelf : public df::Object {
private:
public:
	// default constructor
	Shelf(df::Position pos, bool bottomShelf = false);

	// event handler
	//int eventHandler(df::Event *p_e);

	// if collision event then go to this function
	//int eventCollision(df::EventCollision *p_e);
};
#endif