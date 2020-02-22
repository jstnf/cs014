#include "arithmeticExpression.h"

#include <fstream>
#include <sstream>
#include <stack>

using std::cout;
using std::endl;
using std::ostringstream;
using std::stack;

int arithmeticExpression::priority(char op)
{
    int priority = 0;
    if (op == '(')
    {
        priority = 3;
    }
    else if (op == '*' || op == '/')
    {
        priority = 2;
    }
    else if (op == '+' || op == '-')
    {
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix()
{
    stack<char> s;
    ostringstream oss;
    char c;
    for (unsigned i = 0; i < infixExpression.size(); ++i)
    {
        c = infixExpression.at(i);
        if (c == ' ')
        {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') //c is an operator
        {
            if (c == '(')
            {
                s.push(c);
            }
            else if (c == ')')
            {
                while (s.top() != '(')
                {
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else
            {
                while (!s.empty() && priority(c) <= priority(s.top()))
                {
                    if (s.top() == '(')
                    {
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else //c is an operand
        {
            oss << c;
        }
    }
    while (!s.empty())
    {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

//void arithmeticExpression::visualizeTree(const string &outputFilename)
//{
//    ofstream outFS(outputFilename.c_str());
//    if (!outFS.is_open())
//    {
//        cout << "Error opening " << outputFilename << endl;
//        return;
//    }
//    outFS << "digraph G {" << endl;
//    visualizeTree(outFS, root);
//    outFS << "}";
//    outFS.close();
//    string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
//    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
//    system(command.c_str());
//}

arithmeticExpression::arithmeticExpression(const string &expr) : infixExpression(expr), root(nullptr) { }

void arithmeticExpression::buildTree()
{
    string postFix = infix_to_postfix();
    char key = 'a';

    root = buildNode(postFix, key);
}

TreeNode *arithmeticExpression::buildNode(string &eq, char &key)
{
    if (!eq.empty())
    {
        TreeNode* node = new TreeNode(eq.at(eq.size() - 1), static_cast<char>(key));
        key++;
        eq.pop_back();

        if (priority(node->data) > 0)
        {
            node->right = buildNode(eq, key);
            node->left = buildNode(eq, key);
        }

        return node;
    }

    return nullptr;
}

void arithmeticExpression::infix()
{
    infix(root);
}

void arithmeticExpression::prefix()
{
    prefix(root);
}

void arithmeticExpression::postfix()
{
    postfix(root);
}

void arithmeticExpression::infix(TreeNode *node)
{
    if (node != nullptr)
    {
        if (node->left != nullptr)
        {
            cout << '(';
        }

        infix(node->left);
        cout << node->data;
        infix(node->right);

        if (node->left != nullptr)
        {
            cout << ')';
        }
    }
}

void arithmeticExpression::prefix(TreeNode *node)
{
    if (node != nullptr)
    {
        cout << node->data;
        prefix(node->left);
        prefix(node->right);
    }
}

void arithmeticExpression::postfix(TreeNode *node)
{
    if (node != nullptr)
    {
        postfix(node->left);
        postfix(node->right);
        cout << node->data;
    }
}