// game engine includes
#include "InputManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"

#include "EventKeyboard.h"
#include "EventMouse.h"

// constructor, set type, gameover, and gameloop number
df::InputManager::InputManager(){
	setType("InputManager");
}

// overloaded constructor
df::InputManager::InputManager(InputManager const&){
	setType("InputManager");
}

// Get the one and only instance of the InputManager.
df::InputManager &df::InputManager::getInstance(){
	static InputManager input_manager;
	return input_manager;
}

// Get terminal ready to capture input.
// Return 0 if ok, else return -1.
int df::InputManager::startUp(){

	// needs graphics manager to be already started up
	if (!df::GraphicsManager::getInstance().isStarted())
		return -1;

	sf::RenderWindow *rw = df::GraphicsManager::getInstance().getWindow();
	
	rw->setKeyRepeatEnabled(true);

	Manager::startUp();

	df::LogManager::getInstance().writeLog("InputManager:startUp Started up InputManager\n");
}

// Revert back to normal terminal mode.
void df::InputManager::shutDown(){

	sf::RenderWindow *rw = df::GraphicsManager::getInstance().getWindow();
	rw->setKeyRepeatEnabled(false);

	Manager::shutDown();

	df::LogManager::getInstance().writeLog("InputManager:shutDown InputManager has been shut down\n");
}

// Get input from the keyboard and mouse.
// Pass event along to all Objects.
void df::InputManager::getInput(){
	// Check past window events.
	sf::RenderWindow *rw = df::GraphicsManager::getInstance().getWindow();
	
	
	sf::Event event;
	while (rw->pollEvent(event)){
		
		bool unrecongnizedEvent = false;

		// boolean and event if it is a keyboard event
		bool isKeyboardEvent = false;
		df::EventKeyboard *eventKeyboard = new df::EventKeyboard();
		df::EventKeyboard *eventKeyboardPressed = new df::EventKeyboard();

		// boolean and event if it is a mouse event
		bool isMouseButtonEvent = false;
		df::EventMouse *eventMouse = new df::EventMouse();

		// find out what general action it is
		switch (event.type){
		case sf::Event::KeyPressed:
			isKeyboardEvent = true;
			eventKeyboard->setKeyboardAction(EventKeyboardAction::KEY_PRESSED);
			break;
		case sf::Event::KeyReleased:
			isKeyboardEvent = true;
			eventKeyboard->setKeyboardAction(EventKeyboardAction::KEY_RELEASED);
			break;
		case sf::Event::MouseMoved:
			eventMouse->setMouseAction(EventMouseAction::MOVED);
			eventMouse->setMousePosition(df::Position(event.mouseMove.x, event.mouseMove.y));
			Manager::onEvent(eventMouse);
			break;
		case sf::Event::MouseButtonPressed:
			isMouseButtonEvent = true;
			eventMouse->setMouseAction(EventMouseAction::PRESSED);
			eventMouse->setMousePosition(df::Position(event.mouseButton.x, event.mouseButton.y));
			break;
		case sf::Event::MouseButtonReleased:
			isMouseButtonEvent = true;
			eventMouse->setMouseAction(EventMouseAction::CLICKED);
			eventMouse->setMousePosition(df::Position(event.mouseButton.x, event.mouseButton.y));
			break;
		}

		// if it is a mouse button event then find out what button it is and send it to all objects
		if (isMouseButtonEvent){
			switch (event.mouseButton.button){
			case sf::Mouse::Left:
				eventMouse->setMouseButton(EventMouseButton::LEFT);
				break;
			case sf::Mouse::Right:
				eventMouse->setMouseButton(EventMouseButton::RIGHT);
				break;
			case sf::Mouse::Middle:
				eventMouse->setMouseButton(EventMouseButton::MIDDLE);
				break;

				// unkown button
			default:
				unrecongnizedEvent = true;
				break;
			}

			if (!unrecongnizedEvent)
				Manager::onEvent(eventMouse);
		}

		// if it is a keyboard event then find out what button it is and send it to all objects
		if (isKeyboardEvent){
			switch (event.key.code){

				// special keys
			case sf::Keyboard::Space:
				eventKeyboard->setKey(Input::SPACE);
				break;
			case sf::Keyboard::Return:
				eventKeyboard->setKey(Input::RETURN);
				break;
			case sf::Keyboard::Escape:
				eventKeyboard->setKey(Input::ESCAPE);
				break;
			case sf::Keyboard::Tab:
				eventKeyboard->setKey(Input::TAB);
				break;
			case sf::Keyboard::Left:
				eventKeyboard->setKey(Input::LEFTARROW);
				break;
			case sf::Keyboard::Right:
				eventKeyboard->setKey(Input::RIGHTARROW);
				break;
			case sf::Keyboard::Up:
				eventKeyboard->setKey(Input::UPARROW);
				break;
			case sf::Keyboard::Down:
				eventKeyboard->setKey(Input::DOWNARROW);
				break;
			case sf::Keyboard::Pause:
				eventKeyboard->setKey(Input::PAUSE);
				break;
			case sf::Keyboard::Subtract:
				eventKeyboard->setKey(Input::MINUS);
				break;
			case sf::Keyboard::Add:
				eventKeyboard->setKey(Input::PLUS);
				break;
			case sf::Keyboard::Tilde:
				eventKeyboard->setKey(Input::TILDE);
				break;
			case sf::Keyboard::Period:
				eventKeyboard->setKey(Input::PERIOD);
				break;
			case sf::Keyboard::Comma:
				eventKeyboard->setKey(Input::COMMA);
				break;
			case sf::Keyboard::Slash:
				eventKeyboard->setKey(Input::SLASH);
				break;
			case sf::Keyboard::LControl:
				eventKeyboard->setKey(Input::LEFTCONTROL);
				break;
			case sf::Keyboard::RControl:
				eventKeyboard->setKey(Input::RIGHTCONTROL);
				break;
			case sf::Keyboard::LShift:
				eventKeyboard->setKey(Input::LEFTSHIFT);
				break;
			case sf::Keyboard::RShift:
				eventKeyboard->setKey(Input::RIGHTSHIFT);
				break;

				// letters
			case sf::Keyboard::A:
				eventKeyboard->setKey(Input::A);
				break;
			case sf::Keyboard::B:
				eventKeyboard->setKey(Input::B);
				break;
			case sf::Keyboard::C:
				eventKeyboard->setKey(Input::C);
				break;
			case sf::Keyboard::D:
				eventKeyboard->setKey(Input::D);
				break;
			case sf::Keyboard::E:
				eventKeyboard->setKey(Input::E);
				break;
			case sf::Keyboard::F:
				eventKeyboard->setKey(Input::F);
				break;
			case sf::Keyboard::G:
				eventKeyboard->setKey(Input::G);
				break;
			case sf::Keyboard::H:
				eventKeyboard->setKey(Input::H);
				break;
			case sf::Keyboard::I:
				eventKeyboard->setKey(Input::I);
				break;
			case sf::Keyboard::J:
				eventKeyboard->setKey(Input::J);
				break;
			case sf::Keyboard::K:
				eventKeyboard->setKey(Input::K);
				break;
			case sf::Keyboard::L:
				eventKeyboard->setKey(Input::L);
				break;
			case sf::Keyboard::M:
				eventKeyboard->setKey(Input::M);
				break;
			case sf::Keyboard::N:
				eventKeyboard->setKey(Input::N);
				break;
			case sf::Keyboard::O:
				eventKeyboard->setKey(Input::O);
				break;
			case sf::Keyboard::P:
				eventKeyboard->setKey(Input::P);
				break;
			case sf::Keyboard::Q:
				eventKeyboard->setKey(Input::Q);
				break;
			case sf::Keyboard::R:
				eventKeyboard->setKey(Input::R);
				break;
			case sf::Keyboard::S:
				eventKeyboard->setKey(Input::S);
				break;
			case sf::Keyboard::T:
				eventKeyboard->setKey(Input::T);
				break;
			case sf::Keyboard::U:
				eventKeyboard->setKey(Input::U);
				break;
			case sf::Keyboard::V:
				eventKeyboard->setKey(Input::V);
				break;
			case sf::Keyboard::W:
				eventKeyboard->setKey(Input::W);
				break;
			case sf::Keyboard::X:
				eventKeyboard->setKey(Input::X);
				break;
			case sf::Keyboard::Y:
				eventKeyboard->setKey(Input::Y);
				break;
			case sf::Keyboard::Z:
				eventKeyboard->setKey(Input::Z);
				break;

				// numbers
			case sf::Keyboard::Num1:
				eventKeyboard->setKey(Input::NUM1);
				break;
			case sf::Keyboard::Num2:
				eventKeyboard->setKey(Input::NUM2);
				break;
			case sf::Keyboard::Num3:
				eventKeyboard->setKey(Input::NUM3);
				break;
			case sf::Keyboard::Num4:
				eventKeyboard->setKey(Input::NUM4);
				break;
			case sf::Keyboard::Num5:
				eventKeyboard->setKey(Input::NUM5);
				break;
			case sf::Keyboard::Num6:
				eventKeyboard->setKey(Input::NUM6);
				break;
			case sf::Keyboard::Num7:
				eventKeyboard->setKey(Input::NUM7);
				break;
			case sf::Keyboard::Num8:
				eventKeyboard->setKey(Input::NUM8);
				break;
			case sf::Keyboard::Num9:
				eventKeyboard->setKey(Input::NUM9);
				break;
			case sf::Keyboard::Num0:
				eventKeyboard->setKey(Input::NUM0);
				break;

			// any other keys
			default:
				unrecongnizedEvent = true;
				break;
			}

			if (!unrecongnizedEvent)
				if (sf::Keyboard::isKeyPressed(event.key.code)){
					eventKeyboardPressed->setKey(eventKeyboard->getKey());
					eventKeyboardPressed->setKeyboardAction(df::KEY_DOWN);
					Manager::onEvent(eventKeyboardPressed);
				}

				Manager::onEvent(eventKeyboard);
		}
	}
}