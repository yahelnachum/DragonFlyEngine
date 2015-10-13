#ifndef __LIVES_H__
#define __LIVES_H__

// game engine includes
#include "ViewObject.h"
#include "Event.h"

// constant defined type
#define LIVES_STRING "Lives"

class Lives : public df::ViewObject {

	public:
		/* creates a points object to keep track of score */
		Lives();

		/* used to update the viewobject every couple of frames*/
		int eventHandler(df::Event *p_e);
};
#endif