// game engine includes
#include "WorldManager.h"
#include "LogManager.h"

#include "Object.h"

// constructor, set default values
df::Object::Object(){
	// set defaults
	static int identifier = 0;
	id = identifier;
	pos = df::Position();
	identifier++;
	type = "Object";
	altitude = 2;

	x_velocity = 0;
	y_velocity = 0;
	
	x_velocity_countdown = 1;
	y_velocity_countdown = 1;
	
	solidness = df::HARD;

	p_sprite = NULL;
	sprite_center = true;
	sprite_index = 0;
	sprite_slowdown = 1;
	sprite_slowdown_count = 0;

	box = df::Box();

	// write to log that object was created
	df::LogManager::getInstance().writeLog("Object::Object created type: %s, id: %d\n", type.c_str(), id);

	// Add self to game world.
	df::WorldManager::getInstance().insertObject(this);
}

// destructor, remove object from world and write to log about deletion
df::Object::~Object(){
	// Remove self from game world.
	df::WorldManager::getInstance().removeObject(this);
	df::LogManager::getInstance().writeLog("Object::Object removed type: %s, id: %d\n", type.c_str(), id);
}

// Set object id.
void df::Object::setId(int new_id){
	id = new_id;
}

// Get object id.
int df::Object::getId() const{
	return id;
}

// Set type identifier of object.
void df::Object::setType(string new_type){
	type = new_type;
}

// Get type identifier of object.
string df::Object::getType() const{
	return type;
}

// Set Position of object.
void df::Object::setPosition(df::Position new_pos){
	pos = new_pos;
}

// Get Position of object.
df::Position df::Object::getPosition() const{
	return pos;
}

// Handle event (default is to ignore everything).
// Return 0 if ignored, else 1 if handled.
int df::Object::eventHandler(Event *p_e){
	return 0;
}

// Set object altitude.
// Checks for in range [0, MAX_ALTITUDE].
// Return 0 if ok, else -1.
int df::Object::setAltitude(int new_altitude){
	df::LogManager::getInstance().writeLog("alt %d\n", new_altitude);
	if (new_altitude <= df::MAX_ALTITUDE && new_altitude >= 0){
		altitude = new_altitude;
		return 0;
	}
	return -1;
}

// Return object altitude.
int df::Object::getAltitude() const{
	return altitude;
}

// Get and set velocity (x,y).
void df::Object::setXVelocity(float new_x_velocity){
	x_velocity = new_x_velocity;
	x_velocity_countdown = 1;
}

float df::Object::getXVelocity() const{
	return x_velocity;
}

void df::Object::setYVelocity(float new_y_velocity){
	y_velocity = new_y_velocity;
	y_velocity_countdown = 1;
}

float df::Object::getYVelocity() const{
	return y_velocity;
}

// Perform 1 step of velocity in horizontal direction.
// Return horizontal distance moved this step.
int df::Object::getXVelocityStep(){
	
	// See if object has velocity.
	if (x_velocity == 0)
		return 0;	// No velocity so no move.
	
	// See if moving this step.
	x_velocity_countdown -= fabs(x_velocity);
	if (x_velocity_countdown > 0)
		return 0;	// Not time to move.

	// Moving this step, so figure out how far.
	int spaces = floor(1 - x_velocity_countdown);
	x_velocity_countdown = 1 + fmod(x_velocity_countdown, 1);

	// Return number of spaces to move.
	if (x_velocity > 0)
		return spaces;
	else
		return (-1) * spaces;
}

// Perform 1 step of velocity in vertical direction.
// Return vertical distance moved this step.
int df::Object::getYVelocityStep(){
	// See if object has velocity.
	if (y_velocity == 0)
		return 0;	// No velocity so no move.

	// See if moving this step.
	y_velocity_countdown -= fabs(y_velocity);
	if (y_velocity_countdown > 0)
		return 0;	// Not time to move.

	// Moving this step, so figure out how far.
	int spaces = floor(1 - y_velocity_countdown);
	y_velocity_countdown = 1 + fmod(y_velocity_countdown, 1);

	// Return number of spaces to move.
	if (y_velocity > 0)
		return spaces;
	else
		return (-1) * spaces;
}

// True if HARD or SOFT, else false.
bool df::Object::isSolid(){
	
	if (getSolidness() == df::SPECTRAL)
		return false;

	return true;
}

// Set object solidness, with checks for consistency.
// Return 0 if ok, else -1.
int df::Object::setSolidness(df::Solidness new_solid){

	if (new_solid >= df::HARD && new_solid <= df::SPECTRAL){
		solidness = new_solid;
		return 0;
	}

	return -1;
}

// Return object solidness.
df::Solidness df::Object::getSolidness() const{
	return solidness;
}

// Set object Sprite to new one.
// If set_box is true, set bounding box to size of Sprite.
void df::Object::setSprite(Sprite *p_new_sprite, bool set_box){
	p_sprite = p_new_sprite;
	box.setHorizontal(p_new_sprite->getWidth());
	box.setVertical(p_new_sprite->getHeight());
}

// Return pointer to Sprite associated with this object.
df::Sprite *df::Object::getSprite() const{
	return p_sprite;
}

// Set Sprite to be centered at object Position (pos).
void df::Object::setCentered(bool centered){
	sprite_center = centered;
}

// Indicates if sprite is centered at object Position (pos).
bool df::Object::isCentered() const{
	return sprite_center;
}

// Set index of current Sprite frame to be displayed.
void df::Object::setSpriteIndex(int new_sprite_index){
	sprite_index = new_sprite_index;
}

// Return index of current Sprite frame to be displayed.
int df::Object::getSpriteIndex() const{
	return sprite_index;
}

// Slows down sprite animations.
// Sprite slowdown is in multiples of GameManager frame time.
void df::Object::setSpriteSlowdown(int new_sprite_slowdown){
	sprite_slowdown = new_sprite_slowdown;
}
int df::Object::getSpriteSlowdown() const{
	return sprite_slowdown;
}
void df::Object::setSpriteSlowdownCount(int new_sprite_slowdown_count){
	sprite_slowdown_count = new_sprite_slowdown_count;
}
int df::Object::getSpriteSlowdownCount() const{
	return sprite_slowdown_count;
}

// Draw single sprite frame.
// Drawing accounts for: centering, slowdown, advancing Sprite Frame.
void df::Object::draw(){

	// If sprite not defined, don’t continue further.
	if (p_sprite == NULL)
		return;
	
	int index = getSpriteIndex();

	// Ask graphics manager to draw current frame.
	df::GraphicsManager::getInstance().drawFrame(pos, p_sprite->getFrame(index), sprite_center, p_sprite->getColor());
	// If slowdown is 0, then animation is frozen.
	if (getSpriteSlowdown() == 0)
		return;

	// Increment counter.
	int count = getSpriteSlowdownCount();
	count++;

	// Advance sprite index, if appropriate.
	if (count >= getSpriteSlowdown()){
		count = 0;          // Reset counter.
		index++;     // Advance frame.

		// If at last frame, loop to beginning.
		if (index >= p_sprite->getFrameCount())
			index = 0;

		setSpriteIndex(index);         // Set index for next draw().
	}

	setSpriteSlowdownCount(count); // Set counter for next draw().
}

// Set object's bounding box.
void df::Object::setBox(df::Box new_box){
	box = new_box;
}

// Get object's bounding box.
df::Box df::Object::getBox() const{
	return box;
}
