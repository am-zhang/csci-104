#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void destructorHelper(Node<Key, Value>* n);
    int height(Node<Key, Value>* n) const;
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    bool balanceHelper(Node<Key, Value>* n) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr) :
    current_(ptr)
{
    // TODO
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() :
    current_(NULL)
{
    // TODO
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    current_ = successor(current_);
    return *this;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // added successor helper function
    if(current == NULL)
    {
        return current;
    }
    Node<Key, Value>* temp;
    if(current->getRight() != NULL) // checks if it has a right child
    {
        temp = current->getRight();
        while(temp->getLeft() != NULL)
        {
            temp = temp->getLeft();
        }
    }
    else // tries to find first node that is a left child
    {
        temp = current->getParent();
        while(temp != NULL && current == temp->getRight())
        {
            current = temp;
            temp = temp->getParent();
        }
    }
    return temp;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() :
    root_(NULL)
{
    // TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    destructorHelper(root_);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::destructorHelper(Node<Key, Value>* n)
{
    // added recursive helper function
    if(n == NULL) // base case
    {
        return;
    }
    destructorHelper(n->getLeft());
    destructorHelper(n->getRight());
    delete n;
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    if(root_ == NULL) // if tree is empty
    {
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        return;
    }

    Node<Key, Value>* curr = root_;
    Key k = keyValuePair.first;
    while(curr != NULL) // loops until it finds correct place
    {
        if(k == curr->getKey()) // overwrites current value
        {
            curr->setValue(keyValuePair.second);
            return;
        }
        else if(k < curr->getKey()) // if key is less than current key
        {
            if(curr->getLeft() == NULL)
            {
                Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, curr);
                curr->setLeft(temp);
                return;
            }
            curr = curr->getLeft();
        }
        else if(k > curr->getKey()) // if key is greater than greater key
        {
            if(curr->getRight() == NULL)
            {
                Node<Key, Value>* temp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, curr);
                curr->setRight(temp);
                return;
            }
            curr = curr->getRight();
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* temp = internalFind(key);
    if(temp == NULL) // key doesn't exist in the tree
    {
        return;
    }

    if(temp->getLeft() != NULL && temp->getRight() != NULL) // 2 children
    {
        Node<Key, Value>* previous = predecessor(temp);
        nodeSwap(temp, previous);
    }

    bool isRoot = false;
    bool isLeft = false;
    bool isRight = false;
    if(temp->getParent() == NULL) // checks if removing root
    {
        isRoot = true;
    }
    else if(temp == temp->getParent()->getRight()) // checks if removing a right child
    {
        isRight = true;
    }
    else if(temp == temp->getParent()->getLeft()) // checks if removing a left child
    {
        isLeft = true;
    }

    if(temp->getLeft() == NULL && temp->getRight() == NULL) // 0 children
    {
        if(isRoot) // checks if deleting only root
        {
            delete temp;
            temp = NULL;
            root_ = NULL;
            return;
        }
        if(isRight)
        {
            temp->getParent()->setRight(NULL);
        }
        else if(isLeft)
        {
            temp->getParent()->setLeft(NULL);
        }
        delete temp;
        temp = NULL;
    }
    else if(temp->getLeft() != NULL) // 1 child on the left
    {
        Node<Key, Value>* left = temp->getLeft();
        if(!isRoot)
        {
            if(isRight)
            {
                temp->getParent()->setRight(left);
            }
            else if(isLeft)
            {
                temp->getParent()->setLeft(left);
            }
        }
        else
        {
            root_ = left;
        }
        left->setParent(temp->getParent());
        delete temp;
        temp = NULL;
    }
    else if(temp->getRight() != NULL) // 1 child on the right
    {
        Node<Key, Value>* right = temp->getRight();
        if(!isRoot)
        {
            if(isRight)
            {
                temp->getParent()->setRight(right);
            }
            else if(isLeft)
            {
                temp->getParent()->setLeft(right);
            }
        }
        else
        {
            root_ = right;
        }
        right->setParent(temp->getParent());
        delete temp;
        temp = NULL;
    }
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if(current == NULL)
    {
        return current;
    }
    Node<Key, Value>* temp;
    if(current->getLeft() != NULL) // checks if it has a left child
    {
        temp = current->getLeft();
        while(temp->getRight() != NULL)
        {
            temp = temp->getRight();
        }
    }
    else // tries to find first node that is a right child
    {
        temp = current->getParent();
        while(temp != NULL && current == temp->getLeft())
        {
            current = temp;
            temp = temp->getParent();
        }
    }
    return temp;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    destructorHelper(root_);
    root_ = NULL;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* temp = root_;
    if(root_ == NULL)
    {
        return NULL;
    }
    while(temp->getLeft() != NULL)
    {
        temp = temp->getLeft();
    }
    return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    if(root_ == NULL) // if tree is empty
    {
        return NULL;
    }

    Node<Key, Value>* curr = root_;
    while(curr != NULL)
    {
        if(key == curr->getKey()) // node is found
        {
            return curr;
        }
        else if(key < curr->getKey())
        {
            if(curr->getLeft() == NULL) // if the key isn't found, return
            {
                return NULL;
            }
            curr = curr->getLeft();
        }
        else if(key > curr->getKey())
        {
            if(curr->getRight() == NULL) // if the key isn't found, return
            {
                return NULL;
            }
            curr = curr->getRight();
        }
    }
    return curr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    if(root_ == NULL) // empty case
    {
        return true;
    }
	return balanceHelper(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balanceHelper(Node<Key, Value>* n) const
{
    // added recursive helper function to determine if balanced
    int left = 0;
    if(n->getLeft() != NULL)
    {
        left = height(n->getLeft()); 
    }

	int right = 0;
    if(n->getRight() != NULL)
    {
        right = height(n->getRight());
    }

	if(abs(left - right) > 1) // determines if this node is balanced
	{
		return false;
	}
    
	bool lsub = true;
	bool rsub = true;
	if (n->getLeft() != NULL) // checks balance of subtrees
	{
		lsub = balanceHelper(n->getLeft());
	}
	if (n->getRight() != NULL)
	{
		rsub = balanceHelper(n->getRight());
	}
	return (lsub && rsub); // returns true if all nodes are balanced
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(Node<Key, Value>* n) const
{
    // added recursive helper function to determine height
    if (n == NULL)
	{
		return 0;
	}

    int lheight = 0;
    if(n->getLeft() != NULL)
    {
        lheight = height(n->getLeft()); // gets height of left subtree
    }

    int rheight = 0;
    if(n->getRight() != NULL)
    {
        rheight = height(n->getRight()); // gets height of right subtree
    }
    
    if(lheight > rheight) // gets taller subtree
    {
        return 1 + lheight;
    }
    else
    {
        return 1 + rheight;
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
