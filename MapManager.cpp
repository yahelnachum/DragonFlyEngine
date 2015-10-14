// game engine includes
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

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
	df::WorldManager &wm = df::WorldManager::getInstance();
	for (int i = 0; i < mo_count; i++) {
		wm.markForDelete(p_map_o[i]);
	}
	mo_count = 0;
	return 0;
}

// load the next level
int MapManager::loadNextLevel() {
	df::ResourceManager::getInstance().getSound("applause")->play();

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
	currentLevel = 1;
	stackNeeded = 7;

	new Ladder(df::Position(5, 5), 10);
	new Ladder(df::Position(25, 5), 10);
	new Ladder(df::Position(40, 5), 10);
	new Floor(df::Position(35, 5), 25);
	new Floor(df::Position(0, 5), 35);
	new Floor(df::Position(0, 15), 10);
	new Floor(df::Position(20, 15), 27);

	Enemy *enem = new Enemy(df::Position(3, 5));
	Hero *hero = new Hero(df::Position(45, 14));
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

// load level 2 of the map
int MapManager::loadMap2(){
	currentLevel = 2;
	stackNeeded = 15;

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
			if (j > 10){
				new Shelf(df::Position(i, 23), true);
			}
		}
	}


	Enemy *enem = new Enemy(df::Position(3, 5));
	Enemy *enem1 = new Enemy(df::Position(75, 5));
	Hero *hero = new Hero(df::Position(51, 15));
	df::Position pos = hero->getPosition();
	pos.setX(pos.getX() - 5);
	new Power(SHIELD, df::Position(3, 2));

	Button *butt = new Button();
	butt->addWall(new Wall(df::Position(35, 0), 25));
	butt->setPosition(df::Position(42, 3));

	return 0;
	return 0;
}

int MapManager::loadMap3(){
	currentLevel = 3;
	stackNeeded = 11;

	new Floor(df::Position(3, 5), 40);
	new Floor(df::Position(50, 5), 20);
	new Floor(df::Position(5, 10), 15);
	new Floor(df::Position(30, 10), 40);
	new Floor(df::Position(20, 14), 45);
	new Floor(df::Position(38, 18), 17);

	new Ladder(df::Position(19, 11), 4);
	new Ladder(df::Position(5, 6), 5);
	new Ladder(df::Position(69, 6), 5);
	new Ladder(df::Position(38, 6), 13);
	new Ladder(df::Position(50, 6), 5);
	new Ladder(df::Position(55, 15), 4);
	new Ladder(df::Position(60, 11), 4);

	int col1 = 9;

	new Block(df::Position(col1, 5));
	new Shelf(df::Position(col1, 5));
	new Block(df::Position(col1, 10));
	new Shelf(df::Position(col1, 10));

	new Shelf(df::Position(col1, 23), true);

	int col2 = 30;

	new Block(df::Position(col2, 5));
	new Shelf(df::Position(col2, 5));
	new Block(df::Position(col2, 10));
	new Shelf(df::Position(col2, 10));
	new Block(df::Position(col2, 14));
	new Shelf(df::Position(col2, 14));

	new Shelf(df::Position(col2, 23), true);

	int col3 = 43;

	new Block(df::Position(col3, 5));
	new Shelf(df::Position(col3, 5));
	new Block(df::Position(col3, 10));
	new Shelf(df::Position(col3, 10));
	new Block(df::Position(col3, 14));
	new Shelf(df::Position(col3, 14));
	new Block(df::Position(col3, 18));
	new Shelf(df::Position(col3, 18));

	new Shelf(df::Position(col3, 23), true);

	int col4 = 65;

	new Block(df::Position(col4, 5));
	new Shelf(df::Position(col4, 5));
	new Block(df::Position(col4, 10));
	new Shelf(df::Position(col4, 10));
	new Block(df::Position(col4, 14));
	new Shelf(df::Position(col4, 14));

	new Shelf(df::Position(col4, 23), true);

	Button *butt = new Button();
	butt->addWall(new Wall(df::Position(35, 0), 25));
	butt->setPosition(df::Position(53, 5));

	Enemy *enem = new Enemy(df::Position(3, 5));
	Enemy *enem1 = new Enemy(df::Position(55, 9));
	Hero *hero = new Hero(df::Position(51, 17));

	new Power(SHIELD, df::Position(20, 4));

	return 0;
}

// get array of map objects
MapObject **MapManager::getMapObjects(){
	return p_map_o;
}