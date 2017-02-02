#include "ShuntingYard.h"
#include "ExpressionApplication.h"
#include <stdio.h>
#include <string.h>

void test_io() {
	char buf[1000];
	char * p = buf;
	int c;
	while((c = getchar()) != EOF) {
		*p++ = c;
	}
	*p = 0;
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	printf("Shunting Yard Output:\n");
	for (int j=0;j<v.size();j++){
		v[j].print();
	}
	fflush(stdout);
	ExpressionApplication e(v);
	printf("\nOriginal Tree:\t\t");
	fflush(stdout);
	e._expression -> print();
	printf("Differentiated Tree:\t");
	fflush(stdout);
	BinaryTree * ret = e.differentiate('x');
	ret -> print();
	printf("Simplified Tree:\t");
	fflush(stdout);
	ret = e.simplify();
	ret -> print();
}
void test1(){
	char buf[] = "x^4";
	printf("input: %s\n\n", buf);
    Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
    printf("Differentiated Tree Output:\n");
    ExpressionApplication e(v);
	BinaryTree * ret = e.simplify();
	ret -> print();
    fflush(stdout);
}

void test2() {
	char buf[] = "2x+5x^2+10x^5+15";
	printf("input: %s\n\n", buf);
    Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
    printf("Differentiated Tree Output:\n");
    ExpressionApplication e(v);
	BinaryTree * ret = e.simplify();
	ret -> print();
    fflush(stdout);
}
void test3() {
	char buf[] = "x^3+y^2+x*y+5";
	printf("input: %s\n\n", buf);
    Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
    printf("Differentiated Tree Output:\n");
    ExpressionApplication e(v);
	BinaryTree * ret = e.simplify();
	ret -> print();
    fflush(stdout);
}

void test4() {
	char buf[] = "(y+y^2+y^4)*(x+24+x^2)";
	printf("input: %s\n\n", buf);
    Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
    printf("Differentiated Tree Output:\n");
    ExpressionApplication e(v);
	BinaryTree * ret = e.simplify();
	ret -> print();
    fflush(stdout);
}

void test5() {
	char buf[] = "(x^4+15x^2+32/x+5)/(x^2+32x+25)";
	printf("input: %s\n\n", buf);
    Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
    printf("Differentiated Tree Output:\n");
    ExpressionApplication e(v);
	BinaryTree * ret = e.simplify();
	ret -> print();
    fflush(stdout);
}

void test6() {
      /*
      Test for Building Tree 
      */
	char buf[] = "y*x^4+x^9";
	printf("input: %s\n\n", buf);
    Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
    printf("Differentiated Tree Output:\n");
    ExpressionApplication e(v);
	BinaryTree * ret = e.simplify();
	ret -> print();
    fflush(stdout);
}

void test7() {
	char buf[] = "((((3*(x^2))+(2*(0^1)))+((1*y)+(x*0)))+0)";
	printf("input: %s\n\n", buf);
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	printf("Differentiated Tree Output:\n");
	ExpressionApplication e(v);
	BinaryTree *ret = e.simplify();
	ret -> print();
	fflush(stdout);
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		test_io(); // std io for manual testing
	}
	else {
		if ( !strcmp(argv[1], "test1")) {
			test1();
		}
		if(	 !strcmp(argv[1], "test2")) {
			test2();
		}
		if(	 !strcmp(argv[1], "test3")) {
			test3();
		}
		if(	 !strcmp(argv[1], "test4")) {
			test4();
		}
		if(	 !strcmp(argv[1], "test5")) {
			test5();
		}
		if(	 !strcmp(argv[1], "test6")) {
			test6();
		}
		if(	 !strcmp(argv[1], "test7")) {
			test7();
		}
	}
}
