#ifndef _SOUND_H__
#define _SOUND_H__

// system includes
#include <string>
#include <SFML/Audio.hpp>

namespace df{
	class Sound{

	private:
		sf::Sound sound;				// the sfml sound.
		sf::SoundBuffer sound_buffer;	// sfml sound buffer associated with sound.
		std::string label;				// text label to identify sound.

	public:
		Sound();
		~Sound();

		// Load sound buffer from file.
		// Retrun 0 if ok, else -1.
		int loadSound(std::string filename);

		// Set label associated with sound.
		void setLabel(std::string new_label);

		// Get label associated with sound.
		std::string getLabel() const;

		//Play sound.
		// If loop is true, repeat play when done.
		void play(bool loop = false);

		// Stop sound.
		void stop();

		// Pause sound.
		void pause();

		// Return sfml sound.
		sf::Sound getSound() const;
	};
}
#endif