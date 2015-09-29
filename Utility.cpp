// system includes
#include <sstream>
using std::stringstream;

// game engine includes
#include "WorldManager.h"

#include "Utility.h"
#include "Box.h"
#include "Object.h"

// Return true if two positions intersect, else false.
bool df::Utility::positionsIntersect(df::Position p1, df::Position p2){
	if (p1.getX() == p2.getX() &&
		p1.getY() == p2.getY())
		return true;

	return false;
}

// Return true if two boxes intersect, else false
bool df::Utility::boxIntersectsBox(df::Box b1, df::Box b2){
	// Test horizontal overlap (x_overlap).
	bool x_overlap = (b2.getCorner().getX() <= b1.getCorner().getX() && b1.getCorner().getX() <= b2.getCorner().getX() + b2.getHorizontal() - 1) ||     // Either left side of A in B?
					 (b1.getCorner().getX() <= b2.getCorner().getX() && b2.getCorner().getX() <= b1.getCorner().getX() + b1.getHorizontal() - 1);     // Or left side of B in A?
	
	// Test vertical overlap (y_overlap).
	bool y_overlap = (b2.getCorner().getY() <= b1.getCorner().getY() && b1.getCorner().getY() <= b2.getCorner().getY() + b2.getVertical() - 1) ||     // Either top side of A in B?
					 (b1.getCorner().getY() <= b2.getCorner().getY() && b2.getCorner().getY() <= b1.getCorner().getY() + b1.getVertical() - 1);     // Or top side of B in A?
	
	if (x_overlap && y_overlap)
		return true;         // Boxes do intersect.
	else
		return false;        // Boxes do not intersect.

}

// Convert relative bounding Box for Object to absolute world Box.
df::Box df::Utility::getWorldBox(df::Object *p_o){
	Box temp_box = p_o->getBox();
	Position corner = temp_box.getCorner();
	corner.setX(corner.getX() + p_o->getPosition().getX());
	corner.setY(corner.getY() + p_o->getPosition().getY());
	temp_box.setCorner(corner);

	return temp_box;
}

// Convert relative bounding Box for Object to absolute world Box 
// at Position where.
df::Box df::Utility::getWorldBox(df::Object *p_o, df::Position where){
	Box temp_box = p_o->getBox();
	Position corner = temp_box.getCorner();
	corner.setX(where.getX());
	corner.setY(where.getY());
	temp_box.setCorner(corner);

	return temp_box;

}

// Convert world position to view position.
df::Position df::Utility::worldToView(Position world_pos){
	df::Position view_origin = df::WorldManager::getInstance().getView().getCorner();
	int view_x = view_origin.getX();
	int view_y = view_origin.getY();
	Position view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
	return view_pos;

}

// Convert view position to world position.
df::Position df::Utility::viewToWorld(Position view_pos){
	df::Position view_origin = df::WorldManager::getInstance().getView().getCorner();
	int view_x = view_origin.getX();
	int view_y = view_origin.getY();
	Position world_pos(view_pos.getX() + view_x, view_pos.getY() + view_y);
	return world_pos;
}

// Convert int to a string, returning string.
string df::Utility::intToString(int number) {
	stringstream ss;  // Create stringstream.
	ss << number;     // Add number to stream.
	return ss.str();  // Return string with contents of stream.
}
