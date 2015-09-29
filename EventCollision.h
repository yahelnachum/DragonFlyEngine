#ifndef __EVENT_COLLISION_H__
#define __EVENT_COLLISION_H__

// game engine includes
#include "Event.h"
#include "Object.h"

namespace df{

	// string type
	#define DF_COLLISION_EVENT "__collision__"

	class EventCollision : public Event {

	private:
		Position pos;   // Where collision occurred.
		Object *p_obj1; // Object moving, causing collision.
		Object *p_obj2; // Object being collided with.

	public:
		// Create collision event at (0,0) with obj1 and obj2 NULL.
		EventCollision();

		// Create collision event between o1 and o2 at position p.
		// Object o1 `caused' collision by moving into object o2.
		EventCollision(Object *p_o1, Object *p_o2, Position p);

		// Return object that caused collision.
		Object *getObject1() const;

		// Set object that caused collision.
		void setObject1(Object *p_new_o1);

		// Return object that was collided with.
		Object *getObject2() const;

		// Set object that was collided with.
		void setObject2(Object *p_new_o2);

		// Return position of the collision.
		Position getPosition() const;

		// Set position of collision.
		void setPosition(Position new_pos);
	};
}
#endif