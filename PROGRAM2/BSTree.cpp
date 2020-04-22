#include "BSTree.h"

#include <algorithm>
#include <iostream>

using std::cout;
using std::max;

BSTree::BSTree() : root(nullptr) { }

BSTree::~BSTree()
{
    delete root; // Goes down recursively through Node destructor
}

void BSTree::insert(const string &newString)
{
    Node* parent = nullptr;
    Node* curr = root;
    bool isLeft = true;

    while (curr && !(newString == curr->getData()))
    {
        if (curr->getData() > newString)
        {
            parent = curr;
            curr = curr->getLeft();
            isLeft = true;
        }
        else
        {
            parent = curr;
            curr = curr->getRight();
            isLeft = false;
        }
    }

    if (curr) // We found a node that matches the string
    {
        curr->setCount(curr->getCount() + 1);
    }
    else // We're inserting a new Node
    {
        Node* newNode = new Node(newString);

        if (parent) // Check if the parent is valid
        {
            if (isLeft)
            {
                parent->setLeft(newNode);
            }
            else
            {
                parent->setRight(newNode);
            }
        }
        else // If no parent, that means that the BST was empty
        {
            root = newNode;
        }
    }
}

void BSTree::remove(const string &key)
{
    // Check if empty, do nothing

    // Locate the node, going down until either find it or null
    // Check count, if > 1 decrement
    // else, run algorithm

    // Find the node to delete
    Node* parent = nullptr;
    Node* curr = root;
    bool isLeft = true;

    while (curr && !(curr->getData() == key))
    {
        if (curr->getData() > key)
        {
            parent = curr;
            curr = curr->getLeft();
            isLeft = true;
        }
        else if (curr->getData() < key)
        {
            parent = curr;
            curr = curr->getRight();
            isLeft = false;
        }
    }

    // If node with string exists (this also handles empty case)
    if (curr) // curr now points to the node we need
    {
        if (curr->getCount() > 1) // Decrement count since it's greater than 1
        {
            curr->setCount(curr->getCount() - 1);
        }
        else // Count is 1, remove the node
        {
            // If has left, find the largest node on left subtree and replace
            if (curr->getLeft())
            {
                Node* subCurr = curr->getLeft();

                // Find largest node on left subtree
                while (subCurr->getRight())
                {
                    subCurr = subCurr->getRight();
                }

                // Copy data and count from subCurr up to curr
                curr->setData(subCurr->getData());
                curr->setCount(subCurr->getCount());

//                // Move children of subCurr up
//                if (subParent != curr)
//                {
//                    // We're dealing with left nodes here since we traversed right
//                    subParent->setRight(subCurr->getLeft());
//                    // This should account for if subCurr's left was nullptr (we're just moving a nullptr up)
//                }
//                else // If subParent was curr, that means we need to update its left value
//                {
//                    // Nothing was to the right, but there might be things to the left
//                    subParent->setLeft(subCurr->getLeft());
//                }

                // Get the right most child of left subtree to replace subCurr
                Node* replaceSubCurrParent = subCurr;
                Node* replaceSubCurr = subCurr->getLeft();
                while (replaceSubCurr && replaceSubCurr->getRight())
                {
                    replaceSubCurrParent = replaceSubCurr;
                    replaceSubCurr = replaceSubCurr->getRight();
                }

                // Check if there was actually a node to the left
                if (replaceSubCurr)
                {
                    subCurr->setData(replaceSubCurr->getData());
                    subCurr->setCount(replaceSubCurr->getCount());

                    // Move the left children from the replacing node to the right most in the left subtree
                    if (subCurr->getLeft())
                    {
                        Node* rightChildNewParent = subCurr->getLeft();
                        while (rightChildNewParent->getRight())
                        {
                            rightChildNewParent = rightChildNewParent->getRight();
                        }
                        rightChildNewParent->setRight(replaceSubCurr->getLeft());
                    }
                }

                // Erase the pointer to the right node since it's been brought up
                // If there was no node in the first place, it shouldn't matter because it's already nullptr
                replaceSubCurrParent->setRight(nullptr);

                delete replaceSubCurr;
            }
            else if (curr->getRight()) // If has right, find the smallest node on right subtree and replace
            {
                Node* subCurr = curr->getRight();

                // Find smallest node on right subtree
                while (subCurr->getLeft())
                {
                    subCurr = subCurr->getLeft();
                }

                // Copy data and count from subCurr up to curr
                curr->setData(subCurr->getData());
                curr->setCount(subCurr->getCount());

//                // Move children of subCurr up
//                if (subParent != curr)
//                {
//                    // We're dealing with right nodes here since we traversed left
//                    subParent->setLeft(subCurr->getRight());
//                    // This should account for if subCurr's right was nullptr (we're just moving a nullptr up)
//                }
//                else // If subParent was curr, that means we need to update its right value
//                {
//                    // Nothing was to the left, but there might be things to the right
//                    subParent->setRight(subCurr->getRight());
//                }

                // Get the left most child of right subtree to replace subCurr
                Node* replaceSubCurrParent = subCurr;
                Node* replaceSubCurr = subCurr->getRight();
                while (replaceSubCurr && replaceSubCurr->getLeft())
                {
                    replaceSubCurrParent = replaceSubCurr;
                    replaceSubCurr = replaceSubCurr->getLeft();
                }

                // Check if there was actually a node to the right
                if (replaceSubCurr)
                {
                    subCurr->setData(replaceSubCurr->getData());
                    subCurr->setCount(replaceSubCurr->getCount());

                    // Move the right children from the replacing node to the left most in the right subtree
                    if (subCurr->getRight())
                    {
                        Node* leftChildNewParent = subCurr->getRight();
                        while (leftChildNewParent->getLeft())
                        {
                            leftChildNewParent = leftChildNewParent->getLeft();
                        }
                        leftChildNewParent->setLeft(replaceSubCurr->getRight());
                    }
                }

                // Erase the pointer to the left node since it's been brought up
                // If there was no node in the first place, it shouldn't matter because it's already nullptr
                replaceSubCurrParent->setLeft(nullptr);

                delete replaceSubCurr;
            }
            else // It's a leaf
            {
                if (parent) // The parent isn't null, curr is not root
                {
                    if (isLeft)
                    {
                        parent->setLeft(nullptr);
                        delete curr;
                    }
                    else
                    {
                        parent->setRight(nullptr);
                        delete curr;
                    }
                }
                else // Parent is null, node is root, tree is now empty
                {
                    delete curr;
                    root = nullptr;
                }
            }
        }
    }
}

bool BSTree::search(const string &key) const
{
    Node* curr = root;

    while (curr && !(curr->getData() == key)) // Position curr on the node to find, or nullptr if not found
    {
        if (curr->getData() > key)
        {
            curr = curr->getLeft();
        }
        else if (curr->getData() < key)
        {
            curr = curr->getRight();
        }
    }

    return curr != nullptr;
}

string BSTree::largest() const
{
    Node* curr = root;

    if (curr)
    {
        while (curr->getRight() != nullptr)
        {
            curr = curr->getRight();
        }

        return curr->getData();
    }
    else
    {
        return "";
    }
}

string BSTree::smallest() const
{
    Node* curr = root;

    if (curr)
    {
        while (curr->getLeft() != nullptr)
        {
            curr = curr->getLeft();
        }

        return curr->getData();
    }
    else
    {
        return "";
    }
}

int BSTree::height(const string &key) const
{
    Node* curr = root;

    while (curr && !(curr->getData() == key))
    {
        if (curr->getData() > key)
        {
            curr = curr->getLeft();
        }
        else
        {
            curr = curr->getRight();
        }
    }

    return curr ? heightRecursive(0, curr) : -1;
}

void BSTree::preOrder() const
{
    preOrder(root);
}

void BSTree::postOrder() const
{
    postOrder(root);
}

void BSTree::inOrder() const
{
    inOrder(root);
}

void BSTree::preOrder(Node *node) const
{
    if (node)
    {
        cout << node->getData() << "(" << node->getCount() << "), ";
        preOrder(node->getLeft());
        preOrder(node->getRight());
    }
}

void BSTree::postOrder(Node *node) const
{
    if (node)
    {
        postOrder(node->getLeft());
        postOrder(node->getRight());
        cout << node->getData() << "(" << node->getCount() << "), ";
    }
}

void BSTree::inOrder(Node *node) const
{
    if (node)
    {
        inOrder(node->getLeft());
        cout << node->getData() << "(" << node->getCount() << "), ";
        inOrder(node->getRight());
    }
}

int BSTree::heightRecursive(int initHeight, Node *node) const
{
    if (!node->getLeft() && !node->getRight())
    {
        return initHeight;
    }
    else
    {
       int left = 0;
       int right = 0;

       if (node->getLeft())
       {
           left = heightRecursive(1 + initHeight, node->getLeft());
       }

       if (node->getRight())
       {
           right = heightRecursive(1 + initHeight, node->getRight());
       }

       return max(left, right);
    }
}
