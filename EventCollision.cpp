// game engine includes
#include "LogManager.h"

#include "EventCollision.h"

// Create collision event at (0,0) with obj1 and obj2 NULL.
df::EventCollision::EventCollision(){
	setType(DF_COLLISION_EVENT);
}

// Create collision event between o1 and o2 at position p.
// Object o1 `caused' collision by moving into object o2.
df::EventCollision::EventCollision(Object *p_o1, Object *p_o2, Position p){
	p_obj1 = p_o1;
	p_obj2 = p_o2;
	pos = p;

	df::LogManager::getInstance().writeLog("EventCollision::EventCollision Object1: type:%s, id:%d, solidness:%d Object2: type:%s, id:%d, solidness:%d\n", p_o1->getType().c_str(), p_o1->getId(), p_o1->getSolidness(), p_o2->getType().c_str(), p_o2->getId(), p_o2->getSolidness());
}

// Return object that caused collision.
df::Object *df::EventCollision::getObject1() const{
	return p_obj1;
}

// Set object that caused collision.
void df::EventCollision::setObject1(Object *p_new_o1){
	p_obj1 = p_new_o1;
}

// Return object that was collided with.
df::Object *df::EventCollision::getObject2() const{
	return p_obj2;
}

// Set object that was collided with.
void df::EventCollision::setObject2(Object *p_new_o2){
	p_obj2 = p_new_o2;
}

// Return position of the collision.
df::Position df::EventCollision::getPosition() const{
	return pos;
}

// Set position of collision.
void df::EventCollision::setPosition(df::Position new_pos){
	pos = new_pos;
}