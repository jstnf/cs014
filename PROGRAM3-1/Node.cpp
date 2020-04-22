#include "Node.h"

Node::Node() : left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) { }

bool Node::hasTwoStrings() const
{
    return !large.empty();
}