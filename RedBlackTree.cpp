#include "RedBlackTree.h"
#include <string>
#include <iostream>

using namespace std;

RedBlackTree:: RedBlackTree(){
    root = new RBTNode();
        root ->left = nullptr;
        root -> right = nullptr;
        root -> parent = nullptr;
    
} //main constructor
RedBlackTree:: RedBlackTree(const RedBlackTree&){

} //should be the copy constructor


void RedBlackTree:: Insert(int val){
    if(Contains(val)){ // checks for duplicates, if dup, end here
        throw invalid_argument("No duplicate values");
    }

    if (root == nullptr){ // creates a root if the root DNE
        root = new RBTNode();
        root->data = val;
        root->color = COLOR_BLACK;
        root ->left = nullptr;
        root -> right = nullptr;
        root -> parent = nullptr;
        numItems ++;
        return;
    }

    //create the new Node
    RBTNode * newNode = new RBTNode();
    newNode -> data = val;
    newNode -> color = COLOR_RED;
    newNode -> left = nullptr;
    newNode -> right = nullptr;
    newNode->parent = nullptr;

    //move through the tree and insert the newNode where is goes in a BST
    RBTNode * curNode  =  root;
    while(curNode != nullptr){
        if(val > curNode -> data){
            if(curNode -> right == nullptr){
                curNode -> right = newNode;
                newNode -> parent = curNode;
                break;
            }
            curNode = curNode -> right; 
        } else if(val < curNode -> data){
            if(curNode -> left == nullptr){
                curNode -> left = newNode;
                newNode -> parent = curNode;
                break;
            }
            curNode = curNode -> left;
        }
    }
    numItems++;
    //here is the evil weird logic that rebalances the whole thing on an insert
    //RBT rebalance algoritm here
    InsertFix(newNode);
    

    //no idea how to make this part memory safe
}

void RedBlackTree:: InsertFix(RBTNode* node){
    //recursive function due to nature of bubbling up    
    //this is the weird evil place where the recolor and rotations should be happening
    if(node -> parent == nullptr || node == nullptr){ // this means you're at the root, i.e. base case
        if(node != nullptr){
            node -> color = COLOR_BLACK;
        }
        return;
    }
    if(node -> parent -> color == COLOR_BLACK){ // black parent means wer're chillin, end of process
        //yay yippee hooray we're lucky
        return;
    }
    RBTNode * uncle = GetUncle(node);

    if ( uncle == nullptr || uncle -> color == COLOR_BLACK){ 
        //TODO
        // this is the case in which we need to start rotating things
        //this part needs implementation

    }
    else
    { // case when uncle is red, turn parent and uncle black and iterate up the tree
        RBTNode* parent = node->parent;
        RBTNode* grandparent = parent->parent; 
        
        //set these to black
        parent -> color = COLOR_BLACK;
        uncle -> color = COLOR_BLACK;

        //G parent to red
        if(grandparent != nullptr){
            grandparent -> color = COLOR_RED;

            InsertFix(grandparent);
        }
        
        if(root != nullptr){
            //root must always be black
            root -> color = COLOR_BLACK;
        }
    } 
}

RBTNode* RedBlackTree:: GetUncle(RBTNode * node){ 
    // not yet certain how to make this one memory safe, that may be later or in the destructor not in this function since it returns an RBTnode pointer
    // Guard against nullptr for node, parent, or grandparent
    if (node == nullptr || node->parent == nullptr || node->parent->parent == nullptr) {
        return nullptr;
    }

    RBTNode* parent = node->parent;
    RBTNode* grandparent = parent->parent;

    // If parent is grandparent's left child, uncle is right child
    if (parent == grandparent->left) {
        return grandparent->right;
    } 
    // If parent is grandparent's right child, uncle is left child
    else {
        return grandparent->left;
    }
}

void RedBlackTree:: RotateLeft(RBTNode * node){
    RBTNode * y = node -> right; // couldn't think of a helpful name tbh
    node -> right = y -> left;
    if (y -> left != nullptr){
        y -> left -> parent = node;
    }

    y -> parent = node -> parent; // connect parents so they can swap children/sibilings

    if(node -> parent == nullptr){
        root = y; // new root
    }
    else if(node == node -> parent -> left) {
        node -> parent -> left = y;
    }else {
        node -> parent -> right = y;
    }

    y -> left = node;
    node -> parent = y;
    return; 
}

void RedBlackTree:: RotateRight(RBTNode * node){
    RBTNode * x = node -> left; // again no good variable names
    node -> left = x -> right;

    if(x -> right != nullptr){
        x -> right -> parent = node;
    }

    x -> parent = node -> parent; // link parents

    if(node -> parent == nullptr){
        root = x; // new root
    }
    else if(node == node -> parent -> right){
        node -> parent -> right = x;
    } else{
        node -> parent -> left = x;
    }

    x -> right = node;
    node -> parent = x;
    return;
}

bool RedBlackTree:: Contains(int val){ 
    //doing this recursively would be more elegant but I don't really feel like writing a helper functiom
    //that being the case while loop it is

    RBTNode * curNode = root;

    while(curNode != nullptr){
        if(curNode -> data == val){
            return true;
        }
        if(val > curNode ->data){
            curNode = curNode -> right;
        } else{
            curNode = curNode -> left;
        }
    }
    //delet pointer here
    return false;
}

int RedBlackTree:: GetMin(){
    //min will always be leftmost since its a BST, again no recursion b/c I dont wanna write a helper functions
    RBTNode * curNode = root;
    while(curNode != nullptr){
        if(curNode -> left != nullptr){
            curNode = curNode -> left;
        }
    }
    //delet pointer after assigning the data to an int
    return curNode -> data;
}

int RedBlackTree:: GetMax(){
    //max will always be right most since its a BST, again no recursion b/c I dont wanna write a helper functions
    RBTNode * curNode = root;
    while(curNode != nullptr){
        if(curNode -> right != nullptr){
            curNode = curNode -> right;
        }
    }

    //delet pointer after assigning the data to an int
    return curNode -> data;
}

int RedBlackTree:: Size(){
    return numItems;
};

    string RedBlackTree:: ToPostfixString(RBTNode * node) const{
        // Base case: empty subtree produces empty string
        if (node == nullptr) {
            return "";
        }
        // 1. Process left subtree
        string leftStr = ToPostfixString(node->left);

        // 2. Process right subtree
        string rightStr = ToPostfixString(node->right);

        // 3. Process current node data
        string currentStr = std::to_string(node->data) + " ";

        // Combine in Left-Right-Root order
        return leftStr + rightStr + currentStr;
    }

    string RedBlackTree:: ToPrefixString(RBTNode * node) const{
        if (node == nullptr) {
        return "";
        }

        // 1. Process current node data
        string currentStr = std::to_string(node->data) + " ";

        // 2. Process left subtree
        string leftStr = ToPrefixString(node->left);

        // 3. Process right subtree
        string rightStr = ToPrefixString(node->right);

        // Combine in Root-Left-Right order
        return currentStr + leftStr + rightStr;
    }

    string RedBlackTree:: ToInfixString(RBTNode * node) const{
        if (node == nullptr) {
            return "";
        }

        // 1. Process left subtree
        string leftStr = ToInfixString(node->left);

        // 2. Process current node data
        string currentStr = std::to_string(node->data) + " ";

        // 3. Process right subtree
        string rightStr = ToInfixString(node->right);

        // Combine in Left-Root-Right order
        return leftStr + currentStr + rightStr;
    }

