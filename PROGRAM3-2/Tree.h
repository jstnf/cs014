#ifndef __TREE_H__
#define __TREE_H__

#include "Node.h"

class Tree
{
private:
    Node *root;
public:
    Tree();
    ~Tree();
    void insert(const string &);
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
    void remove(const string &);
    bool search (const string &) const;
    void shiftUp(Node*);
private:
    // Add additional functions/variables here
    Node* recurDelete(Node*);
    void preOrder(Node*) const;
    void inOrder(Node*) const;
    void postOrder(Node*) const;
    void fix(Node*);
    void redistribute(Node*);
    Node* searchPointer(const string&) const;
};

#endif