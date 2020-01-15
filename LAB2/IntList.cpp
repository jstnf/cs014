#include "IntList.h"

using std::cout;
using std::endl;

IntList::IntList() : dummyHead(new IntNode(0)), dummyTail(new IntNode(0)) {
    dummyHead->next = dummyTail;
    dummyHead->prev = dummyTail;
    dummyTail->next = dummyHead;
    dummyTail->prev = dummyHead;
}

IntList::~IntList() {
    IntNode* curr = dummyHead;
    while (curr != dummyTail)
    {
        IntNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete curr;
}

void IntList::push_front(int value) {
    IntNode* newNode = new IntNode(value);
    IntNode* temp = dummyHead->next;
    newNode->prev = dummyHead;
    newNode->next = temp;
    dummyHead->next = newNode;
    temp->prev = newNode;
}

void IntList::pop_front() {
    if (!empty()) {
        IntNode* temp = dummyHead->next;
        dummyHead->next = temp->next;
        temp->next->prev = dummyHead;
        delete temp;
    }
}

void IntList::push_back(int value) {
    IntNode* newNode = new IntNode(value);
    IntNode* temp = dummyTail->prev;
    newNode->prev = temp;
    newNode->next = dummyTail;
    dummyTail->prev = newNode;
    temp->next = newNode;
}

void IntList::pop_back() {
    if (!empty()) {
        IntNode* temp = dummyTail->prev;
        dummyTail->prev = temp->prev;
        temp->prev->next = dummyTail;
        delete temp;
    }
}

bool IntList::empty() const {
    return dummyHead->next == dummyTail;
}

ostream & operator<<(ostream &out, const IntList &rhs) {
    if (!rhs.empty()) {
        IntNode* curr = rhs.dummyHead->next;
        while (curr->next != rhs.dummyTail) {
            out << curr->data << " ";
            curr = curr->next;
        }
        out << curr->data;
    }

    return out;
}

void IntList::printReverse() const {
    if (!empty()) {
        IntNode* curr = dummyTail->prev;
        while (curr->prev != dummyHead) {
            cout << curr->data << " ";
            curr = curr->prev;
        }
        cout << curr->data;
    }
}