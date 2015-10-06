#include "Shelf.h"

// default constructor
Shelf::Shelf(df::Position pos, bool bottomShelf){
	if (bottomShelf)
		setType("BottomShelf");
	else
		setType("Shelf");
	setPosition(pos);
	setSolidness(df::SOFT);
}