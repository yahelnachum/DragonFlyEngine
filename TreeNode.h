#ifndef __TREE_NODE_H__
#define __TREE_NODE_H__

#include "Position.h"

class TreeNode{
private:
	int nodeLevel;
	int childrenCount;
	TreeNode **children;
	df::Position pos;
	TreeNode *parent;
public:
	TreeNode();

	TreeNode(df::Position position);

	TreeNode(df::Position position, TreeNode *par, int nLevel);

	void addChild(df::Position position, int nLevel);

	TreeNode** getChildren();

	int getChildrenCount();

	df::Position getPosition();

	int getLevel();

	TreeNode* getParent();
		
	static void getValidChildren(int level, TreeNode *base);

	static void printTree(TreeNode *base);

	static df::Position* pathToPosition(TreeNode *base, df::Position posTo, int *size, int nLevel);

	static TreeNode * TreeNode::findLowestTreeNode(TreeNode *base, df::Position pos);
};
#endif