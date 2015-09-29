#ifndef __EVENT_KEYBOARD_H__
#define __EVENT_KEYBOARD_H__

// game engine includes
#include "Event.h"

namespace df{

	// string type
	const std::string DF_KEYBOARD_EVENT = "df::keyboard";

	// Types of keyboard actions Dragonfly recognizes.
	enum EventKeyboardAction {
		UNDEFINED_KEYBOARD_ACTION = -1, // Undefined
		KEY_PRESSED,                    // Was down
		KEY_RELEASED,                   // Was released
		KEY_DOWN,                       // Is down
	};

	// Keys Dragonfly recognizes.
	namespace Input { // New namespace for clarity
		enum Key {
			UNDEFINED_KEY = -1,
			SPACE, RETURN, ESCAPE, TAB, LEFTARROW, RIGHTARROW,
			UPARROW, DOWNARROW, PAUSE, MINUS, PLUS, TILDE, PERIOD,
			COMMA, SLASH, LEFTCONTROL, RIGHTCONTROL, LEFTSHIFT,
			RIGHTSHIFT, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11,
			F12, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R,
			S, T, U, V, W, X, Y, Z, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6,
			NUM7, NUM8, NUM9, NUM0,
		};
	} // end of namespace input

	class EventKeyboard : public Event {

	private:
		Input::Key key_val;                  // Key value.
		EventKeyboardAction keyboard_action;    // Key action.

	public:
		// default constructor
		EventKeyboard();

		// Set key in event.
		void setKey(Input::Key new_key);

		// Get key from event.
		Input::Key getKey() const;

		// Set keyboard event action.
		void setKeyboardAction(EventKeyboardAction new_action);

		// Get keyboard event action.
		EventKeyboardAction getKeyboardAction() const;
	};
}
#endif