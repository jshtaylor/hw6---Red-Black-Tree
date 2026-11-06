#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

using namespace std;

#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_DOUBLE_BLACK 1 // this is used in the remove algorithm, do it later

struct RBTNode{
    //this needs to be implemented before anything else can start tbh
    int data;
    unsigned short color; //idk if this is the correct data type
    RBTNode *left = nullptr; //left child
    RBTNode *right = nullptr; //right child
    RBTNode *parent= nullptr;
};

class RedBlackTree{
    
    public:
    RedBlackTree(); //main constructor
    RedBlackTree(const RedBlackTree&); //should be the copy constructor
    ~RedBlackTree();//since we're using pointers throw this in here

    void Insert(int val);
    bool Contains(int val);
    int GetMin();
    int GetMax();
    int Size();

    RBTNode* GetUncle(RBTNode * node);
    void InsertFix(RBTNode* node);

    //TODO add the private recursive versions of the two strings
    string ToInfixString() const { return ToInfixString(root);};
    string ToPrefixString() const { return ToPrefixString(root);};
    string ToPostfixString() const { return ToPostfixString(root);};

    private:
    unsigned long long int numItems = 0;
    RBTNode *root = nullptr; //TODO write RBTNode struct 

    string ToPostfixString(RBTNode * node) const;
    string ToPrefixString(RBTNode * node) const;
    string ToInfixString(RBTNode * node) const;

    void RotateLeft(RBTNode * node);
    void RotateRight(RBTNode * node);

};

#endif