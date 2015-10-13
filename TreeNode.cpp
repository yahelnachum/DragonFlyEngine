// game engine includes
#include "LogManager.h"

// IHOP includes
#include "TreeNode.h"
#include "MapManager.h"

// default constructor
TreeNode::TreeNode(){
	pos = df::Position(1,1);
	childrenCount = 0;
	children = new TreeNode*[4];
	parent = this;
	nodeLevel = 0;
}

// constructor with position
TreeNode::TreeNode(df::Position position){
	pos = position;
	childrenCount = 0;
	children = new TreeNode*[4];
	nodeLevel = 0;
	parent = this;
}

// constructor with position, parent, and level in tree
TreeNode::TreeNode(df::Position position, TreeNode *par, int nLevel){
	pos = position;
	childrenCount = 0;
	children = new TreeNode*[4];
	parent = par;
	nodeLevel = nLevel;
}

// add a child with a position and a level in tree
void TreeNode::addChild(df::Position position, int nLevel){
	children[childrenCount] = new TreeNode(position, this, nLevel);
	childrenCount++;
}

// return array of children
TreeNode** TreeNode::getChildren(){
	return children;
}

// return number of children in array
int TreeNode::getChildrenCount(){
	return childrenCount;
}

// get position of node
df::Position TreeNode::getPosition(){
	return pos;
}

// get tree level of node
int TreeNode::getLevel(){
	return nodeLevel;
}

// get parent of node
TreeNode * TreeNode::getParent(){
	return parent;
}

// get valid children of node down to depth of level
void TreeNode::getValidChildren(int level, TreeNode *base, df::Position to, bool detail){
	// if at last level then return
	if (level == 0){
		return;
	}

	// get positions in all directions
	MapManager &mm = MapManager::getInstance();
	bool onFork = false;
	df::Position posUp = df::Position(base->getPosition().getX(), base->getPosition().getY() - 1);
	if (!detail){
		while (mm.onMap(posUp) && !onFork){
			if (posUp.equalTo(to))
				onFork = true;
			else
				posUp = df::Position(posUp.getX(), posUp.getY() - 1);
			if (mm.onMap(df::Position(posUp.getX() + 1, posUp.getY())) ||
				mm.onMap(df::Position(posUp.getX() - 1, posUp.getY()))){
				onFork = true;
			}
		}
		onFork = false;
	}
	df::Position posDown = df::Position(base->getPosition().getX(), base->getPosition().getY() + 1);
	if (!detail){
		while (mm.onMap(posDown) && !onFork){
			if (posDown.equalTo(to))
				onFork = true;
			else
				posDown = df::Position(posDown.getX(), posDown.getY() + 1);
			if (mm.onMap(df::Position(posDown.getX() + 1, posDown.getY())) ||
				mm.onMap(df::Position(posDown.getX() - 1, posDown.getY()))){
				onFork = true;
			}
		}
		onFork = false;
	}
	df::Position posLeft = df::Position(base->getPosition().getX() - 1, base->getPosition().getY());
	if (!detail){
		while (mm.onMap(posLeft) && !onFork){
			if (posLeft.equalTo(to))
				onFork = true;
			else
				posLeft = df::Position(posLeft.getX() - 1, posLeft.getY());
			if (mm.onMap(df::Position(posLeft.getX(), posLeft.getY() + 1)) ||
				mm.onMap(df::Position(posLeft.getX(), posLeft.getY() - 1))){
				onFork = true;
			}
		}
		onFork = false;
	}
	df::Position posRight = df::Position(base->getPosition().getX() + 1, base->getPosition().getY());
	if (!detail){
		while (mm.onMap(posRight) && !onFork){
			if (posRight.equalTo(to))
				onFork = true;
			else
				posRight = df::Position(posRight.getX() + 1, posRight.getY());
			if (mm.onMap(df::Position(posRight.getX(), posRight.getY() + 1)) ||
				mm.onMap(df::Position(posRight.getX(), posRight.getY() - 1))){
				onFork = true;
			}
		}
	}
	
	// check if position is on map
	// if so then add it to children
	if (mm.onMap(posUp) && !posUp.equalTo(base->getParent()->getPosition())){
		base->addChild(posUp, base->getLevel() + 1);
	}
	if (mm.onMap(posDown) && !posDown.equalTo(base->getParent()->getPosition())){
		base->addChild(posDown, base->getLevel() + 1);
	}
	if (mm.onMap(posLeft) && !posLeft.equalTo(base->getParent()->getPosition())){
		base->addChild(posLeft, base->getLevel() + 1);
	}
	if (mm.onMap(posRight) && !posRight.equalTo(base->getParent()->getPosition())){
		base->addChild(posRight, base->getLevel() + 1);
	}

	// decrease level and get children of each child
	level--;

	for (int i = 0; i < base->getChildrenCount(); i++){
		getValidChildren(level, (base->getChildren()[i]), to, detail);
	}
}

// include for printing
#include <iostream>
using std::printf;
// print tree
void TreeNode::printTree(TreeNode *base){
	printf("x:%d, y:%d - \n", base->getPosition().getX(), base->getPosition().getY());
	for (int i = 0; i < base->getChildrenCount(); i++){
		printTree(base->getChildren()[i]);
	}
}

// get path to the position given using the given depth
df::Position* TreeNode::pathToPosition(TreeNode *base, df::Position posTo, int *size, int nLevel, bool detail){
	// get all valid children
	getValidChildren(nLevel, base, posTo, detail);
	// get lowest tree
	TreeNode *lowest = TreeNode::findLowestTreeNode(base, posTo);
	
	// get length of path
	(*size) = lowest->getLevel();
	df::Position *path = new df::Position[(*size)];

	// fill array of positions with path to given position
	for (int i = (*size); i >= 0; i--){
		path[i] = lowest->getPosition();
		lowest = lowest->getParent();
	}

	// return path found
	return path;
}

// find shallowest node that is closest to position given
TreeNode * TreeNode::findLowestTreeNode(TreeNode *base, df::Position pos){
	// if node position is equal to searching position
	if (base->getPosition().equalTo(pos)){
		return base;
	}
	// if node has no children
	if (base->getChildrenCount() == 0){
		return base;
	}

	// keep trak of lowest node
	TreeNode *lowestNode = new TreeNode(df::Position(-1000,1000), base, 1000);;
	// go through children and find lowest node on their trees
	for (int i = 0; i < base->getChildrenCount(); i++){
		TreeNode *possible = findLowestTreeNode(base->getChildren()[i], pos);

		// if new node is lower than current the assign current to lower node
		if (possible->getPosition().getManhattanDistance(pos) + possible->getLevel() < lowestNode->getPosition().getManhattanDistance(pos) + lowestNode->getLevel()){
			lowestNode = possible;
		}
	}

	// return lowest node
	return lowestNode;
}