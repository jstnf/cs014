#include "IntSet.h"
#include "Student.h"

#include <iostream>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

int main(int argc,char* argv[1])
{
    if (argc < 2)
    {
        cerr << "Proper usage: " << argv[0] << " <input>." << endl;
        return 1;
    }

    ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        cerr << "Error: Unable to open \"" << argv[1] << "\"." << endl;
        return 1;
    }

    vector<Student*> students;
    string first_name,last_name;
    int sid;
    while(ifs>>first_name)
    {
        ifs >> last_name >> sid;
        students.push_back(new Student(first_name+" "+last_name,sid));
    }

    int unique_students = 0;
    int comparisons = 0;

    // Overall runtime complexity: O(n^2)
    // Overall space complexity: O(1)
    for (unsigned i = 0;i < students.size(); ++i) // O(n)
    {
        bool already_counted = false; // O(1)
        for (unsigned j = 0; j < i; ++j) // O(n) (eventually)
        {
            comparisons++; // O(1)
            if (*students.at(j) == *students.at(i)) // O(1)
            {
                already_counted = true; // O(1)
            }
        }

        if (!already_counted) { unique_students++; } // O(1)
    }

    cout << "Unique students: " << unique_students << endl;
    cout << "\tComparisons made: " << comparisons << endl;

    /* Insert solution here */
    IntSet idSet = IntSet();

    int set_comparisons = 0;

    // Overall runtime complexity: O(n)
    // Overall space complexity: O(n)
    for (unsigned i = 0; i < students.size(); ++i)
    {
        // Debug print
        // cout << "Inserting " << students.at(i)->name() << endl;

        idSet.insert(students.at(i)->sid()); // AVERAGE : O(1) <-> WORST : O(n)
        set_comparisons += idSet.comparisons(); // O(1)
    }

    cout << "Unique students: " << idSet.size() << endl;
    cout << "\tComparisons made: " << set_comparisons << endl;

//    cout << idSet << endl;

    return 0;
}