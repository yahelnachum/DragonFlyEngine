#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Object.h"
#include "Wall.h"

class Button : public df::Object {

private:
	int wall_count;
	Wall *wall[5];

public:
	Button();

	~Button();

	void addWall(Wall *new_wall);

	void removeWall(Wall *rem_wall);

	void activateWalls();

	void deactivateWalls();

};

#endif