#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

// game engine includes
#include "Manager.h"

const int FRAME_TIME_DEFAULT = 33;  // In milliseconds.

namespace df {
	class GameManager : public Manager {

	private:
		GameManager();                      // Private (a singleton).
		GameManager(GameManager const&);   // No copying.
		void operator=(GameManager const&); // No assignment.
		bool game_over;       // True, then game loop should stop.
		int frame_time;       // Target time per game loop (in milliseconds).
		int game_loop;

	public:
		// Get the singleton instance of the GameManager.
		static GameManager &getInstance();

		// Startup all GameManager services.
		int startUp();

		// Shut down GameManager services.
		void shutDown();

		// Run game loop.
		void run();

		// Set game over status to indicated value.
		// If true (the default), will stop game loop.
		void setGameOver(bool game_over = true);

		// Get game over status.
		bool getGameOver() const;

		// Return frame time.
		// Frame time is target time for game loop, in milliseconds.
		int getFrameTime() const;

		// returns the game loop that the game is on
		// created to put game loop in output file
		int getGameLoop() const;
	};
}
#endif