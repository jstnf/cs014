#include "Heap.h"

#include <iostream>

using std::cout;
using std::endl;

Heap::Heap()
{
    numItems = 0;
}

void Heap::enqueue(PrintJob* job)
{
    if (numItems != MAX_HEAP_SIZE)
    {
        if (empty())
        {
            arr[numItems] = job;
            numItems++;
        }
        else
        {
            int currIndex = numItems;
            while (currIndex > 0 && arr[(currIndex - 1) / 2]->getPriority() < job->getPriority())
            {
                arr[currIndex] = arr[(currIndex - 1) / 2];
                currIndex = (currIndex - 1) / 2;
            }

            arr[currIndex] = job;
            numItems++;
        }
    }
}

void Heap::dequeue()
{
    if (!empty())
    {
        if (numItems != 1)
        {
            arr[0] = arr[numItems - 1];
        }

        numItems--;
        trickleDown(0);
    }
}

PrintJob* Heap::highest()
{
    return numItems == 0 ? nullptr : arr[0];
}

void Heap::print()
{
    if (!empty())
    {
        cout << "Priority: " << highest()->getPriority()
             << ", Job Number: " << highest()->getJobNumber()
             << ", Number of Pages: " << highest()->getPages();
    }

    cout << endl;
}

void Heap::trickleDown(int index)
{
    if (numItems < index * 2 + 2) // No children (base case)
    {
        return;
    }
    else if (numItems == index * 2 + 2) // 1 child (base case)
    {
        if (arr[index]->getPriority() < arr[numItems - 1]->getPriority())
        {
            swap(index, numItems - 1);
        }
    }
    else // 2 children (do recursion)
    {
        PrintJob* leftChild = arr[index * 2 + 1];
        PrintJob* rightChild = arr[index * 2 + 2];

        if (leftChild->getPriority() > rightChild->getPriority())
        {
            // Left child is greater, compare it to index
            if (arr[index]->getPriority() < arr[index * 2 + 1]->getPriority())
            {
                swap(index, index * 2 + 1);
            }

            trickleDown(index * 2 + 1);
        }
        else
        {
            // Right child is greater, compare it to index
            if (arr[index]->getPriority() < arr[index * 2 + 2]->getPriority())
            {
                swap(index, index * 2 + 2);
            }

            trickleDown(index * 2 + 2);
        }
    }
}

void Heap::swap(int firstIndex, int secondIndex)
{
    PrintJob* temp = arr[firstIndex];
    arr[firstIndex] = arr[secondIndex];
    arr[secondIndex] = temp;
}
