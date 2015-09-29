#include "Music.h"

df::Music::Music(){
}

// Associate music buffer with file.
// Return 0 if ok, else -1
int df::Music::loadMusic(std::string filename){
	if (music.openFromFile(filename))
		return 0;
	
	return -1;
}

// Set labl associated with music.
void df::Music::setLabel(std::string new_label){
	label = new_label;
}

// Get label associated with music.
std::string df::Music::getLabel() const{
	return label;
}

// Play music
// If loop is true, repeat play when done.
void df::Music::play(bool loop){
	music.setLoop(loop);
	music.play();
}

// Stop music.
void df::Music::stop(){
	music.stop();
}

// pause music.
void df::Music::pause(){
	music.pause();
}

// Return pointer to sfml music.
sf::Music *df::Music::getMusic(){
	return &music;
}