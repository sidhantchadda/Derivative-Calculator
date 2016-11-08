CFLAGS = -g
COMPILE = g++ $(CFLAGS) -c
LINK = g++ $(CFLAGS)

all: clean test

test: BinaryTree.o ExpressionApplication.o
	$(LINK) BinaryTree.o ExpressionApplication.o test.cpp -o test

BinaryTree.o: BinaryTree.cpp BinaryTree.h
	$(COMPILE) BinaryTree.cpp

ExpressionApplication.o: ExpressionApplication.cpp ExpressionApplication.h
	$(COMPILE) ExpressionApplication.cpp
	
clean:
	rm -f *.o test
