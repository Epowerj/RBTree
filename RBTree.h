//Eugene Kramskoi

#ifndef RBTREE_H
#define RBTREE_H

#include "RBNode.h"
#include <iostream>

using namespace std;

class RBTree {
    
private:
    
    RBNode* tree; //pointer to the root node
    
    virtual void destroy_tree(RBNode * fuse);
    
    virtual string rShow(RBNode* start); //recursive show
    virtual RBNode* rsearch(int key, RBNode* leaf); //recursive search
    
    virtual void rb_delete(RBNode* z); //normal delete
    virtual void rb_delete_fixup(RBNode* x); //fixup
    virtual void rb_delete_fixup_sentinel(RBNode* x, bool isright, RBNode* parent, bool isred); //"special cupcake" case fixup
    virtual void rb_transplant(RBNode* u, RBNode* v); //helper function
    
    virtual RBNode* tree_minimum(RBNode* x); //more helpers
    virtual RBNode* tree_maximum(RBNode* x);
    
    virtual RBNode* bbt_insert(int key, RBNode* leaf); //the normal tree insert
    virtual void insert_fixup(RBNode * z); //insert fixup
    
    virtual void leftRotate(RBNode* x);
    virtual void rightRotate(RBNode* x);

public:

    RBTree();
    RBTree(RBTree const & other);
    virtual ~RBTree();
    
    virtual void insert(int value); //launcher function
    virtual void remove(int todelete); //launcher function
    virtual void show(); //just launches rShow
    virtual RBNode* search(int key); //also just launches other functions
    
};

#endif /* RBTREE_H */

