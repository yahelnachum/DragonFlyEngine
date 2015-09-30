#include "MapObject.h"
#include "ObjectList.h"
#include "Position.h"

class Map : df::Object {
private:
	df::ObjectList map_o_list;

public:
	Map();
	~Map();

	// return true if the position falls anywhere on the map
	bool onMap(df::Position pos) const;

	// add a MapObject to the MapObject list
	int addMapObject(MapObject *m_o);

	// remove a MapObject from the MapObject list
	int removeMapObject(MapObject *m_o);

	// returns ObjectList of all MapObject's
	df::ObjectList getMapObjectList() const;
};