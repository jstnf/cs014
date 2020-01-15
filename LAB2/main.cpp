#include "IntList.h"

#include <iostream>

using std::cout;
using std::endl;

int main() {
    cout << "Creating new IntList." << endl;
    IntList* list = new IntList();
    cout << "Printing empty list forward: " << *list << endl;
    cout << "Printing empty list in reverse: ";
    list->printReverse();
    cout << endl << endl;

    cout << "push_front(5)" << endl;
    list->push_front(5);
    cout << "Forward: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl << endl;

    cout << "push_back(8)" << endl;
    list->push_back(8);
    cout << "Forward: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl << endl;

    cout << "push_front(9)" << endl;
    list->push_front(9);
    cout << "Forward: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl << endl;

    cout << "push_back(100)" << endl;
    list->push_back(100);
    cout << "Forward: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl << endl;

    cout << "pop_front()" << endl;
    list->pop_front();
    cout << "Forward: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl << endl;

    cout << "pop_back()" << endl;
    list->pop_back();
    cout << "Forward: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl << endl;

    cout << "pop_front()" << endl;
    list->pop_front();
    cout << "Forward: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl << endl;

    cout << "pop_back()" << endl;
    list->pop_back();
    cout << "Forward: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl << endl;

    cout << "pop_back() empty list" << endl;
    list->pop_back();
    cout << "Forward: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl << endl;

    cout << "pop_front() empty list" << endl;
    list->pop_front();
    cout << "Forward: " << *list << endl;
    cout << "Reverse: ";
    list->printReverse();
    cout << endl;

    cout << "Destructor (deleting list)" << endl;
    delete list;
    cout << "Printing forward deleted pointer. Program will crash!" << endl;
    cout << "Forward: " << *list << endl;
    return 0;
}