// IHOP includes
#include "MapObject.h"
#include "MapManager.h"

// constructor
MapObject::MapObject(){
	// set attributes
	setSolidness(df::SPECTRAL);
	setAltitude(0);
	setType("Map Object");

	// add map object ot map
	MapManager &mm = MapManager::getInstance();
	mm.addMapObject(this);
}

// destructor
MapObject::~MapObject(){
	MapManager &mm = MapManager::getInstance();
	mm.removeMapObject(this);
}

// check if position is on object
bool MapObject::onMapObject(df::Position pos) const{
	return false;
}
