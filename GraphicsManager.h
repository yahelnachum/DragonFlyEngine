#ifndef __GRAPHICS_MANAGER_H__
#define __GRAPHICS_MANAGER_H__

// SFML includes
#include <SFML/Graphics.hpp>

// game engine includes
#include "Manager.h"
#include "Position.h"
#include "Frame.h"

namespace df{

	// Colors Dragonfly recognizes.
	enum Color {
		BLACK = 0,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
	};

	// justification of text
	enum Justification {
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED,
	};

	// If color not specified, will use this.
	const Color COLOR_DEFAULT = WHITE;

	// Defaults for SFML window.
	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	
	const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;

	const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
	
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
	const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
	const std::string FONT_FILE_DEFAULT = "df-font.ttf";

	class GraphicsManager : public Manager {

	private:
		GraphicsManager();                      // Private (a singleton).
		GraphicsManager(GraphicsManager const&);// No copying.
		void operator=(GraphicsManager const&); // No assignment.

		sf::Font font;                // Font used for ASCII graphics.
		sf::RenderWindow *p_window;   // Pointer to SFML window.

		int window_horizontal_pixels; // Horizontal pixels in window.
		int window_vertical_pixels;   // Vertical pixels in window.

		int window_horizontal_chars;  // Horizontal ASCII spaces in window.
		int window_vertical_chars;    // Vertical ASCII spaces in window.

	public:
		// Get the one and only instance of the GraphicsManager.
		static GraphicsManager &getInstance();

		// Open graphics window ready for text-based display.
		// Return 0 if ok, else -1.
		int startUp();

		// Close graphics window.
		void shutDown();

		// Draw a character at screen location (x,y) with color.
		// Return 0 if ok, else -1.
		int drawCh(Position world_pos, char ch, Color color) const;

		// Return window's horizontal maximum (in characters).
		int getHorizontal() const;

		// Return window's vertical maximum (in characters).
		int getVertical() const;

		// Return window's horizontal maximum (in pixels).
		int getHorizontalPixels() const;

		// Return window's vertical maximum (in pixels).
		int getVerticalPixels() const;

		// Render current display buffer.
		// Return 0 if ok, else -1.
		int swapBuffers();

		// Return pointer to SFML drawing window.
		sf::RenderWindow *getWindow() const;

		// Compute character height, based on window size and font.
		float charHeight();

		// Compute character width, based on window size and font.
		float charWidth();

		// Convert ASCII spaces (x,y) to window pixels (x,y).
		Position spacesToPixels(Position spaces);

		// Convert window pixels (x,y) to ASCII spaces (x,y).
		Position pixelsToSpaces(Position pixels);

		// Draw string at screen location (x,y) with color.
		// Justified LEFT, CENTER or RIGHT.
		// Return 0 if ok, else -1.
		int drawString(Position world_pos, std::string str, Justification just, Color color) const;

		// Draw single sprite frame at screen location (x,y) with color.
		// If centered true then center frame at (x,y).
		// Return 0 if ok, else -1.
		int drawFrame(Position world_pos, df::Frame frame, bool centered, df::Color color) const;

	};
}
#endif