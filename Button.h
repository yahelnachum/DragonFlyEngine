#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "MapObject.h"
#include "Wall.h"
#include "EventCollision.h"

const int MAX_WALL_COUNT = 5;

class Button : public MapObject {

private:
	int wall_count;						// number of walls currently stored
	Wall *p_wall[MAX_WALL_COUNT];		// array of stored walls
	bool activated = false;				// has the button been pressed

public:
	Button();
	
	// event handler
	int eventHandler(df::Event *p_e);

	// handle collision event
	int eventCollision(const df::EventCollision *p_e);

	// add a wall to be controlled by this button
	int addWall(Wall *new_wall);

	// remove a wall from this buttons control
	int removeWall(Wall *rem_wall);

	// activate all walls
	void activateWalls();

	// deactivate all walls
	void deactivateWalls();

};

#endif