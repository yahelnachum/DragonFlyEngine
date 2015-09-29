#ifndef __MANAGER_H__
#define __MANAGER_H__

// system includes
#include <string>

// game engine includes
#include "Event.h"

namespace df {

	class Manager {

	private:
		std::string type; // Manager type  identifier .
		bool is_started;  // True when started successfully.

	protected:
		// Set type identifier of Manager.
		void setType(std::string type);

	public:
		// constructor
		Manager();

		// destructor
		virtual ~Manager();

		// Get type identifier of Manager.
		std::string getType() const;

		// Startup Manager.
		// Return 0 if ok, else negative number.
		virtual int startUp();

		// Shutdown Manager.
		virtual void shutDown();

		// Return true when startUp() was executed ok, else false.
		bool isStarted() const;

		// Send event to all Objects.
		// Return count of number of events sent.
		int onEvent(const Event *p_event);
	};

} // end of namespace df
#endif // __MANAGER_H__
