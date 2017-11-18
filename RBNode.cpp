
#include "RBNode.h"

RBNode::RBNode() {
    head = 0;
    red = true; //black is false, red is true
    right = 0;
    left = 0;
    parent = 0;
}

RBNode::RBNode(int value, bool isred, RBNode* rightnode, RBNode* leftnode,
                RBNode* parentnode){
    head = value;
    red = isred; //black is false, red is true
    right = rightnode;
    left = leftnode;
    parent = parentnode;
}

RBNode::RBNode(const RBNode& other) {
    head = other.head;
    red = other.red; //black is false, red is true
    right = other.right;
    left = other.left;
    parent = other.parent;
}

RBNode::~RBNode() {
    //TODO
    //no good destructor
    //I assume that the tree handles this
}

RBNode* RBNode::getSibling(RBNode* node){
    if(node == left){
        return right;
    }else{
        return right;
    }
}

int RBNode::getHead(){
    return head;
}

bool RBNode::isRed(){
    return red;
}

RBNode* RBNode::getRight(){
    return right;
}

RBNode* RBNode::getLeft(){
    return left;
}

RBNode* RBNode::getParent(){
    return parent;
}

void RBNode::setHead(int value){
    head = value;
}

void RBNode::setRed(bool value){
    red = value;
}

void RBNode::setRight(RBNode * toset){
    right = toset;
}

void RBNode::setLeft(RBNode * toset){
    left = toset;
}

void RBNode::setParent(RBNode * toset){
    parent = toset;
}
