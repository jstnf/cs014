#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include "Node.h"

class AVLTree
{
  private:
    Node* root = nullptr;
  public:
    int balanceFactor(Node*) const;
    void insert(const string &);
    void printBalanceFactors() const;
  private:
    void updateHeight(Node*);
    bool setChild(Node*, string, Node*);
    bool replaceChild(Node*, Node*, Node*);
    void rotateRight(Node*);
    void rotateLeft(Node*);
    void rebalance(Node*);
    void recurBalanceFactors(Node*) const;
};

#endif // __AVLTREE_H__