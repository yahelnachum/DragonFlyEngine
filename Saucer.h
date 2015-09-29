// game engine includes
#include "Object.h"
#include "EventCollision.h"

class Saucer : public df::Object {
	private:
		// count for movetoStart
		int count = 0;
		// what sprite to use
		std::string spriteName;
		/* moves the saucer to the right boundary*/
		void moveToStart();

		/* finds out if the saucer is out of bounds*/
		void out();

		/* decides what to do if saucer is hit */
		void hit(const df::EventCollision *p_c);
	public:
		/* creates a saucer object */
		Saucer(std::string spriteName);

		/* destroys the saucer and adds points to score */
		~Saucer();

		/* decides what to do on saucers registered events*/
		int eventHandler(df::Event *p_e);
};