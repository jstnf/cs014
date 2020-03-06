#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;
const int NUMBERS_SIZE = 50000;

void Quicksort_midpoint(int[], int, int);
void Quicksort_medianOfThree(int[], int, int);
void InsertionSort(int[], int);
void fillArrays(int[], int[], int[]);
int Partition_midpoint(int[], int, int);
int Partition_medianOfThree(int[], int, int);

int main()
{
    int qMidpoint[NUMBERS_SIZE];
    int qMedian[NUMBERS_SIZE];
    int insertion[NUMBERS_SIZE];

    fillArrays(qMidpoint, qMedian, insertion);

    clock_t qMidStart = clock();
    Quicksort_midpoint(qMidpoint, 0, NUMBERS_SIZE - 1);
    clock_t qMidEnd = clock();
    int qMidElapsed = (qMidEnd - qMidStart) / CLOCKS_PER_MS;

    cout << "Quicksort (midpoint): " << qMidElapsed << "ms" << endl;

    clock_t qMedStart = clock();
    Quicksort_medianOfThree(qMedian, 0, NUMBERS_SIZE - 1);
    clock_t qMedEnd = clock();
    int qMedElapsed = (qMedEnd - qMedStart) / CLOCKS_PER_MS;

    cout << "Quicksort (median of three): " << qMedElapsed << "ms" << endl;

    clock_t insertStart = clock();
    InsertionSort(insertion, NUMBERS_SIZE);
    clock_t insertEnd = clock();
    int insertElapsed = (insertEnd - insertStart) / CLOCKS_PER_MS;

    cout << "Insertion Sort: " << insertElapsed << "ms" << endl;

    return 0;
}

void Quicksort_midpoint(int numbers[], int i, int k)
{
    int j = 0;

    // Base case: If there are 1 or zero elements to sort,
    // partition is already sorted
    if (i >= k)
    {
        return;
    }

    // Partition the data within the array. Value j returned
    // from partitioning is location of last element in low partition.
    j = Partition_midpoint(numbers, i, k);

    // Recursively sort low partition (i to j) and
    // high partition (j + 1 to k)
    Quicksort_midpoint(numbers, i, j);
    Quicksort_midpoint(numbers, j + 1, k);
}

void Quicksort_medianOfThree(int numbers[], int i, int k)
{
    int j = 0;

    // Base case: If there are 1 or zero elements to sort,
    // partition is already sorted
    if (i >= k)
    {
        return;
    }

    // Partition the data within the array. Value j returned
    // from partitioning is location of last element in low partition.
    j = Partition_medianOfThree(numbers, i, k);

    // Recursively sort low partition (i to j) and
    // high partition (j + 1 to k)
    Quicksort_medianOfThree(numbers, i, j);
    Quicksort_medianOfThree(numbers, j + 1, k);
}

void InsertionSort(int numbers[], int numbersSize)
{
    for (int i = 1; i < numbersSize; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (numbers[j] < numbers[j - 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j - 1];
                numbers[j - 1] = temp;
            }
        }
    }
}

int genRandInt(int low, int high)
{
    return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[])
{
    for (int i = 0; i < NUMBERS_SIZE; ++i)
    {
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int Partition_midpoint(int *numbers, int i, int k)
{
    int l = 0;
    int h = 0;
    int midpoint = 0;
    int pivot = 0;
    int temp = 0;
    bool done = false;

    // Pick middle element as pivot
    midpoint = i + (k - i) / 2;
    pivot = numbers[midpoint];

    l = i;
    h = k;

    while (!done)
    {
        // Increment l while numbers[l] < pivot
        while (numbers[l] < pivot)
        {
            ++l;
        }

        // Decrement h while pivot < numbers[h]
        while (pivot < numbers[h])
        {
            --h;
        }

        // If there are zero or one elements remaining,
        // all numbers are partitioned. Return h
        if (l >= h)
        {
            done = true;
        }
        else
        {
            // Swap numbers[l] and numbers[h],
            // update l and h
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }

    return h;
}

int Partition_medianOfThree(int *numbers, int i, int k)
{
    int l = 0;
    int h = 0;
    int midpoint = 0;
    int pivot = 0;
    int temp = 0;
    bool done = false;

    // Pick median element as pivot
    midpoint = i + (k - i) / 2;

    if (numbers[midpoint] > numbers[i])
    {
        if (numbers[midpoint] > numbers[k]) // right most is median
        {
            pivot = numbers[k];
        }
        else // midpoint is median
        {
            pivot = numbers[midpoint];
        }
    }
    else
    {
        if (numbers[i] > numbers[k]) // right most is median
        {
            pivot = numbers[k];
        }
        else // left most is median
        {
            pivot = numbers[i];
        }
    }

    l = i;
    h = k;

    while (!done)
    {
        // Increment l while numbers[l] < pivot
        while (numbers[l] < pivot)
        {
            ++l;
        }

        // Decrement h while pivot < numbers[h]
        while (pivot < numbers[h])
        {
            --h;
        }

        // If there are zero or one elements remaining,
        // all numbers are partitioned. Return h
        if (l >= h)
        {
            done = true;
        }
        else
        {
            // Swap numbers[l] and numbers[h],
            // update l and h
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }

    return h;
}