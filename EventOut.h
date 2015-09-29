#ifndef __EVENT_OUT_H__
#define __EVENT_OUT_H__

// game engine include
#include "Event.h"

namespace df{

	// string type
	#define DF_OUT_EVENT "__out__"

	class EventOut : public Event {

	public:
		// default constructor
		EventOut();

	};
}
#endif