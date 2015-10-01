#ifndef __MAPOBJECT_H__
#define __MAPOBJECT_H__

#include "Object.h"

class MapObject : public df::Object {
private:

public:
	MapObject();
	~MapObject();

	// Returns true if the position is on the map object
	virtual bool onMapObject(df::Position pos) const;

};

#endif