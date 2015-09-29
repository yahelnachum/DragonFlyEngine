#ifndef __SPRITE_H__
#define __SPRITE_H__

// system includes
#include <string>

// game engine includes
#include "Frame.h"
#include "GraphicsManager.h"

namespace df{
	class Sprite {

	private:
		int width;                    // Sprite width.
		int height;                   // Sprite height.
		int max_frame_count;          // Maximum number of frames sprite can have.
		int frame_count;              // Actual number of frames sprite has.
		df::Color color;              // Optional color for entire sprite.
		df::Frame *frame;             // Array of frames.
		std::string label;            // Text label to identify sprite.
		Sprite();                     // Sprite constructor always has one arg.

	public:
		// Destroy sprite, deleting any allocated frames.
		~Sprite();

		// Create sprite with indicated maximum number of frames.
		Sprite(int max_frames);

		// Set width of sprite.
		void setWidth(int new_width);

		// Get width of sprite.
		int getWidth() const;

		// Set height of sprite.
		void setHeight(int new_height);

		// Get height of sprite.
		int getHeight() const;

		// Set sprite color.
		void setColor(df::Color new_color);

		// Get sprite color.
		df::Color getColor() const;

		// Get total count of frames in sprite.
		int getFrameCount();

		// Add frame to sprite.
		// Return -1 if frame array full, else 0.
		int addFrame(df::Frame new_frame);

		// Get next sprite frame indicated by number.
		// Return empty frame if out of range [0, frame_count].
		df::Frame getFrame(int frame_number) const;

		// Set label associated with sprite.
		void setLabel(std::string new_label);

		// Get label associated with sprite.
		std::string getLabel() const;
	};
}
#endif