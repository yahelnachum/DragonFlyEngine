// game engine includes
#include "EventKeyboard.h"

// default constructor
df::EventKeyboard::EventKeyboard(){
	setType(DF_KEYBOARD_EVENT);
}

// Set key in event.
void df::EventKeyboard::setKey(Input::Key new_key){
	key_val = new_key;
}

// Get key from event.
df::Input::Key df::EventKeyboard::getKey() const{
	return key_val;
}

// Set keyboard event action.
void df::EventKeyboard::setKeyboardAction(EventKeyboardAction new_action){
	keyboard_action = new_action;
}

// Get keyboard event action.
df::EventKeyboardAction df::EventKeyboard::getKeyboardAction() const{
	return keyboard_action;
}