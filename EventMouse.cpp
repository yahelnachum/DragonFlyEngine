// game engine includes
#include "EventMouse.h"

// default constructor
df::EventMouse::EventMouse(){
	setType(DF_MOUSE_EVENT);
}

// Load mouse event's action.
void df::EventMouse::setMouseAction(EventMouseAction new_mouse_action){
	mouse_action = new_mouse_action;
}

// Get mouse event's action.
df::EventMouseAction df::EventMouse::getMouseAction() const{
	return mouse_action;
}

// Set mouse event's button.
void df::EventMouse::setMouseButton(EventMouseButton new_mouse_button){
	mouse_button = new_mouse_button;
}

// Get mouse event's button.
df::EventMouseButton df::EventMouse::getMouseButton() const{
	return mouse_button;
}

// Set mouse event's position.
void df::EventMouse::setMousePosition(df::Position new_mouse_xy){
	mouse_xy = new_mouse_xy;
}

// Get mouse event's y position.
df::Position df::EventMouse::getMousePosition() const{
	return mouse_xy;
}