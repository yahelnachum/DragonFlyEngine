// system includes
#include <windows.h>

// game engine includes
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

#include "ObjectList.h"
#include "ObjectListIterator.h"

#include "Clock.h"
#include "EventStep.h"

// constructor, set type, gameover, and gameloop number
df::GameManager::GameManager(){
	setType("GameManager");
	game_over = false;
	game_loop = 0;
}

// overloaded constructor
df::GameManager::GameManager(GameManager const&){
	setType("GameManager");
	game_over = false;
	game_loop = 0;
}

// Get the singleton instance of the GameManager.
df::GameManager &df::GameManager::getInstance(){
	static GameManager game_manager;
	return game_manager;
}

// Startup all GameManager services.
int df::GameManager::startUp(){
	
	// startup managers
	df::LogManager::getInstance().startUp();
	df::WorldManager::getInstance().startUp();
	df::GraphicsManager::getInstance().startUp();
	df::InputManager::getInstance().startUp();
	df::ResourceManager::getInstance().startUp();
	df::Manager::startUp();

	// set up world boundary and view
	df::WorldManager::getInstance().setBoundary(df::Box(df::Position(0, 0),
		df::GraphicsManager::getInstance().getHorizontal(),
		df::GraphicsManager::getInstance().getVertical()));
	df::WorldManager::getInstance().setView(df::Box(df::Position(0, 0),
		df::GraphicsManager::getInstance().getHorizontal(),
		df::GraphicsManager::getInstance().getVertical()));

	// write to log
	df::LogManager::getInstance().writeLog("GameManager::startUp Managers have been started\n");

	return 0;
}

// Shut down GameManager services.
void df::GameManager::shutDown(){

	// write to log
	df::LogManager::getInstance().writeLog("GameManager::shutDown Managers are being shutdown\n");
	
	df::InputManager::getInstance().shutDown();
	df::GraphicsManager::getInstance().shutDown();
	df::WorldManager::getInstance().shutDown();
	df::LogManager::getInstance().shutDown();
	df::Manager::shutDown();
}

// Run game loop.
void df::GameManager::run(){
	df::LogManager::getInstance().writeLog("GameManager::run GameManager is running the game\n");

	// get clock
	game_loop = 0;
	df::WorldManager &wm = df::WorldManager::getInstance();
	df::GraphicsManager &gm = df::GraphicsManager::getInstance();
	Clock cl;
	int i = 0;

	// run game loops
	while (!getGameOver()){

		// send step event to all objects
		EventStep es = EventStep(i);
		df::Manager::onEvent(&es);
		
		// get input
		df::InputManager::getInstance().getInput();

		// update world
		wm.update();

		// draw world to screen
		wm.draw();

		// swap buffers and show player new screen
		gm.swapBuffers();

		// add one to loop
		i++;

		// get split and sleep extra time if finished in less than default frame time
		int delta = cl.split();
		if (delta > 0 && delta < FRAME_TIME_DEFAULT)
			Sleep(FRAME_TIME_DEFAULT - delta);
		frame_time = cl.delta();

		// write to lock how long game loop took
		df::LogManager::getInstance().writeLog("GameManager::run Frame took %d milliseconds\n", frame_time);
		game_loop++;
	}
}

// Set game over status to indicated value.
// If true (the default), will stop game loop.
void df::GameManager::setGameOver(bool game_over){
	this->game_over = game_over;
}

// Get game over status.
bool df::GameManager::getGameOver() const{
	return game_over;
}

// Return frame time.
// Frame time is target time for game loop, in milliseconds.
int df::GameManager::getFrameTime() const{
	return frame_time;
}

// returns the game loop that the game is on
int df::GameManager::getGameLoop() const{
	return game_loop;
}
