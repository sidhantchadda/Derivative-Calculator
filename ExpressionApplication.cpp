#include "ExpressionApplication.h"
#include "ShuntingYard.h"
#include <stack>
#include <stdio.h>
using namespace std;

BinaryTree *
ExpressionApplication::buildExpressionTree(vector<Token> &v) {
	//TODO 3
	delete _expression;
	_expression = new BinaryTree();
	stack<TreeNode*> stack;
	for(int i = 0; i<v.size(); i++) {
		Token t = v.at(i);
		if(t.elementType == integer || t.elementType == identifier) {
			TreeNode *node = new TreeNode(t);
			stack.push(node);
		}
		//is operator
		else {
			TreeNode* child1 = stack.top();
			stack.pop();
			if(stack.empty())
				printf("error found empty stack too soon\n");
			TreeNode* child2 = stack.top();
			stack.pop();

			TreeNode* parent = new TreeNode(t);
			parent -> _left = child2;
			parent -> _right = child1;

			child1 -> _parent = parent;
			child2 -> _parent = parent;

			stack.push(parent);
		}

	}
	TreeNode* root1 = stack.top();
	stack.pop();
	_expression -> _root = root1;
	return _expression;
	//make sure stack is empty if its not empty there is a problem	
}

ExpressionApplication::ExpressionApplication(vector<Token> &v) {
	_expression = NULL;
	buildExpressionTree(v);
}

ExpressionApplication::~ExpressionApplication() {
	//TODO 2

	delete _expression;
	_expression = NULL;
}
BinaryTree*
ExpressionApplication::differentiate(char target) {
	//start at root node
	TreeNode* copyN = _expression -> _root -> duplicate(NULL);
	BinaryTree* copy = new BinaryTree();
	copy -> _root = copyN;

	diff(copy -> _root, target, copy);
	return copy;
}
void
ExpressionApplication::diff(TreeNode* node, char target, BinaryTree* tree) {
	if(node == NULL)
		return;
	//base case is if the node is a leaf node
	if(node ->isLeaf()) {
		if(node -> t -> elementType == identifier) {
			//is variable
			if(node -> t -> _id == target) {
				//change x to 1
				node -> t -> elementType = integer;
				node -> t -> _num = 1;
			}
			else {
				//is a variable that is not x change to 0
				node -> t -> elementType = integer;
				node -> t -> _num = 0;
			}
		}
		else {	
			node -> t -> _num = 0;
		}
	}
	if(node -> _left != NULL && node -> _right != NULL)	{
		if(node -> _left -> isLeaf() && node -> _right -> isLeaf()) {
			//node is an operator
			if(node -> _left -> t -> elementType ==  identifier) {
				if(node -> t -> _op == '^') {
					if(node -> _left -> t -> _id == target) {
						TreeNode* x = node -> _left;
						TreeNode* n = node -> _right;

						node -> t -> _op = '*';
						node -> _left = n;
						n -> _parent = node;

						Token carT = Token('^');
						TreeNode* carrot = new TreeNode(carT);
						carrot -> _parent = node;
						node -> _right = carrot;

						carrot -> _left = x;
						x -> _parent = carrot;

						Token minusT = Token('-');
						TreeNode* minus = new TreeNode(minusT);
						carrot -> _right = minus;
						minus -> _parent = carrot;

						TreeNode* nc = n -> duplicate(minus);
						minus -> _left = nc;

						Token n1T = Token(1);
						TreeNode* n1 = new TreeNode(n1T);
						minus -> _right = n1;
						n1 -> _parent = minus;
						//should this return statement be here
						return;
					}
				}

			}
		}
	}
	if(!node -> isLeaf()) {
		//node is an operator
		if(node -> t -> _op == '+') {
			diff(node -> _left, target, tree);
			diff(node -> _right, target, tree);
		}
		else if(node -> t -> _op == '-') {
			diff(node -> _left, target, tree);
			diff(node -> _right, target, tree);
		}
		else if(node -> t -> _op == '^') {
			tree -> deleteNode(node -> _left);
			tree -> deleteNode(node -> _right);
			node -> _left = NULL;
			node -> _right = NULL;
			node -> t -> elementType = integer;
			node -> t -> _num = 0;
		}
		else if(node -> t -> _op == '*') {
			//change operator to +
			node -> t -> _op = '+';
			TreeNode* f = node -> _left;
			TreeNode* g = node -> _right;

			Token t = Token('*');
			TreeNode* mul1 = new TreeNode(t);
			TreeNode* mul2 = new TreeNode(t);

			node -> _left = mul1;
			node -> _right = mul2;

			mul1 -> _parent = node;
			mul2 -> _parent = node;

			TreeNode* fp = f -> duplicate(mul2);
			diff(fp, target, tree);
			TreeNode* gp = g -> duplicate(mul1);
			diff(gp, target, tree);

			f -> _parent = mul1;
			g -> _parent = mul2;

			mul1 -> _left = f;
			mul1 -> _right = gp;

			mul2 -> _left = fp;
			mul2 -> _right = g;
		}
		else if(node -> t -> _op == '/') {
			TreeNode* f = node -> _left;
			TreeNode* g = node -> _right;

			Token minusT = Token('-');
			TreeNode* minus = new TreeNode(minusT);
			node -> _left = minus;
			minus -> _parent = node;

			Token mulT = Token('*');
			TreeNode* mul1 = new TreeNode(mulT);
			TreeNode* mul2 = new TreeNode(mulT);

			minus -> _left = mul1;
			minus -> _right = mul2;
			mul1 -> _parent = minus;
			mul2 -> _parent = minus;

			TreeNode* fp = f -> duplicate(mul1);
			diff(fp, target, tree);
			mul1 -> _left = fp;

			g -> _parent = mul1;
			mul1 -> _right = g;

			TreeNode* gp = g -> duplicate(mul2);
			diff(gp, target, tree);
			mul2 -> _left = gp;
			gp -> _parent = mul2;

			f -> _parent = mul2;
			mul2 -> _right = f;

			Token carT = Token('^');
			TreeNode* carrot = new TreeNode(carT);
			node -> _right = carrot;
			carrot -> _parent = node;

			TreeNode* g2 = g -> duplicate(carrot);
			carrot -> _left = g2;

			Token t2 = Token(2);
			TreeNode* n2 = new TreeNode(t2);

			n2 -> _parent = carrot;
			carrot -> _right = n2;
		}
	}

}

TreeNode * differentiate(bool isPowerOp, char target) {
	//TODO 5
	return NULL;
}

BinaryTree *
ExpressionApplication::simplify() {
	//TODO 4
	//both children need to be leaf nodes in order to simplifiy
	//perform postOrder traversal.
	TreeNode* copyN = _expression -> _root -> duplicate(NULL);
	BinaryTree* copy = new BinaryTree();
	copy -> _root = copyN;
	diff(copy ->_root, 'x', copy);
	sim(copy ->_root, copy);
	return copy;
}

void
ExpressionApplication::sim(TreeNode* node, BinaryTree* tree) {
	if(node == NULL)
		return;
	sim(node -> _left, tree);
	sim(node -> _right, tree);
	//perform computation
	if(!node -> isLeaf()) {
		//make sure both its children are leaf nodes
		TreeNode* left = node -> _left;
		TreeNode* right = node -> _right;
		if(left->isLeaf() && right->isLeaf()) {
			//perform simplification
			if(left -> t -> elementType == integer && right -> t -> elementType == integer) {
				//easy simplification no rules needed
				char c = node -> t -> _op;
				int value = 0;
				if(c == '+') {
					value = left -> t -> _num + right -> t -> _num;	
				}
				else if(c == '-') {
					value = left -> t -> _num - right -> t -> _num;	
				}
				else if(c == '*') {
					value = left -> t -> _num * right -> t -> _num;	
				}
				else if(c == '/') {
					value = left -> t -> _num / right -> t -> _num;	
				}
				else if(c == '^') {
					value = left -> t -> _num;
					int temp = value;
					int exp = right -> t -> _num;
					if(exp == 0) {
						value = 1;
					}
					else {	
						for(int i = 0; i< exp; i++) {
							value = value * temp;
						}
					}
				}
				else {
					printf("issue has occured interally\n");
				}
				tree -> deleteNode(left);
				tree -> deleteNode(right);
				node -> _left = NULL;
				left = NULL;
				node -> _right = NULL;
				right = NULL;
				node -> t -> elementType = integer;
				node -> t -> _num = value;
				return;
			}
			if(left ->t ->elementType == identifier && right -> t ->elementType == identifier) {
				if(node -> t -> _op == '+') {
					if(right -> t -> _id == left -> t ->_id) {
						node -> t -> _op = '*';
						left -> t -> elementType = integer;
						left -> t -> _num = 2;
					}
				}
					
			}
		}
		//node is an operator
		//complete left side
		if(left -> t -> elementType != operation) {
			if(left -> t -> elementType == integer) {
				//left value is integer
				int val = left -> t -> _num;
				char op = node -> t -> _op;
				if((val == 0 && op == '+') || (val == 1 && op == '*')) {
					//complete step 1
					if(node == tree -> _root) {

						//right should be the new tree
						delete left;
						delete node;
						right -> _parent = NULL;
						tree -> _root = right;
					}
					else {
						//replace node with right subtree
						delete left;
						TreeNode* parent = node -> _parent;
						if(node -> isRighty()) {
							parent -> _right = NULL;
							delete node;
							parent -> _right = right;
						}
						//is a lefty
						else {
							parent -> _left = NULL;
							delete node;
							parent -> _left = right;
						}
					}
				}
				if(val == 0 && op == '*') {
					if(node == tree -> _root) {
						tree -> _root = left;
						tree -> deleteNode(right);
						node -> _right = NULL;
						delete node;
						node = NULL;
					}
					else {
						//if node is not the root of the tree
						tree -> deleteNode(right);
						node -> _right = NULL;
						right = NULL;
						TreeNode* parent = node -> _parent;
						if(node -> isRighty()) {
							parent -> _right = left;
						}
						else {
							//is lefty
							parent -> _left = left;
						}
						delete node;
						node = NULL;
					}
				}
				//should this return be here?
				return;
			}
		}
		if(right -> t-> elementType != operation) {
			if(right -> t -> elementType == integer) {
				int val = right -> t -> _num;
				char op = node -> t -> _op;
				if((val == 1 && op == '*') || (val == 0 && op == '+')) {
					//strategy move left to node
					//check case where it is the root node
					if(node == tree -> _root) {	
						delete right;
						delete node;
						left -> _parent = NULL;
						tree -> _root = left;
					}
					else {
						delete right;
						TreeNode* parent = node -> _parent;
						if(node -> isRighty()) {
							parent -> _right = NULL;
							delete node;
							parent -> _right = left;
						}
						else {
							//is lefty
							parent -> _left = NULL;
							delete node;
							parent -> _left = left;
						}
					}
				}
				if(val == 0 && op == '*') {
					//right sub node is 0
					//strategy make node = to right subnode
					if(node == tree -> _root) {
						tree -> _root = right;
						tree -> deleteNode(left);
						left = NULL;
						delete node;
						node = NULL;
					}
					else {
						tree -> deleteNode(left);
						left= NULL;
						node -> _left = NULL;
						TreeNode* parent = node -> _parent;
						if(node -> isRighty()) {
							parent -> _right = right;
							delete node;
							node = NULL;
						}
						else {
							parent -> _left = right;
							delete node;
							node = NULL;
						}
					}
				}
			}
		}
	}
}
