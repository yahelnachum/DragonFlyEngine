// game engine includes
#include "GraphicsManager.h"
#include "LogManager.h"

#include "Position.h"
#include "Utility.h"
#include "Frame.h"

// constructor
df::GraphicsManager::GraphicsManager(){
	setType("GraphicsManager");
}

// overloaded constructor
df::GraphicsManager::GraphicsManager(GraphicsManager const&){
	setType("GraphicsManager");
}

// Get the one and only instance of the GraphicsManager.
df::GraphicsManager &df::GraphicsManager::getInstance(){
	static GraphicsManager graphics_manager;
	return graphics_manager;
}

// Open graphics window ready for text-based display.
// Return 0 if ok, else -1.
int df::GraphicsManager::startUp() {

	// If window already created, do nothing.
	if (p_window != NULL){
		return 0;
	}

	// Create window to draw on.
	p_window = new sf::RenderWindow(sf::VideoMode(WINDOW_HORIZONTAL_PIXELS_DEFAULT, WINDOW_VERTICAL_PIXELS_DEFAULT), WINDOW_TITLE_DEFAULT);

	// Turn off mouse cursor for window.
	p_window->setMouseCursorVisible(false);

	// Synchronize refresh rate with monitor.
	p_window->setVerticalSyncEnabled(true);

	// load font
	if (font.loadFromFile("df-font.ttf") == false) {
		df::LogManager::getInstance().writeLog("GraphicsManager::startUp() Error! Unable to load font 'df-font.ttf'.\n");
		return -1;
	}

	df::LogManager::getInstance().writeLog("GraphicsManager::startUp() GraphicsManager has started up.\n");
	return df::Manager::startUp();
}

// Close graphics window.
void df::GraphicsManager::shutDown() {
	p_window->close();
	df::Manager::shutDown();
	df::LogManager::getInstance().writeLog("GraphicsManager::shutDown() GraphicsManager has been shutdown.\n");
}

// Draw a character at screen location (x,y) with color.
// Return 0 if ok, else -1.
int df::GraphicsManager::drawCh(Position world_pos, char ch, df::Color color) const {
	
	// Make sure window is allocated.
	if (p_window == NULL)
		return -1;

	Position view_pos = df::Utility::worldToView(world_pos);

	df::GraphicsManager &gm = df::GraphicsManager::getInstance();
	// Convert spaces (x,y) to pixels (x,y).
	Position pixel_pos = gm.spacesToPixels(view_pos);

	// Draw background rectangle since text is "see through" in SFML.
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(gm.charWidth(), gm.charHeight() - 1));
	rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
	rectangle.setPosition(pixel_pos.getX() + gm.charWidth() / 2 - 5, pixel_pos.getY() + gm.charHeight() / 2 - 12);
	p_window->draw(rectangle);

	// Create character text to draw.
	static sf::Text text("", font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold); // Make bold, since looks better. 

	// Scale to right size.
	if (gm.charWidth() < gm.charHeight())
		text.setCharacterSize(gm.charWidth() * 2);
	else
		text.setCharacterSize(gm.charHeight() * 2);

	// Set SFML color based on Dragonfly color.
	switch (color){
	case df::BLACK:
		text.setColor(sf::Color::Black);
		break;
	case df::RED:
		text.setColor(sf::Color::Red);
		break;
	case df::GREEN:
		text.setColor(sf::Color::Green);
		break;
	case df::YELLOW:
		text.setColor(sf::Color::Yellow);
		break;
	case df::BLUE:
		text.setColor(sf::Color::Blue);
		break;
	case df::MAGENTA:
		text.setColor(sf::Color::Magenta);
		break;
	case df::CYAN:
		text.setColor(sf::Color::Cyan);
		break;
	case df::WHITE:
		text.setColor(sf::Color::White);
		break;
	default:
		text.setColor(sf::Color::White);
		break;
	}

	// Set position in window (in pixels).
	text.setPosition(pixel_pos.getX(), pixel_pos.getY());

	// Draw character.
	p_window->draw(text);

	return 0;
}

// Return window's horizontal maximum (in characters).
int df::GraphicsManager::getHorizontal() const {
	return WINDOW_HORIZONTAL_CHARS_DEFAULT;
}

// Return window's vertical maximum (in characters).
int df::GraphicsManager::getVertical() const {
	return WINDOW_VERTICAL_CHARS_DEFAULT;
}

// Return window's horizontal maximum (in pixels).
int df::GraphicsManager::getHorizontalPixels() const {
	return WINDOW_HORIZONTAL_PIXELS_DEFAULT;
}
// Return window's vertical maximum (in pixels).
int df::GraphicsManager::getVerticalPixels() const {
	return WINDOW_VERTICAL_PIXELS_DEFAULT;
}

// Render current display buffer.
// Return 0 if ok, else -1.
int df::GraphicsManager::swapBuffers() {
	
	// Make sure window is allocated.
	if (p_window == NULL)
		return -1;

	// Display current window.
	p_window->display();

	// Clear window to get ready for next draw.
	p_window->clear();

	return 0; // Success.
}

// Return pointer to SFML drawing window.
sf::RenderWindow *df::GraphicsManager::getWindow() const {
	return p_window;
}

// Compute character height, based on window size and font.
float df::GraphicsManager::charHeight(){
	return (float)getVerticalPixels() / (float)getVertical();
}

// Compute character width, based on window size and font.
float df::GraphicsManager::charWidth(){
	return (float)getHorizontalPixels() / (float)getHorizontal();
}

// Convert ASCII spaces (x,y) to window pixels (x,y).
df::Position df::GraphicsManager::spacesToPixels(Position spaces){
	return Position(spaces.getX() * charWidth(), spaces.getY() * charHeight());
}

// Convert window pixels (x,y) to ASCII spaces (x,y).
df::Position df::GraphicsManager::pixelsToSpaces(Position pixels){
	return Position(pixels.getX() / charWidth(), pixels.getY() / charHeight());
}

// Draw string at screen location (x,y) with color.
// Justified LEFT, CENTER or RIGHT.
// Return 0 if ok, else -1.
int df::GraphicsManager::drawString(Position world_pos, std::string str, Justification just, Color color) const{

	// Get starting position.
	Position starting_pos = world_pos;
	switch (just){
		case CENTER_JUSTIFIED:
			starting_pos.setX(world_pos.getX() - str.size() / 2);
			break;
		case RIGHT_JUSTIFIED:
			starting_pos.setX(world_pos.getX() - str.size());
			break;
		case LEFT_JUSTIFIED:
			break;
		default:
			break;
	}

	int ret;
	// Draw string character by character.
	for (int i = 0; i < str.size(); i++){
		Position temp_pos(starting_pos.getX() + i, starting_pos.getY());
		ret = df::GraphicsManager::getInstance().drawCh(temp_pos, str[i], color);
	}

	return ret;
}

// Draw single sprite frame at screen location (x,y) with color.
// If centered true then center frame at (x,y).
// Return 0 if ok, else -1.
int df::GraphicsManager::drawFrame(df::Position world_pos, df::Frame frame, bool centered, Color color) const{
	// Error check empty string.
	if (frame.getString().compare("") == 0){
		return -1;
	}

	int x_offset, y_offset;
	// Centered?  Then offset (x,y) by 1/2 (width,height).
	if (centered){
		x_offset = frame.getWidth() / 2;
		y_offset = frame.getHeight() / 2;
	}
	else{
		x_offset = 0;
		y_offset = 0;
	}

	// Frame data stored in string.
	std::string str = frame.getString();

	// Draw row by row, character by character.
	for (int y = 0; y < frame.getHeight(); y++){
		for (int x = 0; x < frame.getWidth(); x++){
			Position temp_pos(world_pos.getX() - x_offset + x, world_pos.getY() - y_offset + y);
			drawCh(temp_pos, str[y * frame.getWidth() + x], color);
		}// x
	}// y
}
	