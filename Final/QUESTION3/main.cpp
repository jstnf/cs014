#include "Patient.h"

#include <iostream>
#include <utility>

#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

// Describe any additional functions that are needed for part III

int main(int argc,char* argv[]) {
    if (argc < 2) {
        cerr << "Proper usage: " << argv[0] << " <patients_file>." << endl;
        return 1;
    }

    ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        cerr << "Error: Unable to open " << argv[1] << endl;
        return 1;
    }

    set<pair<int, int>> intake_times = set<pair<int, int>>();  // Part I, what data structure should be used here and why? (implement)
    // Sets will automatically order by the intake_time and provide a quick reference (pair) to the ID associated with it

    unordered_map<int, Patient*> patients = unordered_map<int, Patient*>(); // Part II, what data structure should be used here and why? (implement)
    // Maps allow you to associate a key with an object, which in this case is a Patient
    // The operations of a map, including lookup, are O(1) complexity, making maps optimal for large datasets like a patient database
    // The map is unordered as it does not necessarily need to be in any kind of sorting order, so an unordered_map would be an optimization over a standard map

    //set<pair<int, int>> patient_urgencies = set<pair<int, int>>(); // Part III, what data structure should be used here and why? (comments only)
    // Use a set because it avoids duplicates and can automatically sort by urgency, which is useful when listing out by urgency

    string first_name, last_name;
    int intake_time,urgency,id;

    // Overall runtime complexity: O(1)
    // Overall space complexity: O(1)
    while (ifs >> id) {
        ifs >> first_name >> last_name >> intake_time >> urgency; // O(1)
        Patient *patient_record = new Patient(id,first_name + " "s + last_name); // O(1)
        patient_record->urgency(urgency); // O(1)

        intake_times.insert(make_pair(intake_time,id)); // O(1)
        patients.insert(make_pair(id,patient_record)); // O(1)
        // patient_urgencies.insert(make_pair(urgency,patient_record)) // O(1)
    }

    // Output Patients sorted by oldest intake_time (smallest) to newest intake_time (largest) (Implement)
    cout << "Sorted by intake times: " << endl;
    auto it = intake_times.begin(); // O(1)
    while (it != intake_times.end()) // O(n)
    {
        cout << *patients.at(it->second) << endl; // O(1)
        it++; // O(1)
    }

    // Output Patients ID's sorted by most urgent to least urgent
    // In commenst describe how this would work.

    // You would create an iterator from the end of the patient_urgencies set
    // Afterwards, you would iterate backwards, which would effectively iterate from high to low
    // Print the patient itself (dereference the iterator) as you iterate

    return 0;
}
