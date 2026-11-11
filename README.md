# hw6---Red-Black-Tree

This is/will be full implementation of a Red Black Tree
An RBT is a variant of a binary search tree that self balances in order to maintain O(logN) effieceny, this is done by having colored nodes and rules about how the colored nodes can interact
the header has functions: Contructor, Insert, Contains, GetMin, GetMax, InsertFix, Size, Rotate left/right, get uncle, and copy subtree, as well as the 3 traversal method toStrings

Most of those are pretty self explanitory
Copy Subtree is a helper used in the copy contructor\
InsertFix is how the tree self balances using the helpers get uncle and rotate left/right after the insert method has been called

The tree Uses the RBTNode struct which has the data: data - int value of the node, color - red or black(defined as shorts 0 or 1), left - left child, right - right child, and parent

