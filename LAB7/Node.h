#ifndef __NODE_H__
#define __NODE_H__

#include <string>

using std::string;

struct Node
{
    Node(string);
    int height;
    string key;
    Node* left;
    Node* right;
    Node* parent;
};

#endif // __NODE_H__