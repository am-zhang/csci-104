#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    bool isRoot(AVLNode<Key,Value>* n);
    bool isLeft(AVLNode<Key,Value>* n);
    bool isRight(AVLNode<Key,Value>* n);
    void rotateLeft(AVLNode<Key,Value>* n);
    void rotateRight(AVLNode<Key,Value>* n);
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void removeFix(AVLNode<Key,Value>* n, char diff);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    if(this->root_ == NULL) // if tree is empty
    {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        static_cast<AVLNode<Key, Value>*>(this->root_)->setBalance(0);
        return;
    }

    AVLNode<Key, Value>* curr = (AVLNode<Key, Value>*) this->root_;
    Key k = new_item.first;
    while(curr != NULL) // loops until it finds correct place
    {
        if(k == curr->getKey()) // overwrites current value
        {
            curr->setValue(new_item.second);
            return;
        }
        else if(k < curr->getKey()) // if key is less than current key
        {
            if(curr->getLeft() == NULL)
            {
                AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
                curr->setLeft(temp);
                temp->setBalance(0);
                if(temp->getParent()->getBalance() == 1 || temp->getParent()->getBalance() == -1)
                {
                    temp->getParent()->setBalance(0);
                }
                else
                {
                    temp->getParent()->setBalance(-1);
                    insertFix(temp->getParent(), temp);
                }
                return;
            }
            curr = curr->getLeft();
        }
        else if(k > curr->getKey()) // if key is greater than greater key
        {
            if(curr->getRight() == NULL)
            {
                AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
                curr->setRight(temp);
                temp->setBalance(0);
                if(temp->getParent()->getBalance() == 1 || temp->getParent()->getBalance() == -1)
                {
                    temp->getParent()->setBalance(0);
                }
                else
                {
                    temp->getParent()->setBalance(1);
                    insertFix(temp->getParent(), temp);
                }
                return;
            }
            curr = curr->getRight();
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
    if(p == NULL || p->getParent() == NULL)
    {
        return;
    }

    AVLNode<Key,Value>* g = p->getParent();
    if(isLeft(p)) // p is left child
    {
        g->updateBalance(-1);
        if(g->getBalance() == 0)
        {
            return;
        }
        else if(g->getBalance() == -1)
        {
            insertFix(g,p);
        }
        else if(g->getBalance() == -2)
        {
            if(p->getLeft() == n) // zig zig
            {
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            else // zig zag
            {
                rotateLeft(p);
                rotateRight(g);
                if(n->getBalance() == -1)
                {
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 0)
                {
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 1)
                {
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }
    else // p is right child
    {
        g->updateBalance(1);
        if(g->getBalance() == 0)
        {
            return;
        }
        else if(g->getBalance() == 1)
        {
            insertFix(g,p);
        }
        else if(g->getBalance() == 2)
        {
            if(p->getRight() == n) // zig zig
            {
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            else // zig zag
            {
                rotateRight(p);
                rotateLeft(g);
                if(n->getBalance() == 1)
                {
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 0)
                {
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                else if(n->getBalance() == -1)
                {
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }
    
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* temp = (AVLNode<Key, Value>*) BinarySearchTree<Key, Value>::internalFind(key);
    if(temp == NULL) // key doesn't exist in the tree
    {
        return;
    }

    if(temp->getLeft() != NULL && temp->getRight() != NULL) // 2 children
    {
        Node<Key, Value>* n = BinarySearchTree<Key, Value>::predecessor(temp);
        AVLNode<Key, Value>* previous = (AVLNode<Key, Value>*) n;
        this->nodeSwap(temp, previous);
    }

    char diff = 0;
    AVLNode<Key, Value>* parent = temp->getParent();

    if(temp->getLeft() == NULL && temp->getRight() == NULL) // 0 children
    {
        if(isRoot(temp)) // checks if deleting only root
        {
            delete temp;
            temp = NULL;
            this->root_ = NULL;
            return;
        }
        else if(isRight(temp))
        {
            parent->setRight(NULL);
            diff = -1;
        }
        else if(isLeft(temp))
        {
            parent->setLeft(NULL);
            diff = 1;
        }
        delete temp;
        temp = NULL;
        removeFix(parent, diff);
    }
    else if(temp->getLeft() != NULL) // 1 child on the left
    {
        AVLNode<Key, Value>* left = temp->getLeft();
        if(!isRoot(temp))
        {
            if(isRight(temp))
            {
                parent->setRight(left);
                diff = -1;
            }
            else if(isLeft(temp))
            {
                parent->setLeft(left);
                diff = 1;
            }
        }
        else
        {
            this->root_ = left;
        }
        left->setParent(parent);
        delete temp;
        temp = NULL;
        removeFix(parent, diff);
    }
    else if(temp->getRight() != NULL) // 1 child on the right
    {
        AVLNode<Key, Value>* right = temp->getRight();
        if(!isRoot(temp))
        {
            if(isRight(temp))
            {
                parent->setRight(right);
                diff = -1;
            }
            else if(isLeft(temp))
            {
                parent->setLeft(right);
                diff = 1;
            }
        }
        else // changes root
        {
            this->root_ = right;
        }
        right->setParent(parent);
        delete temp;
        temp = NULL;
        removeFix(parent, diff);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, char diff)
{
    if(n == NULL)
    {
        return;
    }
    AVLNode<Key,Value>* p = n->getParent();
    char ndiff = 0;
    if(p != NULL)
    {
        if(isLeft(n))
        {
            ndiff = 1;
        }
        else
        {
            ndiff = -1;
        }
    }
    if(diff == -1)
    {
        if(n->getBalance() + diff == -2)
        {
            AVLNode<Key,Value>* c = n->getLeft();

            if(c->getBalance() == -1) // zig zig
            {
                rotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if(c->getBalance() == 0) // zig zig
            {
                rotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
                return;
            }
            else if(c->getBalance() == 1) // zig zag
            {
                AVLNode<Key,Value>* g = c->getRight();
                rotateLeft(c);
                rotateRight(n);
                if(g->getBalance() == 1)
                {
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                }
                else if(g->getBalance() == 0)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                else if(g->getBalance() == -1)
                {
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        }
        else if(n->getBalance() + diff == -1)
        {
            n->setBalance(-1);
            return;
        }
        else if(n->getBalance() + diff == 0)
        {
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
    else if(diff == 1)
    {
        if(n->getBalance() + diff == 2)
        {
            AVLNode<Key,Value>*c = n->getRight();

            if(c->getBalance() == 1) // zig zig
            {
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            }
            else if(c->getBalance() == 0) // zig zig
            {
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
                return;
            }
            else if(c->getBalance() == -1) // zig zag
            {
                AVLNode<Key,Value>* g = c->getLeft();
                rotateRight(c);
                rotateLeft(n);
                if(g->getBalance() == -1)
                {
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                }
                else if(g->getBalance() == 0)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                else if(g->getBalance() == 1)
                {
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        }
        else if(n->getBalance() + diff == 1)
        {
            n->setBalance(1);
            return;
        }
        else if(n->getBalance() + diff == 0)
        {
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isRoot(AVLNode<Key,Value>* n)
{
    if(n->getParent() == NULL)
    {
        return true;
    }
    return false;
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isLeft(AVLNode<Key,Value>* n)
{
    if(n == n->getParent()->getLeft())
    {
        return true;
    }
    return false;
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isRight(AVLNode<Key,Value>* n)
{
    if(n == n->getParent()->getRight())
    {
        return true;
    }
    return false;
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n)
{
    AVLNode<Key, Value>* child = n->getRight();
    AVLNode<Key, Value>* childLeft = child->getLeft();
    AVLNode<Key, Value>* parent = n->getParent();
    if(isRoot(n)) // if node is root
    {
        this->root_ = child;
        child->setParent(NULL);
    }
    else if (isLeft(n)) // else if node is a left child
    {
        parent->setLeft(child);
        child->setParent(parent);
    }
    else if(isRight(n)) // else if node is a right child
    {
        parent->setRight(child);
        child->setParent(parent);
    }

    child->setLeft(n);
    n->setParent(child);
    if(childLeft != NULL) // if child has a left child
    {
        childLeft->setParent(n);
        n->setRight(childLeft);
    }
    else
    {
        n->setRight(NULL);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* n)
{
    AVLNode<Key, Value>* child = n->getLeft();
    AVLNode<Key, Value>* childRight = child->getRight();
    AVLNode<Key, Value>* parent = n->getParent();
    if(isRoot(n)) // if node is root
    {
        this->root_ = child;
        child->setParent(NULL);
    }
    else if (isRight(n)) // else if node is a right child
    {
        parent->setRight(child);
        child->setParent(parent);
    }
    else if(isLeft(n)) // else if node is a left child
    {
        parent->setLeft(child);
        child->setParent(parent);
    }

    child->setRight(n);
    n->setParent(child);
    if(childRight != NULL) // if child has a right child
    {
        childRight->setParent(n);
        n->setLeft(childRight);
    }
    else
    {
        n->setLeft(NULL);
    }
}

#endif
