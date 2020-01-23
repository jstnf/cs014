#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::out_of_range;
using std::string;
using std::vector;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index);
template<typename T>
void selection_sort(vector<T> &vals);
template<typename T>
void print_vector(vector<T> &vals);
template<typename T>
T getElement(vector<T> vals, int index);

// Given code (Part B)
vector<char> createVector()
{
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main()
{
    vector<int>* intVector = new vector<int>();
    intVector->push_back(9);
    intVector->push_back(333);
    intVector->push_back(7);
    intVector->push_back(10);
    intVector->push_back(42);

    selection_sort(*intVector);
    print_vector(*intVector);

    vector<char>* charVector = new vector<char>();
    charVector->push_back('a');
    charVector->push_back('w');
    charVector->push_back('1');
    charVector->push_back('*');
    charVector->push_back('A');

    selection_sort(*charVector);
    print_vector(*charVector);

    vector<string>* stringVector = new vector<string>();
    stringVector->push_back("bananas");
    stringVector->push_back("apple");
    stringVector->push_back("watermelon");
    stringVector->push_back("kiwi");
    stringVector->push_back("Apple");

    selection_sort(*stringVector);
    print_vector(*stringVector);

    // Part B
    try
    {
        srand(time(0));
        vector<char> vals = createVector();
        char curChar;
        int index;
        int numOfRuns = 10;
        while(--numOfRuns >= 0){
            cout << "Enter a number: " << endl;
            cin >> index;
            curChar = getElement(vals, index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
    }
    catch (out_of_range& excpt)
    {
        cout << excpt.what() << endl;
    }

    return 0;
}

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index)
{
    unsigned minIndex = index;

    for (unsigned i = index + 1; i < vals.size(); ++i)
    {
        if (vals.at(minIndex) > vals.at(i))
        {
            minIndex = i;
        }
    }

    return minIndex;
}

template<typename T>
void selection_sort(vector<T> &vals)
{
    for (unsigned i = 0; i + 1 < vals.size(); ++i)
    {
        unsigned minIndex = min_index(vals, i);
        T temp = vals.at(i);
        vals.at(i) = vals.at(minIndex);
        vals.at(minIndex) = temp;
    }
}

template<typename T>
void print_vector(vector<T> &vals)
{
    for (unsigned i = 0; i < vals.size(); ++i)
    {
        cout << vals.at(i) << " ";
    }
    cout << endl;
}

template<typename T>
T getElement(vector<T> vals, int index)
{
    unsigned comp = index; // Compare vals.size() to unsigned int to avoid warning
    if (index < 0 || comp >= vals.size())
    {
        throw out_of_range("out of range exception occured");
    }

    return vals.at(index);
}