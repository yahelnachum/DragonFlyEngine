#ifndef __START_SCREEN_H__
#define __START_SCREEN_H__

#include "Object.h"

class StartScreen : public df::Object {
private:

public:
	// default constructor
	StartScreen();

	// event handler
	int eventHandler(df::Event *p_e);
};
#endif