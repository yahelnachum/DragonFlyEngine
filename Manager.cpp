// game engine includes
#include "Manager.h"
#include "WorldManager.h"
#include "LogManager.h"

// constructor, sets started to false
df::Manager::Manager(){
	is_started = false;
}

// destructor
df::Manager::~Manager(){

}

// Set type identifier of Manager.
void df::Manager::setType(std::string type){
	df::Manager::type = type;
}

// Get type identifier of Manager.
std::string df::Manager::getType() const{
	return type;
}

// Startup Manager.
// Return 0 if ok, else negative number.
int df::Manager::startUp(){
	is_started = true;
	return 0;
}

// Shutdown Manager.
void df::Manager::shutDown(){
	is_started = false;
}

// Return true when startUp() was executed ok, else false.
bool df::Manager::isStarted() const{
	return is_started;
}

// Send event to all Objects.
// Return count of number of events sent.
int df::Manager::onEvent(const Event *p_event){
	
	df::LogManager::getInstance().writeLog("Event being sent: %s\n", p_event->getType().c_str());

	int count = 0;

	// get all objects and send them the event
	df::ObjectList all_objects = df::WorldManager::getInstance().getAllObjects();
	df::ObjectListIterator oli(&all_objects);
	while(!oli.isDone()){
		oli.currentObject()->eventHandler((df::Event *) p_event);
		oli.next();
		count++;
	}

	// return how many objects used the event
	return count;
}