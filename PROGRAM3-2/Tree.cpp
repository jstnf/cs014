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

bool Tree::search(const string &str) const
{
    return searchPointer(str);
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
                newLarge->middle = parent->right;
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

void Tree::remove(const string &str)
{
    Node* searchNode = searchPointer(str);

    if (searchNode)
    {
        Node* leafNode = nullptr;

        if (searchNode->left) // If the search node is NOT a leaf
        {
            // We need to swap with in-order successor
            if (searchNode->hasTwoStrings()) // The search node has two strings
            {
                if (str == searchNode->small) // The string is the small, go to the middle for inorder successor
                {
                    leafNode = searchNode->middle;
                    while (leafNode->left)
                    {
                        leafNode = leafNode->left;
                    }

                    searchNode->small = leafNode->small; // Swap with inorder
                }
                else // The string is the large, go to the right for inorder successor
                {
                    leafNode = searchNode->right;
                    while (leafNode->left)
                    {
                        leafNode = leafNode->left;
                    }

                    searchNode->large = leafNode->small; // Swap with inorder
                }
            }
            else // The search node has one string
            {
                leafNode = searchNode->middle;
                while (leafNode->left)
                {
                    leafNode = leafNode->left;
                }

                searchNode->small = leafNode->small;
            }

            // Now that we swapped, get rid of the string that we swapped out
            if (leafNode->hasTwoStrings())
            {
                leafNode->small = leafNode->large;
                leafNode->large = "";
            }
            else
            {
                leafNode->small = "";
            }
        }
        else // The search node is a leaf
        {
            if (searchNode->hasTwoStrings())
            {
                if (str == searchNode->small)
                {
                    searchNode->small = searchNode->large;
                }

                searchNode->large = "";
                // After this case, the leaf node will be guaranteed to have 1 string
            }
            else
            {
                searchNode->small = "";
                // After this case, the leaf node will be guaranteed to have 0 strings
            }

            // Point our leaf node to the searchNode
            leafNode = searchNode;
        }

        // If our leaf node still has a string in it (guaranteed to be either 1 or 0 strings) then we need to do some fixing
        if (leafNode->small.empty())
        {
            fix(leafNode);
        }
    }
}

void Tree::fix(Node *node)
{
    if (node == root)
    {
        if (node->left)
        {
            root = node->left;
            root->parent = nullptr;
        }
        else if (node->middle)
        {
            root = node->middle;
            root->parent = nullptr;
        }
        else // TODO CHECK THE VALIDITY OF THIS CODE
        {
            root = nullptr;
        }

        delete node;
    }
    else
    {
        Node* parent = node->parent;

        // If the parent has any children with two strings, we need to do some redistributing
        if (parent->left->hasTwoStrings() || parent->middle->hasTwoStrings() || (parent->hasTwoStrings() && parent->right->hasTwoStrings())) // TODO INCOMPLETE
        {
            redistribute(parent);
        }
        else // We need to do some merging
        {
            if (parent->hasTwoStrings())
            {
                if (node == parent->left) // TODO CHILDREN?
                {
                    parent->left = parent->middle; // TODO MOVING VALUE INTEAD OF WHOLE NODE?
                    parent->middle = parent->right;
                    parent->right = nullptr;
                    parent->left->large = parent->left->small;
                    parent->left->small = parent->small;
                    parent->small = parent->large;
                    parent->large = "";

                    delete node;
                }
                else if (node == parent->middle) // TODO CHILDREN?
                {
                    parent->left->large = parent->small;
                    parent->small = parent->large;
                    parent->large = "";
                    parent->middle = parent->right; // TODO MOVING VALUE INSTEAD OF WHOLE NODE?
                    parent->right = nullptr;

                    delete node;
                }
                else // Node is the parent's right // TODO CHILDREN?
                {
                    parent->middle->large = parent->large;
                    parent->large = "";
                    parent->right = nullptr;

                    delete node;
                }
            }
            else // Parent only has 1 string (2 children)
            {
                if (node == parent->left)
                {
                    parent->middle->large = parent->middle->small;
                    parent->middle->small = parent->small;
                    parent->small = "";

//                    if (node->middle) // TODO check the validity of this code
//                    {
//                        parent->middle->right = parent->middle->middle;
//                        parent->middle->middle = parent->middle->left;
//                        parent->middle->left = node->middle;
//                    }

                    parent->left = nullptr;
                    delete node;
                }
                else
                {
                    parent->left->large = parent->small;
                    parent->small = "";

//                    if (node->left) // TODO check the validity of this code
//                    {
//                        parent->left->right = node->left;
//                    }

                    parent->middle = nullptr;
                    delete node;
                }

                fix(parent);
            }
        }
    }
}

void Tree::redistribute(Node *parent)
{
    // Find which node is empty in order to know how to redistribute
    if (parent->hasTwoStrings()) // Two string case (3 children)
    {
        if (parent->left->small.empty()) // Left is empty
        {
            if (parent->middle->hasTwoStrings()) // Middle has two strings
            {
                parent->left->small = parent->small;
                parent->small = parent->middle->small;
                parent->middle->small = parent->middle->large;
                parent->middle->large = "";
            }
            else // Right has two strings
            {
                parent->left->small = parent->small;
                parent->small = parent->middle->small;
                parent->middle->small = parent->large;
                parent->large = parent->right->small;
                parent->right->small = parent->right->large;
                parent->right->large = "";
            }
        }
        else if (parent->middle->small.empty()) // Middle is empty
        {
            if (parent->left->hasTwoStrings()) // Left has two strings
            {
                parent->middle->small = parent->small;
                parent->small = parent->left->large;
                parent->left->large = "";
            }
            else // Right has two strings
            {
                parent->middle->small = parent->large;
                parent->large = parent->right->small;
                parent->right->small = parent->right->large;
                parent->right->large = "";
            }
        }
        else // Right is empty
        {
            if (parent->middle->hasTwoStrings()) // Middle has two strings
            {
                parent->right->small = parent->large;
                parent->large = parent->middle->large;
                parent->middle->large = "";
            }
            else // Left has two strings
            {
                parent->right->small = parent->large;
                parent->large = parent->middle->small;
                parent->middle->small = parent->small;
                parent->small = parent->left->large;
                parent->left->large = "";
            }
        }
    }
    else // One-string case (2 children)
    {
        if (parent->left->small.empty())
        {
            // The middle child has two strings
            parent->left->small = parent->small;
            parent->small = parent->middle->small;
            parent->middle->small = parent->middle->large;
            parent->middle->large = "";
        }
        else
        {
            // The left child has two strings
            parent->middle->small = parent->small;
            parent->small = parent->left->large;
            parent->left->large = "";
        }
    }
}

Node *Tree::searchPointer(const string &str) const
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

    return searchNode;
}
