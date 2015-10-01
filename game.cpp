// system includes
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

// game engine includes
#include "GameManager.h"
#include "WorldManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

#include "EventCollision.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventOut.h"

#include "Position.h"

#include "Frame.h"
#include "Sprite.h"
#include "Box.h"

#include "Utility.h"

// IHOP includes
#include "MapManager.h"
#include "MapObject.h"

#include "Hero.h"
#include "Enemy.h"

int main(){

	// shorten cout commands
	using std::cout;

	// print out menu for tests
	int test = 0;
	cout << "Please choose one of the options:\n";
	cout << "-1 to exit\n";
	cout << "0 for IHOP Simulator\n";
	cout << "1 for test\n";
	cout << "2 for Hero tests\n";
	cout << "3 for Frame Drawing tests\n";
	cout << "4 for Box class and boxIntersects function tests\n";
	cout << "5 for Views and Audio tests\n";
	cout << "6 for Audio tests\n";
	cout << "\n";
	std::cin >> test;

	// start up managers
	df::GameManager::getInstance().startUp();

	// get instances of managers
	df::GameManager &gameM = df::GameManager::getInstance();
	df::WorldManager &wm = df::WorldManager::getInstance();
	df::GraphicsManager &graphicsM = df::GraphicsManager::getInstance();
	df::InputManager &im = df::InputManager::getInstance();
	df::LogManager &lm = df::LogManager::getInstance();
	df::ResourceManager &rm = df::ResourceManager::getInstance();

	lm.setFlush();
	// Test IHOP Simulator 2015
	if (test == 0) {
		lm.writeLog("Testing maps and map Objects\n");
		MapManager &test_map = MapManager::getInstance();
		MapObject *test_mo1 = new MapObject();
		MapObject *test_mo2 = new MapObject();
		MapObject *test_mo3 = new MapObject();
		df::Position testPos = df::Position();
		lm.writeLog("onMap: %s, onMapObject: %s\n", test_map.onMap(testPos) ? "true" : "false", test_mo1->onMapObject(testPos) ? "true" : "false");

		test_map.shutDown();

	}
	// test graphics manager
	else if (test == 1){
		MapObject *test_mo = new MapObject();

	}

	// test ResourceMangaer
	if (test == 2){
		rm.loadSprite("../sprites/hero-spr.txt", "hero");

		new Hero();
		new Enemy();

		gameM.run();
	}

	// Test Frame Drawing
	else if (test == 3){
		
	}

	// test collisions
	else if (test == 4){
		

	}

	// tests for new object functions and new event classes
	else if (test == 5){
		
	}

	// tests for audio
	else if (test == 6){
		
	}

	// if tester ran a test then prompt to exit programs
	if (test != -1){
		cout << "\nEnter any character to exit:\n";
		std::cin >> test;
	}

	// shut down all the managers and end program
	df::GameManager::getInstance().shutDown();
}