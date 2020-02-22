#include "AVLTree.h"

#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;
using std::max;

int AVLTree::balanceFactor(Node *node) const
{
    int leftHeight = -1;
    if (node->left)
    {
        leftHeight = node->left->height;
    }

    int rightHeight = -1;
    if (node->right)
    {
        rightHeight = node->right->height;
    }

    return leftHeight - rightHeight;
}

void AVLTree::updateHeight(Node *node)
{
    int leftHeight = -1;
    if (node->left)
    {
        leftHeight = node->left->height;
    }

    int rightHeight = -1;
    if (node->right)
    {
        rightHeight = node->right->height;
    }

    node->height = max(leftHeight, rightHeight) + 1;
}

bool AVLTree::setChild(Node *parent, string whichChild, Node *child)
{
    if (whichChild != "left" && whichChild != "right")
    {
        return false;
    }

    if (whichChild == "left")
    {
        parent->left = child;
    }
    else
    {
        parent->right = child;
    }

    if (child)
    {
        child->parent = parent;
    }

    updateHeight(parent);
    return true;
}

bool AVLTree::replaceChild(Node *parent, Node *currentChild, Node *newChild)
{
    if (parent->left == currentChild)
    {
        return setChild(parent, "left", newChild);
    }
    else if (parent->right == currentChild)
    {
        return setChild(parent, "right", newChild);
    }

    return false;
}

void AVLTree::rotateRight(Node *node)
{
    Node* leftRightChild = node->left->right;
    if (node->parent)
    {
        replaceChild(node->parent, node, node->left);
    }
    else // node is root
    {
        root = node->left;
        root->parent = nullptr;
    }

    setChild(node->left, "right", node);
    setChild(node, "left", leftRightChild);
}

void AVLTree::rotateLeft(Node *node)
{
    Node* rightLeftChild = node->right->left;
    if (node->parent)
    {
        replaceChild(node->parent, node, node->right);
    }
    else // node is root
    {
        root = node->right;
        root->parent = nullptr;
    }

    setChild(node->right, "left", node);
    setChild(node, "right", rightLeftChild);
}

void AVLTree::rebalance(Node *node)
{
    updateHeight(node);

    if (balanceFactor(node) == -2)
    {
        if (balanceFactor(node->right) == 1)
        {
            // Double rotation case.
            rotateRight(node->right);
        }

        rotateLeft(node);
    }
    else if (balanceFactor(node) == 2)
    {
        if (balanceFactor(node->left) == -1)
        {
            // Double rotation case.
            rotateLeft(node->left);
        }

        rotateRight(node);
    }
}

void AVLTree::insert(const string &str)
{
    Node* curr = root;
    while (curr)
    {
        if (curr->key > str)
        {
            curr = curr->left;
        }
        else if (curr->key < str)
        {
            curr = curr->right;
        }
        else
        {
            return;
        }
    }

    Node* node = new Node(str);

    if (!root)
    {
        root = node;
        node->parent = nullptr;
        return;
    }

    Node* cur = root;
    while (cur)
    {
        if (node->key < cur->key)
        {
            if (!cur->left)
            {
                cur->left = node;
                node->parent = cur;
                cur = nullptr;
            }
            else
            {
                cur = cur->left;
            }
        }
        else
        {
            if (!cur->right)
            {
                cur->right = node;
                node->parent = cur;
                cur = nullptr;
            }
            else
            {
                cur = cur->right;
            }
        }
    }

    node = node->parent;

    while (node)
    {
        rebalance(node);
        node = node->parent;
    }
}

void AVLTree::printBalanceFactors() const
{
    recurBalanceFactors(root);
    cout << endl;
}

void AVLTree::recurBalanceFactors(Node *node) const
{
    if (node)
    {
        recurBalanceFactors(node->left);
        cout << node->key << "(" << balanceFactor(node) << "), ";
        recurBalanceFactors(node->right);
    }
}
