#include "LogManager.h"

#include "TreeNode.h"
#include "MapManager.h"

TreeNode::TreeNode(){
	pos = df::Position(1,1);
	childrenCount = 0;
	children = new TreeNode*[4];
	parent = this;
	nodeLevel = 0;
}

TreeNode::TreeNode(df::Position position){
	pos = position;
	childrenCount = 0;
	children = new TreeNode*[4];
	nodeLevel = 0;
	parent = this;
}

TreeNode::TreeNode(df::Position position, TreeNode *par, int nLevel){
	pos = position;
	childrenCount = 0;
	children = new TreeNode*[4];
	parent = par;
	nodeLevel = nLevel;
}

void TreeNode::addChild(df::Position position, int nLevel){
	children[childrenCount] = new TreeNode(position, this, nLevel);
	childrenCount++;
}

TreeNode** TreeNode::getChildren(){
	return children;
}

int TreeNode::getChildrenCount(){
	return childrenCount;
}

df::Position TreeNode::getPosition(){
	return pos;
}

int TreeNode::getLevel(){
	return nodeLevel;
}

TreeNode * TreeNode::getParent(){
	return parent;
}

void TreeNode::getValidChildren(int level, TreeNode *base){
	if (level == 0){
		return;
	}
	df::LogManager::getInstance().writeLog("here4\n");
	MapManager &mm = MapManager::getInstance();
	df::Position posUp = df::Position(base->getPosition().getX(), base->getPosition().getY() - 1);
	df::Position posDown = df::Position(base->getPosition().getX(), base->getPosition().getY() + 1);
	df::Position posLeft = df::Position(base->getPosition().getX() - 1, base->getPosition().getY());
	df::Position posRight = df::Position(base->getPosition().getX() + 1, base->getPosition().getY());
	
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

	level--;

	for (int i = 0; i < base->getChildrenCount(); i++){
		getValidChildren(level, (base->getChildren()[i]));
	}
}

#include <iostream>
using std::printf;
void TreeNode::printTree(TreeNode *base){
	printf("x:%d, y:%d - \n", base->getPosition().getX(), base->getPosition().getY());
	for (int i = 0; i < base->getChildrenCount(); i++){
		printTree(base->getChildren()[i]);
	}
}

df::Position* TreeNode::pathToPosition(TreeNode *base, df::Position posTo, int *size, int nLevel){
	getValidChildren(nLevel, base);
	TreeNode *lowest = TreeNode::findLowestTreeNode(base, posTo);
	
	std::printf("x: %d, y: %d\n", lowest->getPosition().getX(), lowest->getPosition().getY());
	(*size) = lowest->getLevel();
	df::Position *path = new df::Position[(*size)];
	for (int i = (*size); i >= 0; i--){
		path[i] = lowest->getPosition();
		lowest = lowest->getParent();
	}
	return path;
}

TreeNode * TreeNode::findLowestTreeNode(TreeNode *base, df::Position pos){
	if (base->getPosition().equalTo(pos)){
		return base;
	}
	if (base->getChildrenCount() == 0){
		return base;
	}

	TreeNode *lowestNode = new TreeNode(df::Position(-1000,1000), base, 1000);;
	for (int i = 0; i < base->getChildrenCount(); i++){
		TreeNode *possible = findLowestTreeNode(base->getChildren()[i], pos);
		if (possible->getPosition().getManhattanDistance(pos) * possible->getLevel() < lowestNode->getPosition().getManhattanDistance(pos) * lowestNode->getLevel()){
			lowestNode = possible;
		}
	}

	return lowestNode;
}