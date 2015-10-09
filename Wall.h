#ifndef __WALL_H__
#define __WALL_H__

#include "MapObject.h"

const char WALL_CHAR = 'H';

class Wall : public MapObject {

private:
	int length;
	bool active = true;

public:
	// constructor for Ladder needs length of section of Ladder
	Wall(df::Position init_pos, int init_length);

	// get boolean corresponding to if the wall is active
	bool getActive() const;

	// set boolean corresponding to if the wall is active
	void setActive(bool new_active);

	// get the length of the section of Ladder
	int getLength() const;

	// set the length of the section of Ladder
	void setLength(int new_length);

	// return true if position falls on Ladder, false otherwise
	bool onMapObject(df::Position pos) const;

	// Draw the Ladder in place
	void draw();
};

#endif