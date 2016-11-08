#include "BinaryTree.h"
#include <vector>
#include <stdio.h>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

class ExpressionApplication {
public:
	BinaryTree * _expression;
	
	ExpressionApplication(vector<Token> &v);
	~ExpressionApplication();
	BinaryTree * differentiate(char c);
	TreeNode* differentiate(bool isPowerOp, char target);
	BinaryTree * simplify();
	BinaryTree * buildExpressionTree(vector<Token> &v);
	void sim(TreeNode* node, BinaryTree* tree);
	void diff(TreeNode* node, char target, BinaryTree* tree);
};
