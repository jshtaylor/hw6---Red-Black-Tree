#include "RedBlackTree.h"
#include <string>

using namespace std;

RedBlackTree:: RedBlackTree(){
    
} //main constructor
RedBlackTree:: RedBlackTree(const RedBlackTree&){

} //should be the copy constructor


void RedBlackTree:: Insert(int val){
    if(!Contains(val)){ // checks for duplicates, if dup, end here
        return;
    }

    if (root == nullptr){ // creates a root if the root DNE
        root = new RBTNode();
        root->Data = val;
        root->Color = COLOR_BLACK;
        root ->left = nullptr;
        root -> right = nullptr;
        numItems ++;
        return;
    }

    //here is the evil weird logic that rebalances the whole thing on an insert
    

};

bool RedBlackTree:: Contains(int val){ 
    //doing this recursively would be more elegant but I don't really feel like writing a helper functiom
    //that being the case while loop it is

    RBTNode * curNode = root;

    while(curNode != nullptr){
        if(curNode -> Data == val){
            return true;
        }
        if(val > curNode ->Data){
            curNode = curNode -> right;
        } else{
            curNode = curNode -> left;
        }
    }
    return false;
}

int RedBlackTree:: GetMin(){
    RBTNode * curNode = root;

    while(curNode != nullptr){
        if(curNode -> left != nullptr){
            curNode = curNode -> left;
        }
    }
    return curNode -> Data;
}

int RedBlackTree:: GetMax(){
        RBTNode * curNode = root;

    while(curNode != nullptr){
        if(curNode -> right != nullptr){
            curNode = curNode -> right;
        }
    }
    return curNode -> Data;

}

int RedBlackTree:: Size(){
    return numItems;

};

