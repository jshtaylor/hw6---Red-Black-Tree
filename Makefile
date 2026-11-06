all:
	g++ -g -Wall -O3 RedBlackTreeTests.cpp RedBlackTree.cpp -o RBTest
clean:
	-rm -f firsttest RBTest
first:
	g++ -g -Wall -O3 RedBlackTreeTestsFirstStep.cpp RedBlackTree.cpp -o firsttest

