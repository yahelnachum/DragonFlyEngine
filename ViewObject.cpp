// game engine includes
#include "ViewObject.h"
#include "GraphicsManager.h"
#include "WorldManager.h"

#include "Utility.h"

#include "EventView.h"

// Construct ViewObject.
// Object settings: SPECTRAL, max alt.
// ViewObject defaults: border, top_center, default color.
df::ViewObject::ViewObject(){
	// Initialize Object attributes.
	setSolidness(SPECTRAL);
	setAltitude(MAX_ALTITUDE);
	setType("ViewObject");

	// Initialize ViewObject attributes.
	setValue(0);
	setBorder(true);
	setLocation(TOP_CENTER);
	setColor(COLOR_DEFAULT);
	setViewString("");
}

// Draw view string and value.
void df::ViewObject::draw(){
	string temp_str;
	
	// Display view string + value.
	if (border)
		temp_str = " " + getViewString() + " " + df::Utility::intToString(value) + " ";
	else
		temp_str = getViewString() + " " + df::Utility::intToString(value);
	
	// Draw centered at position.
	Position pos = df::Utility::viewToWorld(getPosition());
	df::GraphicsManager::getInstance().drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());
	if (this->border){
		// Draw box around display.
		/******still need to finish******/
	}
}

// Handle `view' events if tag matches view_string (others ignored).
// Return 0 if ignored, else 1 if handled.
int df::ViewObject::eventHandler(Event *p_e){

	// See if this is a `view' event.
	if (p_e->getType() == DF_VIEW_EVENT){

		EventView *p_ve = static_cast <EventView *> (p_e);

		// See if this event is meant for this object.
		if (p_ve->getTag() == getViewString()){

			if (p_ve->getDelta())
				setValue(getValue() + p_ve->getValue());  // Change in value.
			else
				setValue(p_ve->getValue());               // New value.
			
			// Event was handled.
			return 1;
		}

	}

	// If here, event was not handled. 
	return 0;
}

// General location of ViewObject on screen.
void df::ViewObject::setLocation(ViewObjectLocation new_location){
	df::Position p;
	int delta = 0;
	
	// Set new position based on location.
	switch (new_location){
	case TOP_LEFT:
		p.setXY(df::WorldManager::getInstance().getView().getHorizontal() * 1 / 6, 1);
		if (getBorder() == false){
			delta = -1;
		}
		break;
	case TOP_CENTER:
		p.setXY(df::WorldManager::getInstance().getView().getHorizontal() * 3 / 6, 1);
		if (getBorder() == false){
			delta = -1;
		}
		break;
	case TOP_RIGHT:
		p.setXY(df::WorldManager::getInstance().getView().getHorizontal() * 5 / 6, 1);
		if (getBorder() == false){
			delta = -1;
		}
		break;
	case CENTER_CENTER:
		p.setXY(df::WorldManager::getInstance().getView().getHorizontal() * 3 / 6, 
			df::WorldManager::getInstance().getView().getVertical() * 3 / 6);
		if (getBorder() == false){
			delta = 0;
		}
		break;
	case BOTTOM_LEFT:
		p.setXY(df::WorldManager::getInstance().getView().getHorizontal() * 1 / 6, 
			df::WorldManager::getInstance().getView().getVertical() - 1);
		if (getBorder() == false){
			delta = 1;
		}
		break;
	case BOTTOM_CENTER:
		p.setXY(df::WorldManager::getInstance().getView().getHorizontal() * 3 / 6, 
			df::WorldManager::getInstance().getView().getVertical() - 1);
		if (getBorder() == false){
			delta = 1;
		}
		break;
	case BOTTOM_RIGHT:
		p.setXY(df::WorldManager::getInstance().getView().getHorizontal() * 5 / 6, 
			df::WorldManager::getInstance().getView().getVertical() - 1);
		if (getBorder() == false){
			delta = 1;
		}
		break;
	}

	// Shift, as needed, based on border.
	p.setY(p.getY() + delta);

	// Set position of object to new position.
	setPosition(p);

	// Set new location.
	location = new_location;

}

// Get general location of ViewObject on screen.
df::ViewObjectLocation df::ViewObject::getLocation(){
	return location;
}

// Set view value.
void df::ViewObject::setValue(int new_value){
	value = new_value;
}

// Get view value.
int df::ViewObject::getValue() const{
	return value;
}

// Set view border (true = display border).
void df::ViewObject::setBorder(bool new_border){
	// check if borders are the same
	if (border != new_border) {

		border = new_border;

		// Reset location to account for bordersetting.
		setLocation(getLocation());
	}
}

// Get view border (true = display border).
bool df::ViewObject::getBorder(){
	return border;
}

// Set view color.
void df::ViewObject::setColor(df::Color new_color){
	color = new_color;
}

// Get view color.
df::Color df::ViewObject::getColor() const{
	return color;
}

// Set view display string.
void df::ViewObject::setViewString(string new_view_string){
	view_string = new_view_string;
}

// Get view display string.
string df::ViewObject::getViewString() const{
	return view_string;
}
