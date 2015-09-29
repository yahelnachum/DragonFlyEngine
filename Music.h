#ifndef __MUSIC_H__
#define __MUSIC_H__

// system includes.
#include <string>
#include <SFML/Audio.hpp>

namespace df{
	class Music{
	
	private:
		sf::Music music;
		std::string label;
		Music(Music const&);
		void operator=(Music const&);

	public:
		Music();

		// Associate music buffer with file.
		// Return 0 if ok, else -1
		int loadMusic(std::string filename);

		// Set labl associated with music.
		void setLabel(std::string new_label);

		// Get label associated with music.
		std::string getLabel() const;

		// Play music
		// If loop is true, repeat play when done.
		void play(bool loop = true);

		// Stop music.
		void stop();

		// pause music.
		void pause();

		// Return pointer to sfml music.
		sf::Music *getMusic();
	};
}
#endif