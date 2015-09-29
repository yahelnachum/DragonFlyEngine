// game engine includes
#include "Manager.h"
#include "LogManager.h"
#include "GraphicsManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"
#include "EventView.h"

#include "Utility.h"

// tester includes
#include "PlayerControlledCar.h"
#include "Bullet.h"
#include "Ball.h"

// default constructor
PlayerControlledCar::PlayerControlledCar(){
	setType("PlayerControlledCar");
	setXVelocity(0);
	setSolidness(df::HARD);

	// put in middle of window
	setPosition(df::Position(df::WINDOW_HORIZONTAL_CHARS_DEFAULT / 2, df::WINDOW_VERTICAL_CHARS_DEFAULT / 2));
}

// Handle event (default is to ignore everything).
// Return 0 if ignored, else 1 if handled.
int PlayerControlledCar::eventHandler(df::Event *p_e){

	// if keyboard event then check key
	if (p_e->getType() == df::DF_KEYBOARD_EVENT && ((df::EventKeyboard *)p_e)->getKeyboardAction() == df::KEY_PRESSED){
		df::EventKeyboard *eka = (df::EventKeyboard *)p_e;
		
		// decide which way to move if it is wasd keys
		switch (eka->getKey()){
		case df::Input::Key::W:
			this->setYVelocity(-0.5);
			break;
		case df::Input::Key::S:
			this->setYVelocity(0.5);
			break;
		case df::Input::Key::A:
			this->setXVelocity(-1.0);
			break;
		case df::Input::Key::D:
			this->setXVelocity(1.0);
			break;
		// set game over if escape is pressed
		case df::Input::Key::ESCAPE:
			df::GameManager::getInstance().setGameOver();
			break;
		}

		// make world follow this object
		//df::WorldManager::getInstance().setViewPosition(this->getPosition());

		return 1;
	}
	if (p_e->getType() == df::DF_KEYBOARD_EVENT && ((df::EventKeyboard *)p_e)->getKeyboardAction() == df::KEY_RELEASED){
		this->setXVelocity(0.0);
		this->setYVelocity(0.0);
		return 1;
	}
	// if its a left mouse press then add a bullet
	else if (p_e->getType() == df::DF_MOUSE_EVENT && ((df::EventMouse *)p_e)->getMouseAction() == df::PRESSED && ((df::EventMouse *)p_e)->getMouseButton() == df::LEFT){
		
		// calculate velocity based on position and distance of mouse
		df::Position pos = ((df::EventMouse *)p_e)->getMousePosition();
		pos = df::GraphicsManager::getInstance().pixelsToSpaces(pos);
		pos = df::Utility::viewToWorld(pos);
		float xVel = (float)(pos.getX() - getPosition().getX());
		float yVel = (float)(pos.getY() - getPosition().getY());
		xVel /= 10;
		yVel /= 10;

		// create bullet with initial values
		new Bullet(xVel, yVel, getPosition());

		df::ResourceManager::getInstance().getSound("fire")->play();

		return 1;
	}

	// if its a right mouse release then add a ball
	else if (p_e->getType() == df::DF_MOUSE_EVENT && ((df::EventMouse *)p_e)->getMouseAction() == df::CLICKED && ((df::EventMouse *)p_e)->getMouseButton() == df::RIGHT){
		
		// calculate velocity based on position and distance of mouse
		df::Position pos = ((df::EventMouse *)p_e)->getMousePosition();
		pos = df::GraphicsManager::getInstance().pixelsToSpaces(pos);
		pos = df::Utility::viewToWorld(pos);
		float xVel = (float)(pos.getX() - getPosition().getX());
		float yVel = (float)(pos.getY() - getPosition().getY());
		xVel /= 10;
		yVel /= 10;

		// create ball with initial values
		new Ball(xVel, yVel, getPosition());

		df::ResourceManager::getInstance().getMusic("music")->play();

		return 1;
	}

	if (p_e->getType() == DF_COLLISION_EVENT){
		df::EventCollision *ec = (df::EventCollision *) p_e;

		if (ec->getObject1()->getType() == "Ball" || ec->getObject2()->getType() == "Ball"){
			df::EventView ev = df::EventView("points", 0, 10);
			df::WorldManager::getInstance().onEvent(&ev);
		}
	}
	return 0;
}