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
    void remove(const string &); // TODO
    bool search (const string &) const;
    void shiftUp(Node*);
  private:
    // Add additional functions/variables here
    Node* recurDelete(Node*);
    void preOrder(Node*) const; // TODO
    void inOrder(Node*) const;
    void postOrder(Node*) const; // TODO
};

#endif