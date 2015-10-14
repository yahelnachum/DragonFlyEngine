#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

// game engine includes 
#include "Manager.h"
#include "Position.h"

// IHOP includes
#include "MapObject.h"

// maximum amount of map objects
const int MAX_MAP_OBJECTS = 128;

class MapManager : df::Manager {
private:
	int stackCounter = 0;					// count of current number of blocks stacked
	int stackNeeded = 0;					// number of stacks needed to get to next level
	int currentLevel = 0;					// current level that the player is on
	int mo_count = 0;						// count of number of map objects
	MapObject *p_map_o[MAX_MAP_OBJECTS];	// array of map objects
	MapManager();							// no construction
	MapManager(MapManager const&);			// No copying.
	void operator=(MapManager const&);		// No assignment.


public:
	// destructor
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

	// remove all currently active map objects
	int removeAllMapObject();

	// get number of stacks needed to complete a level
	int getStackCounter() const;

	// add one to stack counter
	void addStackToCounter();

	// set the number stacks that need to be complete to finish a level
	void setNeededStack(int new_stack_needed);

	// load the next level
	int loadNextLevel();

	// load level 1 of the map
	int loadMap1();

	// load level 2 of the map
	int loadMap2();

	// load level 3 of the map
	int loadMap3();

	// return array of mapobjects
	MapObject **getMapObjects();
};

#endif