#ifndef __MAPOBJECT_H__
#define __MAPOBJECT_H__

// game engine includes
#include "Object.h"

class MapObject : public df::Object {
private:

public:
	// constructor
	MapObject();

	// destructor
	~MapObject();

	// Returns true if the position is on the map object
	virtual bool onMapObject(df::Position pos) const;

};

#endif