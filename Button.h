#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Object.h"
#include "Wall.h"
#include "EventCollision.h"

const int MAX_WALL_COUNT = 5;

class Button : public df::Object {

private:
	int wall_count;
	Wall *p_wall[MAX_WALL_COUNT];
	bool activated = false;

public:
	Button();

	~Button();
	
	// event handler
	int eventHandler(df::Event *p_e);

	// handle collision event
	int eventCollision(const df::EventCollision *p_e);

	int addWall(Wall *new_wall);

	int removeWall(Wall *rem_wall);

	void activateWalls();

	void deactivateWalls();

};

#endif