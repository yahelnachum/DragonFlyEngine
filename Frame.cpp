// game engine includes
#include "Frame.h"

// Create empty frame.
df::Frame::Frame(){
	frame_str = "";
	width = 0;
	height = 0;
}

// Create frame of indicated width and height with string.
df::Frame::Frame(int new_width, int new_height, std::string frame_str){
	width = new_width;
	height = new_height;
	this->frame_str = frame_str;
}

// Set width of frame.
void df::Frame::setWidth(int new_width){
	width = new_width;
}

// Get width of frame.
int df::Frame::getWidth() const{
	return width;
}

// Set height of frame.
void df::Frame::setHeight(int new_height){
	height = new_height;
}

// Get height of frame.
int df::Frame::getHeight() const{
	return height;
}

// Set frame characters (stored as string).
void df::Frame::setString(std::string new_frame_str){
	frame_str = new_frame_str;
}

// Get frame characters (stored as string).
std::string df::Frame::getString() const{
	return frame_str;
}