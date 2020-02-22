#ifndef __STACK_H__
#define __STACK_H__

#include <stdexcept>

using std::out_of_range;
using std::overflow_error;
using std::underflow_error;

template<typename T>
class stack
{
  private:
    static const int MAX_SIZE = 20;
    T data[MAX_SIZE];
    int size;
  public:
    stack()
    {
        size = 0;
    }

    void push(T val)
    {
        if (size == MAX_SIZE)
        {
            throw overflow_error("Called push on full stack.");
        }

        data[size] = val;
        size++;
    }

    void pop()
    {
        if (empty())
        {
            throw out_of_range("Called pop on empty stack.");
        }

        size--;
    }

    T top() const
    {
        if (empty())
        {
            throw underflow_error("Called top on empty stack.");
        }

        return data[size - 1];
    }

    bool empty() const
    {
        return size == 0;
    }
};

#endif