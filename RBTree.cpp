
#include "RBTree.h"
#include "RBNode.h"
#include <iostream>
#include <valarray>

using namespace std;

RBTree::RBTree() {
    tree = 0;
}

RBTree::RBTree(const RBTree& other) {
    //TODO
    //Probably should do a full tree copy, but I don't have the time

    tree = other.tree;
}

RBTree::~RBTree() {
    destroy_tree(tree);
}

//nodes don't actually have a good destructor, so this is important

void RBTree::destroy_tree(RBNode* fuse) {
    if (fuse != 0) {
        destroy_tree(fuse->getLeft());
        destroy_tree(fuse->getRight());
        delete fuse;
    }
}

void RBTree::insert(int value) {
    cout << "Inserting: " << value << endl;
    insert_fixup(bbt_insert(value, tree)); //just launches
}

void RBTree::remove(int todelete) {
    cout << "Deleting: " << todelete << endl;

    RBNode* nodetodelete = search(todelete); //finds what node to delete first

    rb_delete(nodetodelete);
}

void RBTree::show() {
    cout << rShow(tree) << endl; //more launching, whee
}

string RBTree::rShow(RBNode* start) {
    //returns in a format with a ton of brackets
    //12r{{} {}}
    //rootnode{leftchild rightchild}

    if (start == 0) {
        return "";
    } else {

        if (start->isRed()) {
            return to_string(start->getHead()) + "r" +
                    "{" +
                    rShow(start->getLeft()) +
                    "} {" +
                    rShow(start->getRight()) +
                    "}";
        } else {
            return to_string(start->getHead()) + "b" +
                    "{" +
                    rShow(start->getLeft()) +
                    "} {" +
                    rShow(start->getRight()) +
                    "}";
        }
    }
}

RBNode* RBTree::search(int key) {
    return rsearch(key, tree); //don't want to have to type that extra parameter
}

RBNode* RBTree::rsearch(int key, RBNode* leaf) {
    if (leaf != 0) {
        if (key == leaf->getHead())
            return leaf;
        if (key < leaf->getHead())
            return rsearch(key, leaf->getLeft());
        else
            return rsearch(key, leaf->getRight());
    } else return 0;
}

//standard tree insert, more or less

RBNode* RBTree::bbt_insert(int key, RBNode* leaf) {
    if (leaf != 0) { // if we're not inserting to an empty spot

        if (key < leaf->getHead()) {
            if (leaf->getLeft() != 0)
                bbt_insert(key, leaf->getLeft());
            else {
                leaf->setLeft(new RBNode(key, true, 0, 0, leaf));

                //using a constructor instead of this:
                //leaf->left->head = key;
                //leaf->left->left = 0;
                //leaf->left->right = 0;

                return leaf->getLeft();
            }
        } else if (key >= leaf->getHead()) {
            if (leaf->getRight() != 0)
                bbt_insert(key, leaf->getRight());
            else {
                leaf->setRight(new RBNode(key, true, 0, 0, leaf));

                //using a constructor instead of this:
                //leaf->right->head = key;
                //leaf->right->left = 0;
                //leaf->right->right = 0;

                return leaf->getRight();
            }
        }
    } else {
        tree = new RBNode(key, true, 0, 0, 0);
        return tree;
    }

}

void RBTree::insert_fixup(RBNode * z) {

    if (z != tree) { //if z is not the root

        //while z's parent is red and not the root
        //holy crap I hate this. C++ just segfaults if z doesn't have a parent
        while (z != tree && z->getParent()->isRed()) {

            //debug cout << z->head << endl;

            //if parent is a left child
            if (z->getParent() == z->getParent()->getParent()->getLeft()) {

                RBNode* y = z->getParent()->getParent()->getRight(); //y is the uncle

                //if uncle is red and exists
                if (y != 0 && y->isRed()) {

                    //make z's parent black
                    z->getParent()->setRed(false);

                    //make uncle black
                    y->setRed(false);

                    //make z, z's grandparent
                    z = z->getParent()->getParent();

                    //make the grandparent red
                    z->setRed(true);
                } else {
                    if (z == z->getParent()->getRight()) { //if z is a right child
                        z = z->getParent();
                        leftRotate(z);
                    }

                    z->getParent()->setRed(false);
                    z->getParent()->getParent()->setRed(true);
                    rightRotate(z->getParent()->getParent());
                }
            } else { //reversed!
                RBNode* y = z->getParent()->getParent()->getLeft(); //y is the uncle

                //if uncle is red and exists
                if (y != 0 && y->isRed()) {

                    //make z's parent black
                    z->getParent()->setRed(false);

                    //make uncle black
                    y->setRed(false);

                    //make z, z's grandparent
                    z = z->getParent()->getParent();

                    //make the grandparent red
                    z->setRed(true);
                } else if (z == z->getParent()->getLeft()) { //if z is a right child
                    z = z->getParent();
                    rightRotate(z);

                    z->getParent()->setRed(false);
                    z->getParent()->getParent()->setRed(true);
                    leftRotate(z->getParent()->getParent());
                }
            }

            //debug cout << z->head << endl;
        }
    }

    tree->setRed(false); //hopefully tree is never 0 at this point
}

void RBTree::leftRotate(RBNode* x) {
    RBNode* y = x->getRight();

    //turn y's left subtree into x's right subtree
    x->setRight(y->getLeft());

    if (y->getLeft() != 0) //if y's left isn't empty
        y->getLeft()->setParent(x); //update the parent

    y->setParent(x->getParent()); //link x's parent to y

    if (x->getParent() == 0) //if x is the root
        tree = y; //update the root
    else if (x == x->getParent()->getLeft()) //if not the root, but x is a left child
        x->getParent()->setLeft(y);
    else //x is a right child
        x->getParent()->setRight(y);

    y->setLeft(x); //actually do the move
    x->setParent(y); //update parent
}

void RBTree::rightRotate(RBNode* x) {

    RBNode* y = x->getLeft();

    //turn y's right subtree into x's left subtree
    x->setLeft(y->getRight());

    if (y->getRight() != 0) //if y's right isn't empty
        y->getRight()->setParent(x); //update the parent

    y->setParent(x->getParent()); //link x's parent to y

    if (x->getParent() == 0) //if x is the root
        tree = y; //update the root
    else if (x == x->getParent()->getLeft()) //if not the root, but x is a left child
        x->getParent()->setLeft(y);
    else //x is a right child
        x->getParent()->setRight(y);

    y->setRight(x); //actually do the move
    x->setParent(y); //update parent
}

//standard delete for the most part
//you can tell I wrote this late at night because there are almost no comments

void RBTree::rb_delete(RBNode* z) {
    RBNode* y = z;
    bool y_original_color = y->isRed();

    RBNode* x = 0;

    //save in case of null x
    bool isright;
    RBNode* parent;
    bool isred = false;

    if (z->getLeft() == 0) {
        //update save
        isright = true;
        parent = z->getParent();
        
        x = z->getRight();

        rb_transplant(z, z->getRight());
    } else if (z->getRight() == 0) {
        //update save
        isright = false;
        parent = z->getParent();
        
        x = z->getLeft();

        rb_transplant(z, z->getLeft());
    } else {
        y = tree_minimum(z->getRight());
        y_original_color = y->isRed();
        x = y->getRight();

        //update save
        isright = true;
        parent = y;

        if (y->getParent() == z) {
            if (x != 0) //don't do anything if x is 0
                x->setParent(y);
        } else {
            rb_transplant(y, y->getRight());

            y->setRight(z->getRight());
            y->getRight()->setParent(y);
        }

        rb_transplant(z, y);

        y->setLeft(z->getLeft());
        y->getLeft()->setParent(y);
        y->setRed(z->isRed());

        delete z; //I think this is right
    }

    if (y_original_color == false) { //if black
        if (x != 0)
            rb_delete_fixup(x); //I'm not risking using the special case on this
        else //if x is zero use the special case fixup
            rb_delete_fixup_sentinel(x, isright, parent, isred);
    }
}

//normal fixup that doesn't work if x is 0

void RBTree::rb_delete_fixup(RBNode* x) {

    while (x != tree && x->isRed() == false) {

        if (x == x->getParent()->getLeft()) { //if x is a left node
            RBNode* w = x->getParent()->getRight();

            if (w->isRed()) {
                w->setRed(false);
                x->getParent()->setRed(true);
                leftRotate(x->getParent());
                w = x->getParent()->getRight();
            }

            //both left and right are black
            if (w->getLeft()->isRed() == false &&
                    w->getRight()->isRed() == false) {
                w->setRed(true);
                x = x->getParent();
            } else if (w->getRight()->isRed() == false) {
                w->getLeft()->setRed(false);
                w->setRed(true);
                rightRotate(w);
                w = x->getParent()->getRight();

                w->setRed(x->getParent()->isRed());
                x->getParent()->setRed(false);
                w->getRight()->setRed(false);
                leftRotate(x->getParent());
                x = tree;
            }

        } else { //reversed! (if x is a right node)
            RBNode* w = x->getParent()->getLeft();

            if (w->isRed()) {
                w->setRed(false);
                x->getParent()->setRed(true);
                rightRotate(x->getParent());
                w = x->getParent()->getLeft();
            }

            //both left and right are black
            if (w->getLeft()->isRed() == false &&
                    w->getRight()->isRed() == false) {
                w->setRed(true);
                x = x->getParent();
            } else {
                if (w->getLeft()->isRed() == false) {
                    w->getRight()->setRed(false);
                    w->setRed(true);
                    leftRotate(w);
                    w = x->getParent()->getLeft();

                    //
                }

                //the book's formatting here is super confusing
                //is this inside the elseif??
                w->setRed(x->getParent()->isRed());
                x->getParent()->setRed(false);
                w->getLeft()->setRed(false);
                rightRotate(x->getParent());
                x = tree;
            }
        }
    }

    if (x != 0)
        x->setRed(false);
}

//Is this really what you have to do??
//special case of fixup when x is null
//probably works on all the other cases too, but I'm not risking it

void RBTree::rb_delete_fixup_sentinel(RBNode* x, bool isright, RBNode* parent, bool isred) {

    while (x != tree && isred == false) { //using other ways of checking

        if (!isright) { //if x is a left node
            RBNode* w = parent->getRight();

            if (w->isRed()) {
                w->setRed(false);
                parent->setRed(true);
                leftRotate(parent);
                w = parent->getRight();
            }

            //both left and right are black
            if (w->getLeft()->isRed() == false && w->getRight()->isRed() == false) {
                w->setRed(true);
                x = x->getParent();

                //update to the new values
                isright = (x->getParent()->getRight() == x);
                parent = x->getParent();
                isred = x->isRed();
            } else if (w->getRight()->isRed() == false) {
                w->getLeft()->setRed(false);
                w->setRed(true);
                rightRotate(w);
                w = parent->getRight();

                w->setRed(parent->isRed());
                parent->setRed(false);
                w->getRight()->setRed(false);
                leftRotate(parent);
                x = tree;
            }

        } else { //reversed! (if x is a right node)
            RBNode* w = parent->getLeft();

            if (w != 0 && w->isRed()) {

                w->setRed(false);
                parent->setRed(true);
                rightRotate(parent);
                w = parent->getLeft();
            }

            //both left and right are black
            if (w->getLeft()->isRed() == false &&
                    w->getRight()->isRed() == false) {

                w->setRed(true);
                x = parent;

                isright = (x->getParent()->getRight() == x);
                parent = x->getParent();
                isred = x->isRed();
            } else {
                if (w->getLeft()->isRed() == false) {

                    w->getRight()->setRed(false);
                    w->setRed(true);
                    leftRotate(w);
                    w = parent->getLeft();

                    //
                }

                //the book's formatting here is super confusing here again
                //is this inside the elseif??
                w->setRed(parent->isRed());
                parent->setRed(false);
                w->getLeft()->setRed(false);
                rightRotate(parent);
                x = tree;
            }
        }

        if (x != 0) {
            parent = x->getParent();
            isred = x->isRed();
            if (parent != 0) {
                isright = (x->getParent()->getRight() == x);
            }
        }
    }

    if (x != 0) //ugh
        x->setRed(false);
}

//puts v into u's location

void RBTree::rb_transplant(RBNode* u, RBNode* v) { //causes leaks if not fixed?

    if (u->getParent() == 0) {
        tree = v;
    } else if (u == u->getParent()->getLeft()) { //if u is a left node
        u->getParent()->setLeft(v);
    } else { //if u is a right node
        u->getParent()->setRight(v);
    }

    if (v != 0) {
        v->setParent(u->getParent());
    }
}

//gets minimum node in the subtree

RBNode* RBTree::tree_minimum(RBNode* x) {
    while (x->getLeft() != 0) {
        x = x->getLeft();
    }

    return x;
}

//gets maximum node in the subtree

RBNode* RBTree::tree_maximum(RBNode* x) {
    while (x->getRight() != 0) {
        x = x->getRight();
    }

    return x;
}
