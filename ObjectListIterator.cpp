
// game engine includes
#include "ObjectListIterator.h"

// constructor, private because it must be given list to use
df::ObjectListIterator::ObjectListIterator(){
	// Must be given list when created.
}

// Create iterator, over indicated list.
df::ObjectListIterator::ObjectListIterator(const ObjectList *p_l){
	p_list = p_l;
	index = 0;
}

// go to first item in list
void df::ObjectListIterator::first(){
	// Set iterator to first item in list.
	index = 0;
}

// go to next item in list
void df::ObjectListIterator::next(){
	// Set iterator to next item in list.
	index++;
}

// check if the iterator is done iterating over the whole list
bool df::ObjectListIterator::isDone() const{
	// Return true if at end of list.
	return (index >= p_list->getCount());
}

// Return pointer to current Object, NULL if done/empty.
df::Object *df::ObjectListIterator::currentObject() const{
	if (isDone()){
		return NULL;
	}
	return p_list->list[index];
}