#include "RedBlackTree.h"
#include <string>
#include <iostream>

using namespace std;

RedBlackTree:: RedBlackTree(){
    
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
        
}

    

void RedBlackTree:: InsertFix(RBTNode* node){
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
    return curNode -> data;
}

int RedBlackTree:: Size(){
    return numItems;
};

