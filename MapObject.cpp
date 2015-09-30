#include "MapObject.h"
#include "MapManager.h"

MapObject::MapObject(){
	setSolidness(df::SPECTRAL);
	setAltitude(0);
	setType("Map Object");
	MapManager &mm = MapManager::getInstance();
	mm.addMapObject(this);
}

MapObject::~MapObject(){
	MapManager &mm = MapManager::getInstance();
	mm.removeMapObject(this);
}

bool MapObject::onMapObject(df::Position pos){
	return true;
}
