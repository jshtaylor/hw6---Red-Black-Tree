#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

using namespace std;

struct RBTNode{


}

class RedBlackTree{
    public:
    RedBlackTree(); //
    RedBlackTree(const RedBlackTree&); //should be the copy constructor
    ~RedBlackTree();

    void TestSimpleConstructor(); //todo this probably needs an input
    void TestInsertFirstNode(); // this probably needs in input
    void insert(int val);
    bool contains(int val);
    int GetMin();
    int GetMax();
    int Size();

    //TODO add the private recursive versions of the two strings
    string ToInfixString() const {return ToInfixString(root);};
    string ToPrefixString() const { return ToPrefixString(root);};
    string ToPostfixString() const { return ToPostfixString(root);};

    private:
    unsigned long long int numItems = 0;
    RBTNode *root = nullptr; //TODO write RBTNode struct 
};

#endif