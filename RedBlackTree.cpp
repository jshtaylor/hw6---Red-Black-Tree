#include "RedBlackTree.h"
#include <string>

using namespace std;

RedBlackTree:: RedBlackTree(){
    
} //main constructor
RedBlackTree:: RedBlackTree(const RedBlackTree&){

} //should be the copy constructor


void RedBlackTree:: Insert(int val){
    if (root == nullptr){
        root -> Data = val;
        root -> Color = COLOR_BLACK;
    }
    
};

bool RedBlackTree:: Contains(int val){

};

int RedBlackTree:: GetMin(){

};

int RedBlackTree:: GetMax(){

};

int RedBlackTree:: Size(){

};

