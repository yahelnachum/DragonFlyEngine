// game engine includes
#include "Event.h"
	
// Create base event.
df::Event::Event(){
	event_type = "Event";
}

// Destructor.
df::Event::~Event(){

}

// Set event type.
void df::Event::setType(string new_type){
	event_type = new_type;
}

// Get event type.
string df::Event::getType() const{
	return event_type;
}