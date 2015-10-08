#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "MapObject.h"

const char FLOOR_CHAR = '_';

class Floor : public MapObject {

private:
	int length; // length of the section of floor

public:
	// constructor for floor needs length of section of floor
	Floor(df::Position init_pos, int init_length);

	// get the length of the section of floor
	int getLength() const;

	// set the length of the section of floor
	void setLength(int new_length);

	// return true if position falls on floor, false otherwise
	bool onMapObject(df::Position pos) const;

	// Draw the floor in place
	void draw();

};

#endif