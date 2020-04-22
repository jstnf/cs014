#include "Node.h"

Node::Node(string str) : data(str), left(nullptr), right(nullptr), count(1) { }

void Node::setData(string str)
{
    data = str;
}

void Node::setLeft(Node* newLeft)
{
    left = newLeft;
}

void Node::setRight(Node* newRight)
{
    right = newRight;
}

string Node::getData() const
{
    return data;
}

Node *Node::getLeft() const
{
    return left;
}

Node *Node::getRight() const
{
    return right;
}

void Node::setCount(int newCount)
{
    count = newCount;
}

int Node::getCount() const
{
    return count;
}