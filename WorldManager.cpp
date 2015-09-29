// game engine includes
#include "WorldManager.h"
#include "LogManager.h"
#include "GraphicsManager.h"

#include "ViewObject.h"

#include "EventCollision.h"
#include "EventOut.h"

#include "Utility.h"

// constructor, set type of manager
df::WorldManager::WorldManager(){
	// Private (a singleton).
	setType("WorldManager");
}

// overloaded constructor,
df::WorldManager::WorldManager(WorldManager const&){
	// No assignment.
	setType("WorldManager");
}

// Get the one and only instance of the WorldManager.
df::WorldManager &df::WorldManager::getInstance(){
	static WorldManager world_manager;
	return world_manager;
}

// Startup game world (initialize everything to empty).
// Return 0.
int df::WorldManager::startUp(){

	// write to log that manager was started up
	df::LogManager::getInstance().writeLog("WorldManager::startUp starting up\n");
	updates.clear();
	deletions.clear();

	return Manager::startUp();
}

// Shutdown game world (delete all game world Objects).
void df::WorldManager::shutDown(){
	
	// write to log that manager is deleting objects
	df::LogManager::getInstance().writeLog("WorldManager::shutDown deleting all objects\n");
	
	// Delete all game objects.
	df::ObjectList objectList = updates; // Copy list so you can delete during iteration.
	df::ObjectListIterator listIterator(&objectList);
	for (listIterator.first(); !listIterator.isDone(); listIterator.next()){
		delete listIterator.currentObject();
	}

	// shut down super
	Manager::shutDown();
}

// Add Object to world. Return 0 if ok, else -1.
int df::WorldManager::insertObject(df::Object *p_o){
	// write to log inserted object
	df::LogManager::getInstance().writeLog("WorldManager::insertObject inserted type: %s, id: %d\n", p_o->getType().c_str(), p_o->getId());
	return updates.insert(p_o);
}

// Remove Object from world. Return 0 if ok, else -1.
int df::WorldManager::removeObject(df::Object *p_o){
	// write to log removed object
	df::LogManager::getInstance().writeLog("WorldManager::removeObject removed type: %s, id: %d\n", p_o->getType().c_str(), p_o->getId());
	return updates.remove(p_o);
}

// Return list of all Objects in world.
df::ObjectList df::WorldManager::getAllObjects(void) const{
	return updates;
}

// Update world.
// Delete Objects marked for deletion.
void df::WorldManager::update(){
	
	// write to log
	df::LogManager::getInstance().writeLog("WorldManager::update updating world and deleting marked objects\n");
	
	// Update object positions based on their velocities.
	df::ObjectListIterator li(&updates);
	while (!li.isDone()){
		int x = li.currentObject()->getXVelocityStep();
		int y = li.currentObject()->getYVelocityStep();

		// if velocities are not 0 then move object to new position
		if (x != 0 || y != 0){
			df::Position oldP = li.currentObject()->getPosition();
			df::Position newP = df::Position(oldP.getX() + x, oldP.getY() + y);
			moveObject(li.currentObject(), newP);
		}

		li.next();
	}

	// delete marked objects
	li = df::ObjectListIterator(&deletions);
	for (li.first(); !li.isDone(); li.next()){
		delete li.currentObject();
	}

	// clear deletions list
	deletions.clear();
}

// Indicate object is to be deleted at end of current game update.
// Return 0 if ok, else -1.
int df::WorldManager::markForDelete(Object *p_o){
	
	// Object might already have been marked, so only add once.
	df::ObjectListIterator li(&deletions);
	for (li.first(); !li.isDone(); li.next()){
		if (li.currentObject() == p_o)
			return 0;
	}

	// write to log that object has been marked for deletion
	df::LogManager::getInstance().writeLog("WorldManager::markForDelete marking %s:%d for deletion\n", p_o->getType().c_str(), p_o->getId());

	// Object not in list, so add.
	return deletions.insert(p_o);
}

// Draw all objects.
void df::WorldManager::draw(){

	// get iterator of objects to draw
	df::ObjectListIterator oli(&updates);

	// iterate though each altitude
	for (int alt = 0; alt <= MAX_ALTITUDE; alt++){

		// iterate through each object
		// if object is at current altitude then draw
		while (!oli.isDone()){
			if (oli.currentObject()->getAltitude() == alt){
				// Bounding box coordinates are relative to Object,
				// so convert to world coordinates.
				Box temp_box = df::Utility::getWorldBox(oli.currentObject());

				// Only draw if Object would be visible on screen (intersects view).
				if (df::Utility::boxIntersectsBox(temp_box, view) ||
					dynamic_cast <ViewObject *> (oli.currentObject())){
					oli.currentObject()->draw();
				}

			}
			oli.next();
		}
		oli.first();
	}
}

// Return list of Objects collided with at Position `where'.
// Collisions only with solid Objects.
// Does not consider if p_o is solid or not.
df::ObjectList df::WorldManager::isCollision(df::Object *p_o, df::Position where) const{
	// Make empty list.
	ObjectList collision_list = ObjectList();

	// Iterate through all objects.
	ObjectListIterator i(&updates);

	// World position bounding box for object at where
	Box b = df::Utility::getWorldBox(p_o, where);

	while (!i.isDone()){
		Object *p_temp_o = i.currentObject();

		// World position bounding box for other object
		Box b_temp = df::Utility::getWorldBox(p_temp_o);

		if (p_temp_o != p_o){	// Do not consider self.

			// Same location and both solid?
			if (df::Utility::boxIntersectsBox(b, b_temp) && p_temp_o->isSolid()){
				collision_list.insert(p_temp_o);
			}	// No solid collision.
		}	// Not self.

		i.next();
	}	// End iterate.  

	return collision_list;
}

// Move Object.
// If no collision with solid, move ok else don't move.
// If p_go is Spectral, move ok.
// Return 0 if move ok, else -1 if collision with solid.
int df::WorldManager::moveObject(df::Object *p_o, Position where){

	bool do_move = true;

	if (p_o->isSolid()){ // Need to be solid for collisions.

		// Get collisions.
		ObjectList list = isCollision(p_o, where);
		if (!list.isEmpty()){

			// Iterate over list.
			ObjectListIterator i(&list);
			while (!i.isDone()){
				Object *p_temp_o = i.currentObject();

				// Create collision event.
				EventCollision c(p_o, p_temp_o, where);

				// Send to both objects.
				p_o->eventHandler(&c);
				p_temp_o->eventHandler(&c);

				// If both HARD, then cannot move.
				if (p_o->getSolidness() == df::HARD && p_temp_o->getSolidness() == df::HARD){
					do_move = false;
				}

				i.next();
			} // End iterate.

			if (do_move == false){
				return -1; // Move not allowed.
			}

		} // No collision.
	} // Object not solid.

	// calculate whether or not the object 
	// and position are inside or outside
	df::GraphicsManager &gm = df::GraphicsManager::getInstance();
	int o_pos_x = p_o->getPosition().getX();
	int o_pos_y = p_o->getPosition().getY();
	int window_h = gm.getHorizontal();
	int window_v = gm.getVertical();
	bool obj_inside = (o_pos_x > 0 && o_pos_x < window_h) &&
		(o_pos_y > 0 && o_pos_y < window_v);
	bool where_outside = (where.getX() <= 0 || where.getX() >= window_h) ||
		(where.getY() <= 0 || where.getY() >= window_v);

	if (obj_inside && where_outside){
		// Generate out of bounds event and
		// send to object.
		EventOut ov;
		p_o->eventHandler(&ov);
	}

	// If here, no collision so allow move.
	p_o->setPosition(where);

	// If view is following this object, adjust view.
	if (p_view_following == p_o){
		setViewPosition(p_o->getPosition());
	}

	return 0; // Move was ok.
}

// Get game world boundary.
df::Box df::WorldManager::getBoundary() const{
	return boundary;
}

// Set game world boundary.
void df::WorldManager::setBoundary(Box new_boundary){
	boundary = new_boundary;
}

// Get player view of game world.
df::Box df::WorldManager::getView() const{
	return view;
}

// Set player view of game world.
void df::WorldManager::setView(Box new_view){
	view = new_view;
}

// Set view to center screen on Position view_pos.
// View edge will not go beyond world boundary.
void df::WorldManager::setViewPosition(Position view_pos){
	// Make sure horizontal not out of world boundary.

	int x = view_pos.getX() - view.getHorizontal() / 2;
	if (x + view.getHorizontal() > boundary.getHorizontal()){
		x = boundary.getHorizontal() - view.getHorizontal();
	}
	if (x < 0){
		x = 0;
	}

	// Make sure vertical not out of world boundary.
	int y = view_pos.getY() - view.getVertical() / 2;
	if (y + view.getVertical() > boundary.getVertical()){
		y = boundary.getVertical() - view.getVertical();
	}
	if (y < 0){
		y = 0;
	}

	// Set view.
	Position new_corner(x, y);
	view.setCorner(new_corner);

}

// Set view to center screen on Object.
// Set to NULL to stop following.
// If p_new_view_following not legit, return -1 else return 0.
int df::WorldManager::setViewFollowing(Object *p_new_view_following){
	// Set to NULL to turn `off' following.
	if (p_new_view_following == NULL){
		p_view_following = NULL;
		return 0;
	}

	// ...
	// Iterate over all Objects.   Make sure p_new_view_following
	// is one of the Objects, then set found to true.
	// ...
	bool found = false;

	df::ObjectList ol = df::WorldManager::getInstance().getAllObjects();
	df::ObjectListIterator oli(&ol);
	while (!oli.isDone()){
		if (oli.currentObject() == p_new_view_following){
			found = true;
		}
		oli.next();
	}

	// If found, adjust attribute accordingly and set view position.
	if (found){
		p_view_following = p_new_view_following;
		setViewPosition(p_view_following->getPosition());
		return 0;
	}

	// If we get here, was not legit.  Don't change current view.
	return -1;

}