#ifndef __VIEW_OBJECT_H__
#define __VIEW_OBJECT_H__

// system includes
#include <string>

using std::string;

// game engine includes
#include "Object.h"
#include "Event.h"

namespace df{
	// General location of ViewObject on screen.
	enum ViewObjectLocation {
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		CENTER_CENTER,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT,
	};

	class ViewObject : public Object {

	private:
		string view_string;  // Label for value (e.g., "Points").
		int value;           // Value displayed (e.g., points).
		bool border;         // True if border around display.
		df::Color color;           // Color for text.
		ViewObjectLocation location; // Location of ViewObject.	

	public:
		// Construct ViewObject.
		// Object settings: SPECTRAL, max alt.
		// ViewObject defaults: border, top_center, default color.
		ViewObject();

		// Draw view string and value.
		virtual void draw();

		// Handle `view' event if tag matches view_string (others ignored).
		// Return 0 if ignored, else 1 if handled.
		virtual int eventHandler(Event *p_e);

		// General location of ViewObject on screen.
		void setLocation(ViewObjectLocation new_location);

		// Get general location of ViewObject on screen.
		ViewObjectLocation getLocation();

		// Set view value.
		void setValue(int new_value);

		// Get view value.
		int getValue() const;

		// Set view border (true = display border).
		void setBorder(bool new_border);

		// Get view border (true = display border).
		bool getBorder();

		// Set view color.
		void setColor(df::Color new_color);

		// Get view color.
		df::Color getColor() const;

		// Set view display string.
		void setViewString(string new_view_string);

		// Get view display string.
		string getViewString() const;
	};
}
#endif