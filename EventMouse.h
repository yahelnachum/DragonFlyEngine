#ifndef __EVENT_MOUSE_H__
#define __EVENT_MOUSE_H__

// game engine includes
#include "Event.h"
#include "Position.h"

namespace df{
	
	// string type
	const std::string DF_MOUSE_EVENT = "df::mouse";

	// Set of mouse buttons recognized by Dragonfly.
	enum EventMouseButton {
		UNDEFINED_MOUSE_BUTTON = -1,
		LEFT,
		RIGHT,
		MIDDLE,
	};

	// Set of mouse actions recognized by Dragonfly.
	enum EventMouseAction {
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,
		PRESSED,
		MOVED,
	};

	class EventMouse : public Event {

	private:
		EventMouseAction mouse_action;  // Mouse action.
		EventMouseButton mouse_button;  // Mouse button.
		Position mouse_xy;              // Mouse (x,y) coordinates.

	public:
		// default constructor
		EventMouse();

		// Load mouse event's action.
		void setMouseAction(EventMouseAction new_mouse_action);

		// Get mouse event's action.
		EventMouseAction getMouseAction() const;

		// Set mouse event's button.
		void setMouseButton(EventMouseButton new_mouse_button);

		// Get mouse event's button.
		EventMouseButton getMouseButton() const;

		// Set mouse event's position.
		void setMousePosition(Position new_mouse_xy);

		// Get mouse event's y position.
		Position getMousePosition() const;
	};
}
#endif