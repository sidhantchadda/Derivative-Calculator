##About
This is a simple derivative that is able to take a mathematical expression and calculate its derivative.
##How it works
First we take a mathematical expression and parse it to Reverse Polish Notation (RPN) using the [Shunting Yard](https://en.wikipedia.org/wiki/Shunting-yard_algorithm) algorithim. Next we take our RPN and convert it to a Binary Expression Tree. This step is needed so our computer can better understand the order of operations of our expression. Now we take the derivative with respect to a varible ontop of the tree. This step can be done by following some of the basic derivative rules. Now we must simplify our tree by performing computations on constant terms and by grouping like terms together. Finally we must convert our Tree back into a mathematical expression that our average human can understand. This is done by using an inorder traversal on our tree.
##Installation
First clone the repo:
```Bash
$ git clone https://github.com/koochi10/Derivative-Calculator.git
$ cd Derivative-Calculator/
```
To compile run:
```Bash
$ make
```

And to run a test:
```Bash
$ ./test [TESTNAME]
```