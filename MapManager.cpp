// game engine includes
#include "LogManager.h"

// IHOP includes
#include "MapManager.h"
#include "Floor.h"
#include "Ladder.h"
#include "Wall.h"
#include "Button.h"
#include "Enemy.h"
#include "Hero.h"
#include "Power.h"
#include "Block.h"
#include "Shelf.h"
#include "Points.h"
#include "Lives.h"

// constructor
MapManager::MapManager(){
	
}

// destructor
MapManager::~MapManager(){
}

// startup manager
int MapManager::startUp(){
	Manager::startUp();
	setType("Map Manager");
	stackCounter = 0;
	return 0;
}

// shutdown manager
void MapManager::shutDown(){
	Manager::shutDown();
}

// get instance of manager
MapManager &MapManager::getInstance(){
	static MapManager map;
	return map;
}


// return true if the position falls anywhere on the map
bool MapManager::onMap(df::Position pos) const {
	df::LogManager &lm = df::LogManager::getInstance();

	for (int i = 0; i < mo_count; i++) {
		MapObject *currentMO = p_map_o[i];
		if (currentMO->getType() == "Wall") {
			if (currentMO->onMapObject(pos)) {
				return false;
			}
		}
	}

	for (int i = 0; i < mo_count; i++) {
		MapObject *currentMO = p_map_o[i];
		if (currentMO->onMapObject(pos)) {
			return true;
		}
	}

	return false;
}

// get number of stacks needed to complete a level
int MapManager::getStackCounter() const {
	return stackCounter;
}

// add one to stack counter
void MapManager::addStackToCounter() {
	df::LogManager &lm = df::LogManager::getInstance();
	lm.writeLog("IM GETTIN CALLED\n\n\n");
	if (stackCounter == stackNeeded){
		loadNextLevel();
	}
	else {
		stackCounter++;
	}
}

// set the number stacks that need to be complete to finish a level
void MapManager::setNeededStack(int new_stack_needed) {
	stackNeeded = new_stack_needed;
}

// add a MapObject to the MapObject list
int MapManager::addMapObject(MapObject *m_o){
	if (mo_count < MAX_MAP_OBJECTS) {
		p_map_o[mo_count] = m_o;
		mo_count++;
		return 0;
	}
	return -1;
}

// remove a MapObject from the MapObject list
int MapManager::removeMapObject(MapObject *m_o){
	for (int i = 0; i < mo_count; i++) {
		if (p_map_o[i] == m_o) {
			for (int j = i; j < mo_count - 1; j++) {
				p_map_o[j] = p_map_o[j + 1];
				return 0;
			}
		}
	}
	return -1;
}

// remove a MapObject from the MapObject list
int MapManager::removeAllMapObject(){
	for (int i = 0; i < mo_count; i++) {
		p_map_o[i]->~MapObject();
	}
	mo_count = 0;
	return 0;
}

// load the next level
int MapManager::loadNextLevel() {
	df::LogManager &lm = df::LogManager::getInstance();

	stackCounter = 0;
	if (currentLevel == 1) {
		removeAllMapObject();
		loadMap2();
		return 0;
	}
	else if (currentLevel == 2) {
		removeAllMapObject();
		loadMap3();
		return 0;
	}
	else if (currentLevel == 3) {
		removeAllMapObject();
		loadMap1();
		return 0;
	}
	return -1;
}

// load level 1 of the map
int MapManager::loadMap1(){
	stackNeeded = 1;
	currentLevel = 1;

	new Ladder(df::Position(5, 5), 10);
	new Ladder(df::Position(25, 5), 10);
	new Ladder(df::Position(40, 5), 10);
	new Floor(df::Position(35, 5), 25);
	new Floor(df::Position(0, 5), 30);
	new Floor(df::Position(0, 15), 10);
	new Floor(df::Position(20, 15), 27);

	return 0;
}

// load level 2 of the map
int MapManager::loadMap2(){
	stackNeeded = 7;
	currentLevel = 2;

	new Ladder(df::Position(5, 5), 10);
	new Ladder(df::Position(25, 5), 10);
	new Ladder(df::Position(40, 5), 10);
	new Floor(df::Position(35, 5), 25);
	new Floor(df::Position(0, 5), 35);
	new Floor(df::Position(0, 15), 10);
	new Floor(df::Position(20, 15), 27);

	Enemy *enem = new Enemy(df::Position(3, 5));
	Hero *hero = new Hero(df::Position(45,15));
	df::Position pos = hero->getPosition();
	pos.setX(pos.getX() - 5);
	new Power(SHIELD, pos);

	Button *butt = new Button();
	butt->addWall(new Wall(df::Position(30, 0), 25));
	butt->setPosition(df::Position(45, 5));

	new Block(df::Position(40, 5));
	new Block(df::Position(40, 7));
	new Block(df::Position(40, 9));
	new Block(df::Position(40, 11));
	new Shelf(df::Position(40, 15));
	new Shelf(df::Position(40, 23), true);

	new Block(df::Position(25, 5));
	new Block(df::Position(25, 7));
	new Block(df::Position(25, 9));
	new Block(df::Position(25, 11));
	new Shelf(df::Position(25, 15));
	new Shelf(df::Position(25, 23), true);

	return 0;
}

int MapManager::loadMap3(){
	stackNeeded = 15;
	currentLevel = 3;

	new Floor(df::Position(3, 3), 72);
	new Floor(df::Position(3, 10), 72);
	new Floor(df::Position(3, 17), 72);
	new Ladder(df::Position(3, 4), 13);
	new Ladder(df::Position(27, 4), 13);
	new Ladder(df::Position(51, 4), 13);
	new Ladder(df::Position(75, 4), 13);

	for (int i = 3; i < 76; i += 24){
		for (int j = 3; j < 14; j += 3){
			new Block(df::Position(i, j));
			new Shelf(df::Position(i, j));
			if(j > 10){
				new Shelf(df::Position(i, 23), true);
			}
		}
	}

	
	Enemy *enem = new Enemy(df::Position(3, 5));
	Enemy *enem1 = new Enemy(df::Position(75, 5));
	Hero *hero = new Hero(df::Position(51, 15));
	df::Position pos = hero->getPosition();
	pos.setX(pos.getX() - 5);
	new Power(SHIELD, df::Position(3,2));

	Button *butt = new Button();
	butt->addWall(new Wall(df::Position(35, 0), 25));
	butt->setPosition(df::Position(42, 3));

	return 0;
}

// get array of map objects
MapObject **MapManager::getMapObjects(){
	return p_map_o;
}