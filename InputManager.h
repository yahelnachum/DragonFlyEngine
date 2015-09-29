#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

// game engine includes
#include "Manager.h"

namespace df{
	class InputManager : public df::Manager {

	private:
		InputManager();                      // Private (a singleton).
		InputManager(InputManager const&);   // No copying.
		void operator=(InputManager const&); // No assignment.

	public:
		// Get the one and only instance of the InputManager.
		static InputManager &getInstance();

		// Get terminal ready to capture input.
		// Return 0 if ok, else return -1.
		int startUp();

		// Revert back to normal terminal mode.
		void shutDown();

		// Get input from the keyboard and mouse.
		// Pass event along to all Objects.
		void getInput();
	};
}
#endif