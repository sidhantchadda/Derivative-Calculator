#include <stack>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdexcept>
#include "Token.h"

const int precedence[5][3] = {
	{'^', 4, 0},
	{'*', 3, 1},
	{'/', 3, 1},
	{'+', 2, 1},
	{'-', 2, 1}
};



class Shuntingyard {
public:
	char * _string;
		
	Shuntingyard(char * s) {
		_string = strdup(s);
	}
	
	~Shuntingyard() {
		delete _string;
	}
	int calculatePrecedence(Token t) {
		char c = t._op;
		int pres = -1;
		for(int i = 0; i<5; i++) {
			if(precedence[i][0] == c) {
				pres = precedence[i][1];
				return pres;
			}
		}
		return pres;	
	}
	void printOut(std::vector<Token> output) {
		int size = output.size();
		printf("Output: ");
		for(int i = 0; i<size; i++) {
			Token t = output.at(i);
			if(t.elementType == operation)
				printf("%c ",t._op);
			else if(t.elementType == identifier) {
				printf("%c ",t._id);
			}
			else
				printf("%d ",t._num);
		}
		printf("\n");
	}
	void stdprint(std::stack<Token> stack) {	
		if(stack.empty()) {
			return;
		}
		Token t = stack.top();
		stack.pop();
		stdprint(stack);
		stack.push(t);
		//printf("%c ",t._op);
	}
	void printStack(std::stack<Token> stack) {
		//printf("Stack: ");
		stdprint(stack);
		//printf("\n");
	}
	std::vector<Token> infixToPostfix() {
		//TODO 1
		std::vector<Token> output;
		std::stack<Token> stack;
		int	size = strlen(_string);
		for(int i = 0; i<size; i++) {
			//is only running once for 3+4
			char c = _string[i];
			if(c == ' ')
				continue;
			//printf("c is: %c\n",c);
			//printOut(output);
			printStack(stack);
			if(isdigit(c)) {
				int x = i+1;
				if(x < size) {
					char p = _string[x];
					while(isdigit(p)) {	
						if(x >= size)
							break;
						x++;
						p = _string[x];
					}
					//substring and add the integeer here
					//also incraese change i to x
					char* start = &_string[i];
					char* end = &_string[x];
					
					char* sub = (char*) calloc(1, end-start+1);
					memcpy(sub, start, end-start);
					int value = atoi(sub);
					free(sub);
					//value is correct
					i = x-1;
					Token t = Token(value);
					output.push_back(t);
				}
				else {		
					int ic = c - '0';
					Token t = Token(ic);
					output.push_back(t);
				}
			}
			//is not a digit
			else {
				Token t = Token(c);
				int pres = calculatePrecedence(t);
				if(pres == -1) {
					if(c == '(') {
						stack.push(t);
						continue;
					}
					else if(c == ')') {
						//until the element on top of the stack is a left parenthesis
						while(!stack.empty()) {
							Token t2 = stack.top();
							stack.pop();
							if(t2._op == '(')
								break;
							output.push_back(t2);
							if(stack.empty()) {
								throw std::out_of_range("no matching closing parenthesis");
							}
						}
						continue;
					}
					else {	
						//found a variable
						output.push_back(t);
						continue;
					}
				}
				//assuming c is a valid operator
				if(stack.empty()) {
					stack.push(t);
					continue;
				}
				bool left = true;
				if(pres == 4)
					left = false;
				while(!stack.empty()) {
					Token t2 = stack.top();
					int pres2 = calculatePrecedence(t2);
					//something wrong here fix in morning
					if((left == true && (pres <= pres2)) || (left == false && (pres<pres2))) {
						t2 = stack.top();
						stack.pop();
						output.push_back(t2);			
					}
					else
						break;
				}
				stack.push(t);
			}
		}
		while(!stack.empty()) {
			Token t2 = stack.top();
			stack.pop();
			if(t2._op == '(')
				throw std::out_of_range("mismatch parenthesis");
			output.push_back(t2._op);
		}
		//while loop for remaning items in the stack
		return output;	
		//push_back
	}
};
