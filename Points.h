#include "ViewObject.h"
#include "Event.h"

#define POINTS_STRING "Points"

class Points : public df::ViewObject {

	public:
		/* creates a points object to keep track of score */
		Points();

		/* used to update the viewobject every couple of frames*/
		int eventHandler(df::Event *p_e);
};