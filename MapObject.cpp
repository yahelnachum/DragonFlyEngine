#include "MapObject.h"

MapObject::MapObject(){
	setSolidness(df::SPECTRAL);
	setAltitude(0);
}

MapObject::~MapObject(){

}

bool MapObject::onMapObject(df::Position pos){
	return true;
}
