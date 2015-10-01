#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

#include "MapObject.h"
#include "Manager.h"
#include "Position.h"

const int MAX_MAP_OBJECTS = 128;

class MapManager : df::Manager {
private:
	int mo_count = 0;			// count of number of map objects
	MapObject *p_map_o[MAX_MAP_OBJECTS];
	MapManager();
	MapManager(MapManager const&);			// No copying.
	void operator=(MapManager const&); // No assignment.


public:
	~MapManager();

	// Start up the LogManager (open logfile "dragonfly.log").
	int startUp();

	// Shut down the Map manager (close logfile).
	void shutDown();

	// Get instance of the MapManager
	static MapManager &getInstance();

	// return true if the position falls anywhere on the map
	bool onMap(df::Position pos) const;

	// add a MapObject to the MapObject list
	int addMapObject(MapObject *m_o);

	// remove a MapObject from the MapObject list
	int removeMapObject(MapObject *m_o);

	// load level 1 of the map
	int loadMap1();

};

#endif