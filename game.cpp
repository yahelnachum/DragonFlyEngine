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
#include "Floor.h"
#include "Ladder.h"

#include "Hero.h"
#include "Enemy.h"
#include "Block.h"

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
		test_map.startUp();
		test_map.loadMap1();

		gameM.run();

	}
	// test graphics manager
	else if (test == 1){
		MapManager &test_map = MapManager::getInstance();
		test_map.startUp();

		Ladder la(df::Position(10, 10), 10);
		Floor fl(df::Position(5,5), 7);
		bool onFloor = false;

		lm.writeLog("\ntest floor onmap\n");
		onFloor = fl.onMapObject(df::Position(5, 5));
		lm.writeLog("onMapObject %d, %d, %s\n", 5, 5, onFloor ? "true" : "false");
		onFloor = fl.onMapObject(df::Position(4, 5));
		lm.writeLog("onMapObject %d, %d, %s\n", 4, 5, onFloor ? "true" : "false");
		onFloor = fl.onMapObject(df::Position(12, 5));
		lm.writeLog("onMapObject %d, %d, %s\n", 12, 5, onFloor ? "true" : "false");
		onFloor = fl.onMapObject(df::Position(13, 5));
		lm.writeLog("onMapObject %d, %d, %s\n", 13, 5, onFloor ? "true" : "false");
		onFloor = fl.onMapObject(df::Position(5, 6));
		lm.writeLog("onMapObject %d, %d, %s\n", 5, 6, onFloor ? "true" : "false");
		onFloor = fl.onMapObject(df::Position(5, 4));
		lm.writeLog("onMapObject %d, %d, %s\n", 5, 4, onFloor ? "true" : "false");

		lm.writeLog("\ntest ladder onmap\n");
		onFloor = la.onMapObject(df::Position(10, 10));
		lm.writeLog("onMapObject %d, %d, %s\n", 10, 10, onFloor ? "true" : "false");
		onFloor = la.onMapObject(df::Position(10, 9));
		lm.writeLog("onMapObject %d, %d, %s\n", 10, 9, onFloor ? "true" : "false");
		onFloor = la.onMapObject(df::Position(10, 20));
		lm.writeLog("onMapObject %d, %d, %s\n", 10, 20, onFloor ? "true" : "false");
		onFloor = la.onMapObject(df::Position(10, 21));
		lm.writeLog("onMapObject %d, %d, %s\n", 10, 21, onFloor ? "true" : "false");
		onFloor = la.onMapObject(df::Position(9, 10));
		lm.writeLog("onMapObject %d, %d, %s\n", 9, 10, onFloor ? "true" : "false");
		onFloor = la.onMapObject(df::Position(11, 10));
		lm.writeLog("onMapObject %d, %d, %s\n", 11, 10, onFloor ? "true" : "false");

		lm.writeLog("\ntest all through MapManager\n");
		lm.writeLog("test mapmanager onmap\n");
		onFloor = test_map.onMap(df::Position(5, 5));
		lm.writeLog("onMapObject %d, %d, %s\n", 5, 5, onFloor ? "true" : "false");
		onFloor = test_map.onMap(df::Position(4, 5));
		lm.writeLog("onMapObject %d, %d, %s\n", 4, 5, onFloor ? "true" : "false");
		onFloor = test_map.onMap(df::Position(12, 5));
		lm.writeLog("onMapObject %d, %d, %s\n", 12, 5, onFloor ? "true" : "false");
		onFloor = test_map.onMap(df::Position(13, 5));
		lm.writeLog("onMapObject %d, %d, %s\n", 13, 5, onFloor ? "true" : "false");
		onFloor = test_map.onMap(df::Position(5, 6));
		lm.writeLog("onMapObject %d, %d, %s\n", 5, 6, onFloor ? "true" : "false");
		onFloor = test_map.onMap(df::Position(5, 4));
		lm.writeLog("onMapObject %d, %d, %s\n", 5, 4, onFloor ? "true" : "false");
		onFloor = test_map.onMap(df::Position(10, 10));
		lm.writeLog("onMapObject %d, %d, %s\n", 10, 10, onFloor ? "true" : "false");
		onFloor = test_map.onMap(df::Position(10, 9));
		lm.writeLog("onMapObject %d, %d, %s\n", 10, 9, onFloor ? "true" : "false");
		onFloor = test_map.onMap(df::Position(10, 20));
		lm.writeLog("onMapObject %d, %d, %s\n", 10, 20, onFloor ? "true" : "false");
		onFloor = test_map.onMap(df::Position(10, 21));
		lm.writeLog("onMapObject %d, %d, %s\n", 10, 21, onFloor ? "true" : "false");
		onFloor = test_map.onMap(df::Position(9, 10));
		lm.writeLog("onMapObject %d, %d, %s\n", 9, 10, onFloor ? "true" : "false");
		onFloor = test_map.onMap(df::Position(11, 10));
		lm.writeLog("onMapObject %d, %d, %s\n", 11, 10, onFloor ? "true" : "false");


		gameM.run();
	}

	// test ResourceMangaer
	if (test == 2){
		rm.loadSprite("../sprites/hero-spr.txt", "hero");


		new Enemy();
		new Hero();
		new Block();

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