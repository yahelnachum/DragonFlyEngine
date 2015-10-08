#include "MapObject.h"

// constant character for drawing on screen
const char LADDER_CHAR = '|';

class Ladder : public MapObject {

private:
	int length; // length of the section of Ladder

public:
	// constructor for Ladder needs length of section of Ladder
	Ladder(df::Position init_pos, int init_length);

	// get the length of the section of Ladder
	int getLength() const;

	// set the length of the section of Ladder
	void setLength(int new_length);

	// return true if position falls on Ladder, false otherwise
	bool onMapObject(df::Position pos) const;

	// Draw the Ladder in place
	void draw();

};