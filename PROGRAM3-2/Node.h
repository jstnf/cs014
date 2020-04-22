#ifndef __NODE_H__
#define __NODE_H__

#include <string>

using std::string;

class Node
{
    friend class Tree;

private:
    string small;
    string large;

    Node *left;
    Node *middle;
    Node *right;
    Node *parent;

    // Add additional functions/variables here. Remember, you may not add any
    // Node * or string variables.

    /* I hope the constructor doesn't count under the conditions above :( */
    Node();
    bool hasTwoStrings() const;
};

#endif
