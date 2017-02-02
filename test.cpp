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
	/*
	Test for Shunting Yard
	*/
	//char buf[] = "x^3+y^2+x*y+5";
	char buf[] = "((((3*(x^2))+(2*(0^1)))+((1*y)+(x*0)))+0)";
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	printf("\nShunting Yard Output:\n");
	for (int j=0;j<v.size();j++){
		v[j].print();
	}
	
	printf("\n\nExpected Output:\n");
	printf("x3^y2^+xy*+5+\n");
}


void test2() {
	char buf[] ="10+43";
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	printf("\nShunting Yard Output:\n");
	for(int j = 0; j<v.size(); j++) {
		v[j].print();
	}
	printf("\n\n Expected Output:\n");
	printf("1043+\n");
}
void test3() {
	char buf[] ="3+4*2/(1-5)^2^3";
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	printf("\nShunting Yard Output:\n");
	for(int j = 0; j<v.size(); j++) {
		v[j].print();
	}
	printf("\n\n Expected Output:\n");
	printf("342*15-23^^/+\n");
}

void test4() {
	char buf[] ="(10+43)*5-42";
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	printf("\nShunting Yard Output:\n");
	for(int j = 0; j<v.size(); j++) {
		v[j].print();
	}
	printf("\n\n Expected Output:\n");
	printf("1043+5*42-\n");
}

void test5() {
	char buf[] ="x^3+y^2+x*y+5";
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	printf("\nShunting Yard Output:\n");
	for(int j = 0; j<v.size(); j++) {
		v[j].print();
	}
	printf("\n\n Expected Output:\n");
	printf("x3^y2^+xy*+5+\n");
}

void test6() {
      /*
      Test for Building Tree 
      */
      char buf[] = "x^3+y^2+x*y+5";
      Shuntingyard s(buf);
      std::vector<Token> v = s.infixToPostfix();
      printf("\nTree Build Output:\n");
      ExpressionApplication e(v);
      e._expression -> print();
      fflush(stdout);
      printf("\nExpected Output:\n");
      printf("((((x^3)+(y^2))+(x*y))+5)\n");
}

void test7() {
	char buf[] = "((((3*(x^2))+(2*(0^1)))+((1*y)+(x*0)))+0)";
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	printf("\nSimplified Tree Output:\n");
	ExpressionApplication e(v);
	BinaryTree *ret = e.simplify();
	ret -> print();
	fflush(stdout);
	printf("\nExpected Output\n");
	printf("((3*(x^2))+y)\n");
}
void test8() {
	char buf[] = "x^3+y^2+x*y+5";
    Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
    printf("\nDifferentiated Tree Output:\n");
    ExpressionApplication e(v);
	BinaryTree * ret = e.simplify();
	ret -> print();
    fflush(stdout);
    printf("\nExpected Output:\n");
    printf("((3*(x^2))+y)\n");
}
void test9() {
	char buf[] = "y*x^4+x^9";
    Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
    printf("\nDifferentiated Tree Output:\n");
    ExpressionApplication e(v);
	BinaryTree * ret = e.simplify();
	ret -> print();
    fflush(stdout);
    printf("\nExpected Output:\n");
    printf("(3*(x^2))\n");


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
		if(	 !strcmp(argv[1], "test8")) {
			test8();	
		}
		if(	 !strcmp(argv[1], "test9")) {
			test9();
		}
	}
}
