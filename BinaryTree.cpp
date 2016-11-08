#include "BinaryTree.h"

BinaryTree::BinaryTree() {
	_root = NULL;
}


BinaryTree::~BinaryTree() {
	//use PostOrder traversal to delete this tree
	deleteNode(_root);
	_root = NULL;
}
void 
BinaryTree::deleteNode(TreeNode* node) {
	if(node == _root)
		_root = NULL;
	if(node == NULL)
		return;
	deleteNode(node -> _left);
	deleteNode(node -> _right);
	delete node;
}

void printTree(TreeNode * root) {
	if(root == NULL) return;
	if(root -> t -> elementType == operation) {
		putchar('(');
		fflush(stdout);
	}
	printTree(root -> _left);
	root -> t -> print();
	printTree(root -> _right);
	if(root -> t -> elementType == operation) {
		putchar(')');
		fflush(stdout);
	}
}

void
BinaryTree::print() {
	printTree(_root);
	putchar('\n');
}
bool
TreeNode::isLeaf() {
	if(_left == NULL && _right == NULL)
		return true;
	return false;
}
bool
TreeNode::isRighty() {
	if(_parent -> _right == this)
		return true;
	return false;
}
//this function returns a copy of a tree, requires parent
TreeNode*
TreeNode::duplicate(TreeNode* parent) {
	if(this == NULL)
		return NULL;
	TreeNode* newNode = new TreeNode(*(t));
	newNode -> _left = _left -> duplicate(newNode);
	newNode -> _right = _right -> duplicate(newNode);
	if(parent == NULL)
		newNode -> _parent = NULL;
	else
		newNode -> _parent = parent;
	return newNode;
}
