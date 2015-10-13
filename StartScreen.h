#ifndef __START_SCREEN_H__
#define __START_SCREEN_H__

#include "Object.h"

class StartScreen : public df::Object {
private:
	int state = 0;	// 0 start screen on screen
					// 1 game running
public:
	// default constructor
	StartScreen();

	// event handler
	int eventHandler(df::Event *p_e);

	static void removeAllObjectsExceptThis();
};
#endif