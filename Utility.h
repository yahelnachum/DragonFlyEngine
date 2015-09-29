#ifndef __UTILITY_H__
#define __UTILITY_H__

// system includes
#include <string>

// game engine include
#include "Position.h"
#include "Box.h"
#include "Object.h"

namespace df{

	namespace Numbers { // New namespace for clarity
		enum Key {
			ZERO,
			ONE,
			TWO,
			THREE,
			FOUR
		};
	}

	class Utility {

	private:

	public:
		// Return true if two positions intersect, else false.
		static bool positionsIntersect(Position p1, Position p2);

		// Return true if two boxes intersect, else false
		static bool boxIntersectsBox(Box b1, Box b2);

		// Convert relative bounding Box for Object to absolute world Box.
		static Box getWorldBox(Object *p_o);

		// Convert relative bounding Box for Object to absolute world Box 
		// at Position where.
		static Box getWorldBox(Object *p_o, Position where);

		// Convert world position to view position.
		static Position worldToView(Position world_pos);

		// Convert view position to world position.
		static Position viewToWorld(Position view_pos);

		// Convert int to a string, returning string.
		static string intToString(int number);
	};
}
#endif