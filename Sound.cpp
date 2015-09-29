#include "Sound.h"

df::Sound::Sound(){
	sound = sf::Sound();
}

df::Sound::~Sound(){

}

// Load sound buffer from file.
// Retrun 0 if ok, else -1.
int df::Sound::loadSound(std::string filename){
	
	if (sound_buffer.loadFromFile(filename)){
		sound = sf::Sound(sound_buffer);
		return 0;
	}

	return -1;
}

// Set label associated with sound.
void df::Sound::setLabel(std::string new_label){
	label = new_label;
}

// Get label associated with sound.
std::string df::Sound::getLabel() const{
	return label;
}

//Play sound.
// If loop is true, repeat play when done.
void df::Sound::play(bool loop){
	sound.setLoop(loop);
	sound.play();
}

// Stop sound.
void df::Sound::stop(){
	sound.stop();
}

// Pause sound.
void df::Sound::pause(){
	sound.pause();
}

// Return sfml sound.
sf::Sound df::Sound::getSound() const{
	return sound;
}