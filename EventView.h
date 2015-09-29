#ifndef __EVENT_VIEW_H__
#define __EVENT_VIEW_H__

// game engine includes
#include "Event.h"

namespace df{

	#define DF_VIEW_EVENT "__view__"	// view event type

	class EventView : public Event {
	private:
		string tag;  // Tag to associate.
		int value;   // Value for view.
		bool delta;  // True if change in value, else replace value.

	public:
		// Create view event with tag VIEW_EVENT, value 0 and delta false.
		EventView();

		// Create view event with tag, value and delta as indicated.
		EventView(string new_tag, int new_value, bool new_delta);

		// Set tag to new tag.
		void setTag(string new_tag);

		// Get tag.
		string getTag() const;

		// Set value to new value.
		void setValue(int new_value);

		// Get value.
		int getValue() const;

		// Set delta to new delta.
		void setDelta(bool new_delta);

		// Get delta.
		bool getDelta() const;
	};
}
#endif