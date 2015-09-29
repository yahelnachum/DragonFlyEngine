// game engine includes
#include "ObjectList.h"

// constructor, set all objects in list to NULL
df::ObjectList::ObjectList(){
	count = 0;
	for (int i = 0; i < MAX_OBJECTS; i++){
		list[i] = NULL;
	}
}

// Insert object pointer in list.
// Return 0 if ok, else -1.
int df::ObjectList::insert(Object *p_o){
	// insert object in next spot of array
	if(getCount() < MAX_OBJECTS){
		list[getCount()] = p_o;
		count++;
		return 0;
	}
	return -1;
}

// Remove object pointer from list.
// Return 0 if found, else -1.
int df::ObjectList::remove(Object *p_o){
	// find object and remove it from list
	for (int i = 0; i < MAX_OBJECTS; i++){
		if (list[i] == p_o){
			// remove object
			list[i] = NULL;
			count--;
			// push everything in the array after that up by one
			for (int j = i; j < MAX_OBJECTS - 1; j++){
				list[j] = list[j + 1];
			}
			// add NULL for the last spot
			list[MAX_OBJECTS - 1] = NULL;
			return 0;
		}
	}
	return -1;
}

// Clear list (setting count to 0).
void df::ObjectList::clear(){
	// set all objects in list to NULL
	count = 0;
	for (int i = 0; i < MAX_OBJECTS; i++){
		list[i] = NULL;
	}
}

// Return count of number of objects in list.
int df::ObjectList::getCount() const{
	return count;
}

// Return true if list is empty, else false.
bool df::ObjectList::isEmpty() const{
	return (count == 0);
}

// Return true if list is full, else false.
bool df::ObjectList::isFull() const{
	return (count == MAX_OBJECTS);
}