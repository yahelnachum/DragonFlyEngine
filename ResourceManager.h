#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

// system includes
#include <string>

// game engine includes
#include "Manager.h"
#include "Sprite.h"

#include "Sound.h"
#include "Music.h"

namespace df{
	// Maximum number of unique sprites in game.
	const int MAX_SPRITES = 1000;

	const int MAX_SOUNDS = 128;
	const int MAX_MUSICS = 128;

	// Delimiters used to parse Sprite files -
	// the ResourceManager `knows' file format.
	const std::string FRAMES_TOKEN =	 "frames";
	const std::string HEIGHT_TOKEN =	 "height";
	const std::string WIDTH_TOKEN =		 "width";
	const std::string COLOR_TOKEN =		 "color";
	const std::string END_FRAME_TOKEN =	 "end";
	const std::string END_SPRITE_TOKEN = "eof";

	class ResourceManager : public Manager {

	private:
		ResourceManager();                         // Private (a singleton).
		ResourceManager(ResourceManager const&);  // Don't allow copy.
		void operator=(ResourceManager const&);    // Don't allow assignment.
		Sprite *p_sprite[MAX_SPRITES];  // Array of (pointers to) sprites.
		int sprite_count;               // Count of number of loaded sprites.

		Sound sound[MAX_SOUNDS];		// Array of sound buffers
		int sound_count = 0;				// count of number of loaded sounds
		Music *music = new Music[MAX_MUSICS];		// array of music buffers
		int music_count = 0;				// count of number of loaded musics

	public:
		// destructor
		~ResourceManager();

		// Get the one and only instance of the ResourceManager.
		static ResourceManager &getInstance();

		// Get manager ready for resources.
		int startUp();

		// Shut down manager, freeing up any allocated Sprites.
		void shutDown();

		// Load Sprite from file.
		// Assign indicated label to sprite.
		// Return 0 if ok, else -1.
		int loadSprite(std::string filename, std::string label);

		// Unload Sprite with indicated label.
		// Return 0 if ok, else -1.
		int unloadSprite(std::string label);

		// Find Sprite with indicated label.
		// Return pointer to it if found, else NULL.
		Sprite *getSprite(std::string label) const;

		// load sound from file
		// return 0 if ok, else -1
		int loadSound(std::string filename, std::string label);

		// remove sound with indicated label.
		// return 0 if ok, else -1 
		int unloadSound(std::string label);

		// find sound with indicated label.
		// return pointer to it if found, else NULL.
		Sound *getSound(std::string label);

		// Associate file with music
		// return 0 if ok, else -1
		int loadMusic(std::string filename, std::string label);

		// remove label for Music with indicated label.
		// return 0 if ok, else -1
		int unloadMusic(std::string label);

		// find music with indicated label.
		// return pointer to it if found, else NULL
		Music *getMusic(std::string label);
	};
}
#endif