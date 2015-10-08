#ifndef __TREE_NODE_H__
#define __TREE_NODE_H__

// game engine includes
#include "Position.h"

class TreeNode{
private:
	int nodeLevel;			// level in the tree
	int childrenCount;		// number of children
	TreeNode **children;	// array of children
	df::Position pos;		// position of node
	TreeNode *parent;		// parent of node
public:
	// default constructor
	TreeNode();

	// constructor with position
	TreeNode(df::Position position);
	
	// constructor with position, parent, and level in tree
	TreeNode(df::Position position, TreeNode *par, int nLevel);

	// add child with position, and level in tree
	void addChild(df::Position position, int nLevel);

	// return array of children
	TreeNode** getChildren();

	// return number of children in array
	int getChildrenCount();

	// get position of node
	df::Position getPosition();

	// get level of node
	int getLevel();

	// get parent of node
	TreeNode* getParent();
		
	// get all valid children of node with a depth of level
	static void getValidChildren(int level, TreeNode *base);

	// print tree given
	static void printTree(TreeNode *base);

	// instantiate tree with path to given position to a certain depth
	static df::Position* pathToPosition(TreeNode *base, df::Position posTo, int *size, int nLevel);

	// find the shallowest treenode with the leaf position close to or equal to the given position
	static TreeNode * TreeNode::findLowestTreeNode(TreeNode *base, df::Position pos);
};
#endif