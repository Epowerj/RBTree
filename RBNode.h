
#ifndef RBNODE_H
#define RBNODE_H

class RBNode {
public:
    RBNode();
    RBNode(int value, bool isred, RBNode* rightnode, RBNode* leftnode,
                RBNode* parentnode);
    RBNode(const RBNode& other);
    virtual ~RBNode();
    
    virtual RBNode* getSibling(RBNode* node);
    
    virtual int getHead();
    virtual bool isRed();
    virtual RBNode* getRight();
    virtual RBNode* getLeft();
    virtual RBNode* getParent();
    
    virtual void setHead(int value);
    virtual void setRed(bool value);
    virtual void setRight(RBNode* toset);
    virtual void setLeft(RBNode* toset);
    virtual void setParent(RBNode* toset);
    
private:

    int head; //main node value
    bool red; //false is black, true is red
    RBNode * right;
    RBNode * left;
    RBNode * parent;

};

#endif /* RBNODE_H */

