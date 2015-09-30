#include "Map.h"
#include "ObjectListIterator.h"

Map::Map(){
	map_o_list.clear();
}

Map::~Map(){
	map_o_list.clear();
}

// return true if the position falls anywhere on the map
bool Map::onMap(df::Position pos) const {
	df::ObjectListIterator li(&map_o_list);

	for (li.first(); li.isDone(); li.next()) {
		MapObject *currentMO = (MapObject*) li.currentObject();
		if (currentMO->onMapObject(pos)) {
			return true;
		}
	}
	return false;
}

// add a MapObject to the MapObject list
int Map::addMapObject(MapObject *m_o){
	return map_o_list.insert(m_o);
}

// remove a MapObject from the MapObject list
int Map::removeMapObject(MapObject *m_o){
	return map_o_list.remove(m_o);
}

// returns ObjectList of all MapObject's
df::ObjectList Map::getMapObjectList() const{
	return map_o_list;
}
