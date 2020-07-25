HW7 consists of two main files that can be compiled and run:  
bst-test.cpp  
sat_solver.cpp  

bst.h and avlbst.h  
This program implements a binary search tree and then extends it to build an AVL tree.  
1. For the insert() method, duplicate entries overwrite the current value with the updated value. 
2. There is a data member variable balance_ for the AVLNode in avlbst.h which stores and updates the balance of a given node. It is a char type to save memory because it only needs to represent -2, -1, 0, 1, or 2. 
3. The AVLTree inherits from the BST. 
4. Erasing (removing) a key that has 2 children swaps it with its predecessor. 
5. The AVL implementation maintains the balance of the tree and provides O(log n) runtime for insert, remove, and find. 

sat_solver.cpp  
Revisits my Boolean satisfiability solver which previously implemented a std::map of each variable to its current value (0, 1, or unassigned). Instead, my own AVL tree implementation is used as the map implementation for storing variable values rather than std::map. 

Both can be compiled by entering _make_ at the command line.  

A sample invocation of bst-test would be:  
./bst-test  

A sample invocation of sat_solver would be:  
./sat_solver  

These programs also rely on changes made to:  
bst.h  
avlbst.h   

Please check the comments in the above programs for any clarifications.
