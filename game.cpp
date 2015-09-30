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

// tester includes
#include "Car.h"
#include "Bus.h"
#include "PlayerControlledCar.h"
#include "Ball.h"
#include "Reticle.h"
#include "SpecularObject.h"
#include "Saucer.h"
#include "Points.h"

// IHOP includes
#include "MapManager.h"
#include "MapObject.h"

int main(){

	// shorten cout commands
	using std::cout;

	// print out menu for tests
	int test = 0;
	cout << "Please choose one of the options:\n";
	cout << "-1 to exit\n";
	cout << "0 for IHOP Simulator\n";
	cout << "1 for Frame and Sprite tests\n";
	cout << "2 for ResourceManager tests\n";
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
		lm.writeLog("Testing frame and sprite class\n");

		// create two frames
		df::Frame f1 = df::Frame();
		df::Frame f2 = df::Frame(5, 10, "hello");

		// test frame 1
		lm.writeLog("frame f1 actual  : width: %d, height: %d, string: %s\n",
			f1.getWidth(),
			f1.getHeight(),
			f1.getString().c_str());
		lm.writeLog("frame f1 expected: width: 0, height: 0, string: \n");

		// test frame 2
		lm.writeLog("frame f2 actual  : width: %d, height: %d, string: %s\n",
			f2.getWidth(),
			f2.getHeight(),
			f2.getString().c_str());
		lm.writeLog("frame f2 expected: width: 5, height: 10, string: hello\n");

		// change frame 2
		lm.writeLog("changing frame f2 by setting new values to attributes\n");

		f2.setWidth(10);
		f2.setHeight(5);
		f2.setString("bye");

		// test frame 2 again
		lm.writeLog("frame f2 actual  : width: %d, height: %d, string: %s\n",
			f2.getWidth(),
			f2.getHeight(),
			f2.getString().c_str());
		lm.writeLog("frame f2 expected: width: 10, height: 5, string: bye\n");

		// create sprite
		df::Sprite s1 = df::Sprite(3);

		// test sprite
		lm.writeLog("sprite s1 actual   initial attributes: width: %d, height: %d, color: %d, frameCount: %d, label: %s\n",
			s1.getWidth(),
			s1.getHeight(),
			s1.getColor(),
			s1.getFrameCount(),
			s1.getLabel().c_str());
		lm.writeLog("sprite s1 expected initial attributes: width: 0, height: 0, color: 7, frameCount: 0, label: \n");

		// change sprite
		lm.writeLog("changing sprite s1 by setting new values to attributes\n");

		s1.setWidth(5);
		s1.setHeight(10);
		s1.setColor(df::BLACK);
		s1.setLabel("sprite1");

		// test sprite
		lm.writeLog("sprite s1 actual   updated attributes: width: %d, height: %d, color: %d, frameCount: %d, label: %s\n",
			s1.getWidth(),
			s1.getHeight(),
			s1.getColor(),
			s1.getFrameCount(),
			s1.getLabel().c_str());
		lm.writeLog("sprite s1 expected updated attributes: width: 5, height: 10, color: 0, frameCount: 0, label: sprite1\n");

		// add frames to sprite and test return codes
		lm.writeLog("Adding 4 frames to sprite which is one more than max count and checking return codes\n");
		for (int i = 0; i < 4; i++){
			int ret;
			if (i < 2){
				ret = s1.addFrame(f1);
			}
			else{
				ret = s1.addFrame(f2);
			}

			if (i < 3){
				lm.writeLog("adding frame to s1, return code actual  : %d\n", ret);
				lm.writeLog("adding frame to s1, return code expected: 0\n");
			}
			else{
				lm.writeLog("adding frame to s1, return code actual  : %d\n", ret);
				lm.writeLog("adding frame to s1, return code expected: -1\n");
			}
		}

		// test new sprite attributes
		lm.writeLog("sprite s1 actual   updated attributes: width: %d, height: %d, color: %d, frameCount: %d, label: %s\n",
			s1.getWidth(),
			s1.getHeight(),
			s1.getColor(),
			s1.getFrameCount(),
			s1.getLabel().c_str());
		lm.writeLog("sprite s1 expected updated attributes: width: 5, height: 10, color: 0, frameCount: 3, label: sprite1\n");

		// get frames from sprite and test the consistency
		lm.writeLog("trying to get frames from sprite\n");

		lm.writeLog("string of index outside of bounds actual  : %s\n", s1.getFrame(3).getString().c_str());
		lm.writeLog("string of index outside of bounds expected: \n");

		lm.writeLog("string of index inside of bounds actual  : %s\n", s1.getFrame(2).getString().c_str());
		lm.writeLog("string of index inside of bounds expected: bye\n");

		lm.writeLog("check frame at index 2 actual  : width: %d, height: %d, string: %s\n",
			s1.getFrame(2).getWidth(),
			s1.getFrame(2).getHeight(),
			s1.getFrame(2).getString().c_str());
		lm.writeLog("check frame at index 2 expected: width: 10, height: 5, string: bye\n");

	}

	// test ResourceMangaer
	if (test == 2){
		lm.writeLog("Testing ResourceManager class\n");

		// test resource manager type
		lm.writeLog("ResourceManager getType actual  : %s\n", rm.getType().c_str());
		lm.writeLog("ResourceManager getType expected: ResourceManager\n");

		// test loading sprite
		lm.writeLog("Loading sprite into ResourceManager\n");
		rm.loadSprite("../sprites/saucer-spr.txt", "saucer");

		// get sprite from manager
		df::Sprite *sprite1 = rm.getSprite("saucer");

		// test consistency of sprite
		lm.writeLog("getting loaded sprite from ResourceManager\n");
		lm.writeLog("Sprite loaded actual  : frames: %d, width: %d, height: %d, color: %d, label: %s\n",
			sprite1->getFrameCount(),
			sprite1->getWidth(),
			sprite1->getHeight(),
			sprite1->getColor(),
			sprite1->getLabel().c_str());
		lm.writeLog("Sprite loaded expected: frames: 5, width: 6, height: 2, color: 2, label: saucer\n");

		// check frames of sprite
		lm.writeLog("checking sprite's frames\n");

		df::Frame frame0 = sprite1->getFrame(0);
		lm.writeLog("frame0 string actual  : %s\n", frame0.getString().c_str());
		lm.writeLog("frame0 string expected:  ____ /____\\\n");

		df::Frame frame3 = sprite1->getFrame(3);
		lm.writeLog("frame3 string actual  : %s\n", frame3.getString().c_str());
		lm.writeLog("frame3 string expected:  ____ /_o__\\\n");

		// test unloading sprite
		lm.writeLog("Unloading sprite into ResourceManager\n");
		rm.unloadSprite("saucer");

		lm.writeLog("Checking if sprite is actually unloaded\n");
		lm.writeLog("does getSprite() return null? actual  : %s\n", rm.getSprite("saucer") == NULL ? "true" : "false");
		lm.writeLog("does getSprite() return null? expected: true\n");
	}

	// Test Frame Drawing
	else if (test == 3){
		lm.writeLog("Testing Frame Drawing\n");

		// print out menu for tests
		int test1 = 0;
		cout << "Please choose one of the options:\n";
		cout << "0 to exit\n";
		cout << "1 for saucer sprite\n";
		cout << "2 for mothership sprite\n";
		cout << "3 for explosion sprite\n";
		std::cin >> test1;

		// use saucer sprite
		if (test1 == 1){
			rm.loadSprite("../sprites/saucer-spr.txt", "saucer");
			for (int i = 0; i < 8; i++)new Saucer("saucer");

		}

		// use mothership sprite
		else if (test1 == 2){
			rm.loadSprite("../sprites/mothership-spr.txt", "mothership");
			for (int i = 0; i < 8; i++)new Saucer("mothership");

		}

		// use explosion sprite
		else if (test1 == 3){
			rm.loadSprite("../sprites/explosion-spr.txt", "explosion");
			for (int i = 0; i < 8; i++)new Saucer("explosion");

		}

		// run sprites across screen
		gameM.run();

	}

	// test collisions
	else if (test == 4){
		lm.writeLog("Testing box class and boxIntersects function\n");

		// create boxes
		df::Box b1 = df::Box();
		df::Box b2 = df::Box(df::Position(5, 10), 20, 30);

		// test box 1
		lm.writeLog("Default box1 attributes actual  : corner_x: %d, corner_y: %d, horizontal: %d, verticle: %d\n",
			b1.getCorner().getX(),
			b1.getCorner().getY(),
			b1.getHorizontal(),
			b1.getVertical());
		lm.writeLog("Default box1 attributes expected: corner_x: 0, corner_y: 0, horizontal: 0, verticle: 0\n");

		// test box 2
		lm.writeLog("box2 attributes actual  : corner_x: %d, corner_y: %d, horizontal: %d, verticle: %d\n",
			b2.getCorner().getX(),
			b2.getCorner().getY(),
			b2.getHorizontal(),
			b2.getVertical());
		lm.writeLog("box2 attributes expected: corner_x: 5, corner_y: 10, horizontal: 20, verticle: 30\n");

		// change box 1
		lm.writeLog("Changing box1 attributes\n");

		b1.setCorner(df::Position(1, 2));
		b1.setHorizontal(3);
		b1.setVertical(4);

		// retest box 1
		lm.writeLog("changed box1 attributes actual  : corner_x: %d, corner_y: %d, horizontal: %d, verticle: %d\n",
			b1.getCorner().getX(),
			b1.getCorner().getY(),
			b1.getHorizontal(),
			b1.getVertical());
		lm.writeLog("changed box1 attributes expected: corner_x: 1, corner_y: 2, horizontal: 3, verticle: 4\n");

		// create more boxes for intersetcts
		df::Box b3 = df::Box(df::Position(1, 1), 3, 3);
		df::Box b4 = df::Box(df::Position(2, 2), 3, 3);
		df::Box b5 = df::Box(df::Position(10, 10), 1, 1);

		// test interesects
		lm.writeLog("does box3 and box4 intersect? actual  : %s\n", df::Utility::boxIntersectsBox(b3, b4) ? "true" : "false");
		lm.writeLog("does box3 and box4 intersect? expected: true\n");

		lm.writeLog("does box4 and box5 intersect? actual  : %s\n", df::Utility::boxIntersectsBox(b4, b5) ? "true" : "false");
		lm.writeLog("does box4 and box5 intersect? expected: false\n");

	}

	// tests for new object functions and new event classes
	else if (test == 5){
		lm.writeLog("Testing new views function and audio on command\n");

		// create bigger boundary, load sprites and music
		wm.setBoundary(df::Box(df::Position(0, 0), 100, 100));
		rm.loadSprite("../sprites/saucer-spr.txt", "saucer");
		rm.loadSound("../audio/fire.wav", "fire");
		rm.loadMusic("../audio/start-music.wav", "music");

		// create objects and set view following
		PlayerControlledCar *p = new PlayerControlledCar();
		new Reticle;
		wm.setViewFollowing(p);

		for (int i = 0; i < 30; i++)
			new Ball(0, 0, df::Position(rand() % 100, rand() % 100));

		// create view objects
		new Points();

		// run game
		gameM.run();
	}

	// tests for audio
	else if (test == 6){
		lm.writeLog("Testing audio\n");
		
		// load sound in resource manager
		rm.loadSound("../audio/fire.wav", "sound");
		df::Sound *s1 = rm.getSound("sound");
		s1->play();

		// load music in resource manager
		rm.loadMusic("../audio/start-music.wav", "music");
		df::Music *m1 = rm.getMusic("music");
		m1->play();		
	}

	// if tester ran a test then prompt to exit programs
	if (test != -1){
		cout << "\nEnter any character to exit:\n";
		std::cin >> test;
	}

	// shut down all the managers and end program
	df::GameManager::getInstance().shutDown();
}