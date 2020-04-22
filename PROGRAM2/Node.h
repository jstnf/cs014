#ifndef __NODE_H__
#define __NODE_H__

#include <string>

using std::string;

class Node
{
  private:
    string data;
    Node* left;
    Node* right;
    int count;
  public:
    Node(string);
    void setData(string);
    void setLeft(Node*);
    void setRight(Node*);
    void setCount(int);
    string getData() const;
    Node* getLeft() const;
    Node* getRight() const;
    int getCount() const;
};

#endif // __NODE_H__