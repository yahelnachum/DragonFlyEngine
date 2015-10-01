#include "MapManager.h"
#include "ObjectListIterator.h"
#include "LogManager.h"

MapManager::MapManager(){
	
}

MapManager::~MapManager(){
}

int MapManager::startUp(){
	Manager::startUp();
	setType("Map Manager");
	return 0;
}

void MapManager::shutDown(){
	Manager::shutDown();
}

MapManager &MapManager::getInstance(){
	static MapManager map;
	return map;
}


// return true if the position falls anywhere on the map
bool MapManager::onMap(df::Position pos) const {
	df::LogManager &lm = df::LogManager::getInstance();

	for (int i = 0; i < mo_count; i++) {
		MapObject *currentMO = p_map_o[i];
		if (currentMO->onMapObject(pos)) {
			return true;
		}
	}

	return false;
}

// add a MapObject to the MapObject list
int MapManager::addMapObject(MapObject *m_o){
	p_map_o[mo_count] = m_o;
	mo_count++;
	return 0;
}

// remove a MapObject from the MapObject list
int MapManager::removeMapObject(MapObject *m_o){
	for (int i = 0; i < mo_count-1; i++) {
		if (p_map_o[i] == m_o) {
			for (int j = i; j < mo_count - 2; j++) {
				p_map_o[j] = p_map_o[j + 1];
				return 0;
			}
		}
	}
	return -1;
}