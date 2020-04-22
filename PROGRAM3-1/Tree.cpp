#include "Tree.h"

#include <iostream>

using std::cout;

Tree::Tree()
{
    root = nullptr;
}

Tree::~Tree()
{
    delete recurDelete(root);
}

void Tree::insert(const string &str)
{
    if (!root)
    {
        root = new Node();
        root->small = str;
    }
    else
    {
        // Recursive down until we encounter a leaf
        Node* targetNode = root;
        while (targetNode->left)
        {
            // Get the order of the string relative to small and (if exists) large to find which Node to travel to
            if (targetNode->hasTwoStrings())
            {
                if (targetNode->small > str)
                {
                    targetNode = targetNode->left;
                }
                else if (targetNode->large < str)
                {
                    targetNode = targetNode->right;
                }
                else
                {
                    targetNode = targetNode->middle;
                }
            }
            else
            {
                if (targetNode->small > str)
                {
                    targetNode = targetNode->left;
                }
                else
                {
                    targetNode = targetNode->middle;
                }
            }
        }

        if (targetNode->hasTwoStrings())
        {
            // Find the small, middle, and large string of the three
            // Split up the three into the target node with middle string and two new leaf nodes as its children
            string small;
            string middle;
            string large;

            if (targetNode->small > str)
            {
                small = str;
                middle = targetNode->small;
                large = targetNode->large;
            }
            else
            {
                small = targetNode->small;

                if (targetNode->large < str)
                {
                    middle = targetNode->large;
                    large = str;
                }
                else
                {
                    middle = str;
                    large = targetNode->large;
                }
            }

            Node* smallNode = new Node();
            smallNode->small = small;
            Node* largeNode = new Node();
            largeNode->small = large;

            targetNode->small = middle;
            targetNode->large = ""; // assign empty
            targetNode->left = smallNode;
            targetNode->middle = largeNode;
            targetNode->right = nullptr; // might be redundant

            smallNode->parent = targetNode;
            largeNode->parent = targetNode;

            // Time to do some shifting
            shiftUp(targetNode);
        }
        else
        {
            // The node has 1 string in it, find if it should be inserted into the left or right
            if (targetNode->small > str)
            {
                // Put str in the small area and bring small up to large
                targetNode->large = targetNode->small;
                targetNode->small = str;
            }
            else
            {
                // Put str in the large area
                targetNode->large = str;
            }
        }
    }
}

void Tree::preOrder() const
{
    preOrder(root);
}

void Tree::inOrder() const
{
    inOrder(root);
}

void Tree::postOrder() const
{
    postOrder(root);
}

void Tree::remove(const string &str)
{
    Node* searchNode = root;
    while (searchNode)
    {
        // Compare small and (possibly) large
        if (searchNode->small == str || (searchNode->hasTwoStrings() && searchNode->large == str))
        {
            break;
        }
        else // Re-assign searchNode with possible children
        {
            if (searchNode->small > str)
            {
                // Go to the left
                searchNode = searchNode->left;
            }
            else
            {
                if (searchNode->hasTwoStrings() && searchNode->large < str)
                {
                    // The string we're searching for is larger than both strings, go to right
                    searchNode = searchNode->right;
                }
                else
                {
                    // There is only one child or it's in-between two children, go to the middle (right)
                    searchNode = searchNode->middle;
                }
            }
        }
    }

    if (searchNode)
    {
        if (searchNode->hasTwoStrings())
        {
            if (str == searchNode->small)
            {
                searchNode->small = searchNode->large;
                searchNode->large = "";
            }
            else
            {
                searchNode->large = "";
            }
        }
        else
        {
            Node* parent = searchNode->parent;
            if (parent) {
                if (str < parent->small) {
                    parent->left = nullptr;
                    parent->large = parent->middle->small;
                    parent->middle = nullptr;
                } else {
                    parent->middle = nullptr;
                    parent->large = parent->small;
                    parent->small = parent->left->small;
                    parent->left = nullptr;
                }
            }
            else
            {
                Node* temp = new Node();
                if (root->left) {
                    temp->small = root->left->small;
                    temp->large = root->middle->small;
                    root = temp;
                } else {
                    root = nullptr;
                }
            }
        }
    }
}

bool Tree::search(const string &str) const
{
    Node* searchNode = root;
    while (searchNode)
    {
        // Compare small and (possibly) large
        if (searchNode->small == str || (searchNode->hasTwoStrings() && searchNode->large == str))
        {
            return true;
        }
        else // Re-assign searchNode with possible children
        {
            if (searchNode->small > str)
            {
                // Go to the left
                searchNode = searchNode->left;
            }
            else
            {
                if (searchNode->hasTwoStrings() && searchNode->large < str)
                {
                    // The string we're searching for is larger than both strings, go to right
                    searchNode = searchNode->right;
                }
                else
                {
                    // There is only one child or it's in-between two children, go to the middle (right)
                    searchNode = searchNode->middle;
                }
            }
        }
    }

    return false;
}

void Tree::shiftUp(Node *node)
{
    // The node provided in this function needs to be moved into its parent and ALWAYS has only 1 node
    // Therefore, if there is no parent, we shouldn't do anything
    // Only run if the parent is valid
    if (node->parent)
    {
        Node* parent = node->parent;
        if (parent->hasTwoStrings()) // This is our recursive case!
        {
            // Three cases: the node's string is smaller, in the middle, or larger than the node's two strings
            if (parent->small > node->small) // Node is coming from the LEFT
            {
                Node* newLarge = new Node();
                // newLarge takes the parent's middle and right children
                newLarge->left = parent->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->right;
                newLarge->middle->parent = newLarge;
                newLarge->small = parent->large;

                // Reset values of parent and insert the value from node
                parent->left = node; // The new small is the node itself, intact
                parent->middle = newLarge;
                parent->right = nullptr;
                // parent's small stays as parent's small
                parent->large = ""; // Reset to empty

                // Complete the chain by linking newLarge's parent value up
                newLarge->parent = parent;
            }
            else if (parent->large < node->small) // Node is coming from the RIGHT
            {
                Node* newSmall = new Node();
                // newSmall takes the parent's left and middle children
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = parent->middle;
                newSmall->middle->parent = newSmall;
                newSmall->small = parent->small;

                // Reset values of parent and insert the value from node
                parent->left = newSmall;
                parent->middle = node; // The new large is the node itself, intact
                parent->right = nullptr;
                parent->small = parent->large;
                parent->large = ""; // Reset to empty

                // Complete the chain by linking newSmall's parent value up
                newSmall->parent = parent;
            }
            else // Node is coming from the MIDDLE
            {
                Node* newSmall = new Node();
                newSmall->small = parent->small;
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = node->left;
                newSmall->middle->parent = newSmall;

                Node* newLarge = new Node();
                newLarge->small = parent->large;
                newLarge->left = node->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->middle;
                newLarge->middle->parent = newLarge;

                // Reset values of parent and insert the value from node
                parent->left = newSmall;
                parent->middle = newLarge;
                parent->right = nullptr;
                parent->small = node->small;
                parent->large = ""; // Reset to empty

                // Complete the chain by linking newSmall and newLarge's parent values up
                newSmall->parent = parent;
                newLarge->parent = parent;

                delete node; // Delete node as it is now unneeded
            }

            shiftUp(parent);
        }
        else // Moving up into the same node, dealing with children (base case!)
        {
            if (parent->small > node->small) // node is coming from the left side
            {
                parent->large = parent->small;
                parent->small = node->small;

                // Since the node's string is smaller, the node's left and middle are placed onto the parent's left and middle
                // The parent's middle is the remaining child that needs to be assigned onto the parent's right
                parent->left = node->left;
                parent->right = parent->middle;
                parent->middle = node->middle;
            }
            else // node is coming from the middle (right)
            {
                parent->large = node->small;

                // Since the node's string is larger, the node's left and middle are placed onto the parent's middle and right
                // The parent's left is the remaining child, and it doesn't need to be moved
                parent->middle = node->left;
                node->left->parent = parent;
                parent->right = node->middle;
                node->middle->parent = parent;
            }

            // Update both the parent pointers and delete the now useless node
            node->left->parent = parent;
            node->middle->parent = parent;
            delete node;
        }
    }
}

Node *Tree::recurDelete(Node *node)
{
    if (node)
    {
        delete recurDelete(node->left);
        delete recurDelete(node->middle);
        delete recurDelete(node->right);
    }

    return node;
}

void Tree::preOrder(Node *node) const
{
    if (node)
    {
        if (node->hasTwoStrings())
        {
            // SM LE LA MI RI
            cout << node->small << ", ";
            preOrder(node->left);
            cout << node->large << ", ";
            preOrder(node->middle);
            preOrder(node->right);
        }
        else
        {
            cout << node->small << ", ";
            preOrder(node->left);
            preOrder(node->middle);
        }
    }
}

void Tree::inOrder(Node *node) const
{
    if (node)
    {
        inOrder(node->left);
        cout << node->small << ", ";
        inOrder(node->middle);

        // There are two strings in the node
        if (node->hasTwoStrings())
        {
            cout << node->large << ", ";
            inOrder(node->right);
        }
    }
}

void Tree::postOrder(Node *node) const
{
    if (node)
    {
        if (node->hasTwoStrings())
        {
            // LE MI SM RI LA
            postOrder(node->left);
            postOrder(node->middle);
            cout << node->small << ", ";
            postOrder(node->right);
            cout << node->large << ", ";
        }
        else
        {
            postOrder(node->left);
            postOrder(node->middle);
            cout << node->small << ", ";
        }
    }
}
