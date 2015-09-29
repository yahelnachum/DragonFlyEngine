#ifndef __EVENT_STEP_H__
#define __EVENT_STEP_H__

// game engine includes
#include "Event.h"

#define DF_STEP_EVENT "__step__"

namespace df{
	class EventStep : public Event{
	private:
		int step_count; // Iteration number of game loop.

	public:
		// constructor
		EventStep();

		// overloaded constructor to set initial step count
		EventStep(int init_step_count);

		// set step count to given int
		void setStepCount(int new_step_count);

		// returns step count
		int getStepCount() const;

	};
}
#endif