// system includes
#include <iostream>
#include <fstream>
#include <stdlib.h>

// game engine includes
#include "LogManager.h"
#include "ResourceManager.h"

// constructor private
df::ResourceManager::ResourceManager(){
	// Private (a singleton).
	setType("ResourceManager");
	sprite_count = 0;
}

// copying constructor
df::ResourceManager::ResourceManager(ResourceManager const&){
	// Don't allow copy.
	setType("ResourceManager");
	sprite_count = 0;
}

// destructor
df::ResourceManager::~ResourceManager(){
}

// Get the one and only instance of the ResourceManager.
df::ResourceManager &df::ResourceManager::getInstance(){
	static ResourceManager resource_manager;
	return resource_manager;
}

// Get manager ready for resources.
int df::ResourceManager::startUp(){
	return 0;
}

// Shut down manager, freeing up any allocated Sprites.
void df::ResourceManager::shutDown(){
}

// Read single line `tag number', return number
int readLineInt(std::ifstream *p_file, int *p_line_number, const char *tag){
	string line;

	// get line from file
	getline(*p_file, line);

	// check if tag is in line
	if (line.find(tag) == std::string::npos){
		df::LogManager::getInstance().writeLog("LogManger::readLineInt(): Could not find tag \"%s\" on line %d\n", tag, *p_line_number);
		return -1;
	}

	// get everything but the tag
	string sub = tag;
	sub.append(" ");
	int number = atoi(line.substr(sub.length()).c_str());

	// increment the line number
	(*p_line_number)++;

	// return the number
	return number;
}

// Read single line `tag string', return string.
std::string readLineStr(std::ifstream *p_file, int *p_line_number, const char *tag){
	string line;

	// get a line from the file
	getline(*p_file, line);

	// make sure tag is in the line
	if (line.compare(tag) == std::string::npos){
		df::LogManager::getInstance().writeLog("ResourceManager::readLineStr(): Error line %d. Could not find tag \"%s\".\n", *p_line_number, tag);
		return "-1";
	}

	// get everything but the tag
	string sub = tag;
	sub.append(" ");
	string result = line.substr(sub.length()).c_str();

	// increment line number
	(*p_line_number)++;

	// return string
	return result;
}

// Read frame until `eof', return Frame.
df::Frame readFrame(std::ifstream *p_file, int *p_line_number, int width, int height){
	string line, frame_str;

	// loop accross the height of the frame
	for (int i = 1; i <= height; i++){

		// get a line from the file
		getline(*p_file, line); // Error check.

		// check to see if the line length is the same as the width of the frame
		if (line.length() > width){
			df::LogManager::getInstance().writeLog("ResourceManager::readFrame(): Error line %d. Line width is %d, expected %d\n", *p_line_number, line.length(), width);
			return df::Frame();
		}

		// add the line to the frame
		frame_str += line;
		
		// increment line number
		(*p_line_number)++;

	}

	// get the next line from the file
	getline(*p_file, line); // Error check.

	// if the line is not end then write to log
	if (line.compare(df::END_FRAME_TOKEN) == std::string::npos){
		df::LogManager::getInstance().writeLog("ResourceManager::readFrame(): Error line %d. end expected but not found\n", *p_line_number);
		return df::Frame();
	}

	// increment line number
	(*p_line_number)++;

	// create frame from file input taken and return it
	df::Frame frame = df::Frame(width, height, frame_str);
	return frame;
}

// change a color string into an integer
df::Color stringToColor(std::string color){
	if (color.compare("black") == 0)
		return df::BLACK;
	if (color.compare("red") == 0)
		return df::RED;
	if (color.compare("green") == 0)
		return df::GREEN;
	if (color.compare("yellow") == 0)
		return df::YELLOW;
	if (color.compare("blue") == 0)
		return df::BLUE;
	if (color.compare("magenta") == 0)
		return df::MAGENTA;
	if (color.compare("cyan") == 0)
		return df::CYAN;
	else
		return df::WHITE;
}

// Load Sprite from file.
// Assign indicated label to sprite.
// Return 0 if ok, else -1.
int df::ResourceManager::loadSprite(std::string filename, std::string label){
	

	string line;
	std::ifstream myfile(filename);

	if (myfile.is_open()){
		int lineNumber = 1;

		// write to log
		df::LogManager::getInstance().writeLog("ResourceManager::loadSprite(): starting loading sprite \"%s\" with label: %s\n",
			filename.c_str(), label.c_str());

		// get header of file
		int frames = readLineInt(&myfile, &lineNumber, df::FRAMES_TOKEN.c_str());
		int width = readLineInt(&myfile, &lineNumber, df::WIDTH_TOKEN.c_str());
		int height = readLineInt(&myfile, &lineNumber, df::HEIGHT_TOKEN.c_str());
		string color = readLineStr(&myfile, &lineNumber, df::COLOR_TOKEN.c_str());

		// create a sprite with header
		df::Sprite *sprite = new df::Sprite(frames);
		sprite->setWidth(width);
		sprite->setHeight(height);
		sprite->setColor(stringToColor(color));
		sprite->setLabel(label);

		// get the frames from the file
		while (myfile.good()) {
			df::Frame frame = readFrame(&myfile, &lineNumber, width, height);
			sprite->addFrame(frame);
		}

		// add sprite into list
		p_sprite[sprite_count] = sprite;
		sprite_count++;

		// Close file when done.
		myfile.close();

		df::LogManager::getInstance().writeLog("ResourceManager::loadSprite(): done loading sprite \"%s\" with label: %s\n",
			filename.c_str(), label.c_str());
	}
	else{
		df::LogManager::getInstance().writeLog("ResourceManager::loadSprite(): Error. could not open file \"%s\"\n", filename.c_str());
		return -1;
	}
}

// Unload Sprite with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadSprite(std::string label){
	for (int i = 0; i < sprite_count; i++){

		// delete sprite if the labels are the same
		if (label.compare(p_sprite[i]->getLabel()) == 0){
			delete p_sprite[i];

			// scoot over remaining sprites
			for (int j = i; j < sprite_count - 1; j++){
				p_sprite[j] = p_sprite[j + 1];
			}

			sprite_count--;

			return 0;
		}
		
	}
	return -1; // sprite not found
}

// Find Sprite with indicated label.
// Return pointer to it if found, else NULL.
df::Sprite *df::ResourceManager::getSprite(std::string label) const{
	for (int i = 0; i < sprite_count; i++){
		if (p_sprite[i]->getLabel().compare(label) != std::string::npos)
			return p_sprite[i];
	}

	// return NULL if not found
	return NULL;
}

// load sound from file
// return 0 if ok, else -1
int df::ResourceManager::loadSound(std::string filename, std::string label){
	
	if (sound_count == MAX_SOUNDS){
		df::LogManager::getInstance().writeLog("ResourceManager::loadSound(): sound array full\n");
		return -1;	// error
	}

	if (sound[sound_count].loadSound(filename) == -1){
		df::LogManager::getInstance().writeLog("ResourceManager::loadSound(): unable to load from file\n");
		return -1;	// error
	}

	// all set
	sound[sound_count].setLabel(label);
	sound_count++;
	return 0;
}

// remove sound with indicated label.
// return 0 if ok, else -1 
int df::ResourceManager::unloadSound(std::string label){
	for (int i = 0; i < sound_count; i++){
		if (label == sound[i].getLabel()){
			// scoot over remaining sounds
			for (int j = i; j < sound_count; j++){
				sound[j] = sound[j + 1];
			}

			sound_count--;
			return 0;
		}
	}

	return -1; // sound not found
}

// find sound with indicated label.
// return pointer to it if found, else NULL.
df::Sound *df::ResourceManager::getSound(std::string label){
	for(int i = 0; i < sound_count; i++){
		if (label == sound[i].getLabel()){
			return &sound[i];
		}
	}

	return NULL; // sound not found
}

// Associate file with music
// return 0 if ok, else -1
int df::ResourceManager::loadMusic(std::string filename, std::string label){
	if (music_count == MAX_MUSICS){
		df::LogManager::getInstance().writeLog("ResourceManager::loadMusic(): music array full\n");
		return -1;	// error
	}

	if (music[music_count].loadMusic(filename) == -1){
		df::LogManager::getInstance().writeLog("ResourceManager::loadMusic(): unable to load from file\n");
		return -1;	// error
	}

	// all set
	music[music_count].setLabel(label);
	music_count++;
	return 0;
}

// remove label for Music with indicated label.
// return 0 if ok, else -1
int df::ResourceManager::unloadMusic(std::string label){
	for (int i = 0; i < music_count; i++){
		if (label == music[i].getLabel()){
			// scoot over remaining sounds
			for (int j = i; j < music_count; j++){
				//music[j] = music[j + 1];
			}

			music_count--;
			return 0;
		}
	}

	return -1; // music not found
}

// find music with indicated label.
// return pointer to it if found, else NULL
df::Music *df::ResourceManager::getMusic(std::string label){
	for (int i = 0; i < music_count; i++){
		if (label == music[i].getLabel()){
			return &music[i];
		}
	}

	return NULL; // music not found
}