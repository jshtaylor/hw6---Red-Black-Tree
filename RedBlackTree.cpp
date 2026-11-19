#include "RedBlackTree.h"
#include <string>
#include <iostream>

using namespace std;

RedBlackTree:: RedBlackTree(){//empty constructor
    root = nullptr;
}
RedBlackTree:: RedBlackTree(int val){ // works with a root
    root = new RBTNode();
    root->data = val;
    root->color = COLOR_BLACK;
    root ->left = nullptr;
    root -> right = nullptr;
    root -> parent = nullptr;
    numItems ++;
}

RedBlackTree:: RedBlackTree(const RedBlackTree& rbtSource){//should be the copy constructor
    numItems = rbtSource.numItems;

    if(rbtSource.root == nullptr){
        return;
    }

    root = CopySubTree(rbtSource.root, NULL);
} 

RBTNode* RedBlackTree:: CopySubTree(RBTNode const * node, RBTNode * parent){
    if(node == nullptr){
        return nullptr;
    }

    RBTNode * newNode = new RBTNode();
    newNode -> color = node -> color;
    newNode -> parent = node -> parent;
    newNode -> data = node -> data;

    newNode -> left = CopySubTree(node -> left, newNode);
    newNode -> right = CopySubTree(node -> right, newNode);

    return newNode;
}

RedBlackTree:: ~RedBlackTree(){ // destructor
}

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

    RBTNode * uncle = GetUncle(node); // grab all of the familial relations here just in case they are needed later. They are
    RBTNode* parent = node->parent;
    RBTNode* grandparent = parent->parent;

    if ( uncle == nullptr || uncle -> color == COLOR_BLACK){ 
        // this is the case in which we need to start rotating things
        //this part needs implementation
        //Left Side - both LL & LR
        if(parent == grandparent -> left){
            //LR case, double rotation, this first since its a conditional double rotationa and doing this than following it is better
            if(node == parent -> right){
                RotateLeft(parent);
                RBTNode * temp = parent;
                parent = node; // shifts points to match the new LL sturcture
                node = temp;

            }
            //LL case single rotation
            parent -> color = COLOR_BLACK;
            grandparent -> color = COLOR_RED;
            RotateRight(grandparent);
        } else { //right side case - RL and RR
            //RL case - Double rotation, this first since its a conditional double rotationa and doing this than following it is better
            if(node == parent -> left){
                RotateRight(parent);
                RBTNode * temp = parent;
                parent = node; // shifts points to match the new RR sturcture
                node = temp;

            }
            //RR case - single rotation
            parent -> color = COLOR_BLACK;
            grandparent -> color = COLOR_RED;
            RotateLeft(grandparent);
        }
    }
    else
    { // case when uncle is red, turn parent and uncle black and iterate up the tree
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

void RedBlackTree:: Remove(int val){
    //starts by getting the node we're removing
    RBTNode * D = root; // node we are deleted
     //find the node from the root
    while(D != nullptr && D -> data != val){
        if(val > D -> data){
            D = D -> right;
        } else{
            D = D -> left;
        }
     }
     if(D == nullptr){
         throw invalid_argument("Input value does not exist in the RBT\n"); 
    }
// 1. Two-child case: swap data with IOS and recursively remove IOS
    if (D->right != nullptr && D->left != nullptr) {
        RBTNode* IOS = GetIOS(D);
        int num = IOS->data;
        Remove(IOS->data);
        D->data = num;
        return;
    }

    // 2. Save D's color and parent BEFORE deleting D
    int dColor = D->color;
    RBTNode * parent = D -> parent;
    RBTNode* R = RemoveReplace(D); // D is deleted inside here

    // 3. Always run RemoveCheck (even if R is nullptr)
    RemoveCheck(dColor, R, parent);
}

RBTNode * RedBlackTree:: RemoveReplace(RBTNode * D){
    RBTNode * parent = D -> parent;
    RBTNode* R = (D->left != nullptr) ? D->left : D->right; // this should grab the child, regardless of direction
    
    if(R != nullptr){
        R -> parent = parent;
    }
    if(parent == nullptr){
        root = R;
    }else if(D == parent -> left){
        parent -> left = R;
    } else{
        parent -> right = R;
    }
    delete D;
    return R;
}


RBTNode * RedBlackTree:: GetIOS(RBTNode * cur){
    RBTNode * IOS = cur -> right;
         while(IOS -> left != nullptr){
             IOS = IOS -> left;
        }
        return IOS;
}

void RedBlackTree:: RemoveCheck(short DColor, RBTNode * R, RBTNode * parent){
    //brief check to see if need to deal with double blacks
    //I hope no double blacks
    if(R == root){
        if(R != nullptr){
        R -> color = COLOR_BLACK;
        }
        return;
    }
    if( DColor == COLOR_RED){
        return;
    }
    if( R != nullptr && R -> color == COLOR_RED){
        R -> color = COLOR_BLACK;
        return;
    }
    if(R != nullptr){
        R -> color = COLOR_DOUBLE_BLACK;
    }
    FixDoubleBlack(R, parent);
}

void RedBlackTree:: FixDoubleBlack(RBTNode * cur, RBTNode * parent){
   // 1. Base case: Reached root
    if (parent == nullptr || cur == root) {
        if (cur != nullptr) {
            cur->color = COLOR_BLACK;
        }
        return;
    }

    // 2. Identify side and sibling
    bool isLeft = (cur == parent->left); // lil helper function
    RBTNode* sibling = isLeft ? parent->right : parent->left;

    // Helper lambdas for null-safe color checks
    auto isBlack = [](RBTNode* n) { return n == nullptr || n->color == COLOR_BLACK; };

    if (sibling == nullptr) {
        if (cur != nullptr) {
            cur->color = COLOR_BLACK; // Clear double-black on cur before moving up
        }
        if (parent->color == COLOR_RED) {
            parent->color = COLOR_BLACK;
        } else {
            parent->color = COLOR_DOUBLE_BLACK;
            FixDoubleBlack(parent, parent->parent);
        }
        return;
    }

    // Case 1: Sibling is RED
    if (sibling->color == COLOR_RED) {
        sibling->color = COLOR_BLACK;
        parent->color = COLOR_RED;
        if (isLeft) {               // Fixed: rotate TOWARD cur
            RotateLeft(parent);
            sibling = parent->right;
        } else {
            RotateRight(parent);
            sibling = parent->left;
        }
    }

    // Case 2: Sibling is BLACK and both children are BLACK (or nullptr)
    if (isBlack(sibling->left) && isBlack(sibling->right)) { // Fixed: null-safe
        sibling->color = COLOR_RED;
        if (cur != nullptr) {
            cur->color = COLOR_BLACK;
        }
        if (parent->color == COLOR_RED) {
            parent->color = COLOR_BLACK;
        } else if (parent != root) {
            parent->color = COLOR_DOUBLE_BLACK;
            FixDoubleBlack(parent, parent->parent);
        }
        return;
    }

    // Case 3 & 4: Sibling is BLACK and at least one child is RED
    if (isLeft) {
        // Case 3: Near child (left) is RED, far child (right) is BLACK
        if (isBlack(sibling->right)) { // Fixed: null-safe
            if (sibling->left != nullptr) {
                sibling->left->color = COLOR_BLACK;
            }
            sibling->color = COLOR_RED;
            RotateRight(sibling);
            sibling = parent->right;
        }

        // Case 4: Far child (right) is RED
        sibling->color = parent->color;
        parent->color = COLOR_BLACK;
        if (sibling->right != nullptr) {
            sibling->right->color = COLOR_BLACK;
        }
        if (cur != nullptr) {
            cur->color = COLOR_BLACK;
        }
        RotateLeft(parent);
    } else {
        // Case 3 Mirror: Near child (right) is RED, far child (left) is BLACK
        //mirror means cur is right child
        if (isBlack(sibling->left)) { // Fixed: null-safe
            if (sibling->right != nullptr) {
                sibling->right->color = COLOR_BLACK;
            }
            sibling->color = COLOR_RED;
            RotateLeft(sibling);
            sibling = parent->left;
        }

        // Case 4 Mirror: Far child (left) is RED
        //mirror case means cur is right child
        sibling->color = parent->color;
        parent->color = COLOR_BLACK;
        if (sibling->left != nullptr) {
            sibling->left->color = COLOR_BLACK;
        }
        if (cur != nullptr) {
            cur->color = COLOR_BLACK;
        }
        RotateRight(parent);
    }
}

// void RedBlackTree:: Remove(int val){ // I don't like how this works
//     RBTNode * curNode = root;
//     //find the node from the root
//     while(curNode != nullptr && curNode -> data != val){
//         if(val > curNode -> data){
//             curNode = curNode -> right;
//         } else{
//             curNode = curNode -> left;
//         }
//     }
//     if(curNode == nullptr){
//         throw invalid_argument("Input value does not exist in the RBT\n"); 
//     }
//     //atp will need to keep track of the color of the node and if the node is red we can delete w/o needing to fix anything
//     //if the delted node is black we need to use a fix function

//     if(curNode -> left != nullptr && curNode -> right != nullptr){
//         //two child case, this is the one where we need to find the IOS and than do that whole thing
//         RBTNode * IOS = curNode -> right;
//         while(IOS -> left != nullptr){
//             IOS = IOS -> left;
//         }
//         curNode -> data = IOS -> data; // copy ios data
//         curNode = IOS; // we'll need to call remove on the IOS at a later point, probably
//     }
//     short deletedColor = curNode -> color;
//     RBTNode * parent = curNode -> parent;
//     RBTNode* child = (curNode->left != nullptr) ? curNode->left : curNode->right; // this is some bullshits

//     if(child != nullptr){
//         child -> parent = curNode -> parent;
//     }
//     if(curNode -> parent == nullptr){
//         root = child; // this is the case when we're removing the root of the tree
//     }else if(curNode == curNode -> parent -> left){
//         parent -> left = child;
//     }else{
//         parent -> right = child;
//     }
//     delete curNode; // kill the node
//     //if the deleted node was red we don't needa do shit
//     if(deletedColor == COLOR_BLACK){
//         RemoveFix(child, parent);
//     }
// }

// void RedBlackTree:: RemoveFix(RBTNode * cur, RBTNode * parent){
//     if(cur == root){
//         if(cur != nullptr){
//             cur -> color = COLOR_BLACK;
//         }
//         return;
//     }
//     if( cur != nullptr && cur -> color == COLOR_RED){
//         cur->color = COLOR_BLACK;
//         return;
//     }
//     FixDoubleBlack(cur, parent);
// }

// void RedBlackTree:: FixDoubleBlack(RBTNode * cur, RBTNode * parent){
//     //TODO
//     RBTNode * sibling;
//     if(parent -> left == cur){
//         sibling = parent -> right;
//     }else{
//         sibling = parent -> left;
//     } 

//     if(sibling -> color == COLOR_RED){
//         //this should be the fix for a red sibling
//         //rotates it so that we end up in a black sibling situation and than we go to the black
//         //sibling situation
//         parent -> color = COLOR_RED;
//         sibling -> color = COLOR_BLACK;
//         if(parent -> left = sibling){
//             RotateRight(parent);
//         } else{RotateLeft(parent);}
//         parent = cur -> parent;
//         FixDoubleBlack(cur, parent);
//     }
//     //red sibling case

// }


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
    if(root == nullptr){
        throw runtime_error(" GetMin Called on empty tree");
    }
    RBTNode * curNode = root;
    while(curNode -> left != nullptr){
        if(curNode -> left != nullptr){
            curNode = curNode -> left;
        }
    }

    return curNode -> data;
}

int RedBlackTree:: GetMax(){
    //max will always be right most since its a BST, again no recursion b/c I dont wanna write a helper functions
    if(root == nullptr){
        throw runtime_error(" GetMax Called on empty tree");
    }    
    RBTNode * curNode = root;
    while(curNode -> right != nullptr){
        if(curNode -> right != nullptr){
            curNode = curNode -> right;
        }
    }

    return curNode -> data;
}

unsigned long long int RedBlackTree:: Size(){
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
        string colorChar = (node->color == COLOR_BLACK) ? "B" : "R";
        string currentStr = " " + colorChar + to_string(node->data) + " ";

        // Combine in Left-Right-Root order
        return leftStr + rightStr + currentStr;
    }

    string RedBlackTree:: ToPrefixString(RBTNode * node) const{
        if (node == nullptr) {
        return "";
        }

        // 1. Process current node data
        string colorChar = (node->color == COLOR_BLACK) ? "B" : "R";
        string currentStr = " " + colorChar + to_string(node->data) + " ";

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
        string colorChar = (node->color == COLOR_BLACK) ? "B" : "R";
        string currentStr = " " + colorChar + to_string(node->data) + " ";

        // 3. Process right subtree
        string rightStr = ToInfixString(node->right);

        // Combine in Left-Root-Right order
        return leftStr + currentStr + rightStr;
    }