#ifndef __OBJECT_H__
#define __OBJECT_H__

// system includes
#include <string>

// engine includes
#include "Position.h"
#include "Event.h"
#include "Sprite.h"
#include "Box.h"

using std::string; // shorten writing strings

namespace df{

	enum Solidness {
		HARD,     // Objects cause collisions and impede.
		SOFT,     // Objects cause collisions, but don't impede.
		SPECTRAL  // Objects don't cause collisions.
	};

	class Object {

	private:
		int id;						// Unique Object identifier.
		string type;				// User-defined identification.
		df::Position pos;			// Position in game world.
		int altitude;				// 0 to MAX supported (lower drawn first).
		Solidness solidness;		// Solidness of object.

		float x_velocity;           // Horizontal speed in spaces per step.
		float x_velocity_countdown; // Countdown to horizontal movement.
		float y_velocity;           // Vertical speed in spaces per step.
		float y_velocity_countdown; // Countdown to vertical movement.

		df::Sprite *p_sprite;       // Sprite associated with object.
		bool sprite_center;         // True if sprite centered on object.
		int sprite_index;           // Current index frame for sprite.
		int sprite_slowdown;        // Slowdown rate (1 = no slowdown, 0 = stop).
		int sprite_slowdown_count;  // Slowdown counter.

		Box box;					// collision box to use for calculations

	public:
		// constructor
		Object();

		// destructor
		virtual ~Object();

		// Set object id.
		void setId(int new_id);

		// Get object id.
		int getId() const;

		// Set type identifier of object.
		void setType(string new_type);

		// Get type identifier of object.
		string getType() const;

		// Set Position of object.
		void setPosition(df::Position new_pos);

		// Get Position of object.
		df::Position getPosition() const;

		// Handle event (default is to ignore everything).
		// Return 0 if ignored, else 1 if handled.
		virtual int eventHandler(Event *p_e);

		// Set object altitude.
		// Checks for in range [0, MAX_ALTITUDE].
		// Return 0 if ok, else -1.
		int setAltitude(int new_altitude);

		// Return object altitude.
		int getAltitude() const;

		// Get and set velocity (x,y).
		void setXVelocity(float new_x_velocity);
		float getXVelocity() const;
		void setYVelocity(float new_y_velocity);
		float getYVelocity() const;

		// Perform 1 step of velocity in horizontal direction.
		// Return horizontal distance moved this step.
		int getXVelocityStep();

		// Perform 1 step of velocity in vertical direction.
		// Return vertical distance moved this step.
		int getYVelocityStep();

		bool isSolid(); // True if HARD or SOFT, else false.

		// Set object solidness, with checks for consistency.
		// Return 0 if ok, else -1.
		int setSolidness(Solidness new_solid);

		// Return object solidness.
		Solidness getSolidness() const;

		// Set object Sprite to new one.
		// If set_box is true, set bounding box to size of Sprite.
		void setSprite(Sprite *p_new_sprite, bool set_box = true);

		// Return pointer to Sprite associated with this object.
		Sprite *getSprite() const;

		// Set Sprite to be centered at object Position (pos).
		void setCentered(bool centered = true);

		// Indicates if sprite is centered at object Position (pos).
		bool isCentered() const;

		// Set index of current Sprite frame to be displayed.
		void setSpriteIndex(int new_sprite_index);

		// Return index of current Sprite frame to be displayed.
		int getSpriteIndex() const;

		// Slows down sprite animations.
		// Sprite slowdown is in multiples of GameManager frame time.
		void setSpriteSlowdown(int new_sprite_slowdown);
		int getSpriteSlowdown() const;
		void setSpriteSlowdownCount(int new_sprite_slowdown_count);
		int getSpriteSlowdownCount() const;

		// Draw single sprite frame.
		// Drawing accounts for: centering, slowdown, advancing Sprite Frame.
		virtual void draw();

		// Set object's bounding box.
		void setBox(Box new_box);

		// Get object's bounding box.
		Box getBox() const;

	};
}
#endif