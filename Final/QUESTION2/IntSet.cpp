#include "IntSet.h"

#include <iostream> // For testing

// Testing
using std::cout;
using std::endl;

IntSet::IntSet()
{
    _capacity = 1;
    _table = new setRecord[1];
}

IntSet::IntSet(int n)
{
    _capacity = n;
    _table = new setRecord[n];
}

IntSet::IntSet(const IntSet &sourceTable)
{
    _capacity = sourceTable._capacity;
    _size = sourceTable._size;
    _table = new setRecord[sourceTable._capacity];
    for (unsigned i = 0; i < _capacity; i++)
    {
        _table[i].status = sourceTable._table[i].status;
        _table[i].value = sourceTable._table[i].value;
    }
}

void IntSet::insert(int key)
{
    // Optimization, check for key first
    if (count(key) == 1) // O(1)
    {
        // Comparisons are already set
        _comparisons++; // This if statement
        return;
    }

    // Tracked function, we will reset comparison count later
    int funComparisons = 1; // Already 1 for size check // O(1)

    if (_size + 1 > _capacity * 0.67) // O(1)
    {
        // Debug print
        // cout << "We're doing some rehashing..." << endl;

        // Do some rehashing
        rehash(_capacity * 3); // O(n)
        funComparisons += _comparisons; // O(1)

        // Debug print
        // cout << "We finished rehashing!" << endl;
    }

    int currIndex = hash(key, _capacity); // O(1)
    setRecord* record = _table + currIndex; // O(1)

    funComparisons++; // O(1)
    while (record->status == Occupied) // O(1) - O(n) : Depends on probe, but should be const, O(n) at worst case scenario
    {
        // Debug print
        // cout << "COLLISION! (+1 comparison)" << endl;
        currIndex = (currIndex + 1) % static_cast<int>(_capacity); // O(1)
        record = _table + currIndex; // O(1)
        funComparisons++; // O(1)
    }

    record->value = key; // O(1)
    record->status = Occupied; // O(1)
    _size++; // O(1)

    // Reset comparison count
    _comparisons = funComparisons; // O(1)
}

void IntSet::erase(int key)
{
    // If you manage to hit every single value
    // (i.e. every value in _table is Empty and not Empty_since_start)
    // this will infinitely loop...

    // Empty optimization
    if (empty())
    {
        _comparisons = 1;
        return;
    }

    // Tracked function, we will reset comparison count later
    int funComparisons = 1; // 1 from empty check

    int currIndex = hash(key, _capacity);
    setRecord* record = _table + currIndex;
    while (record->status != Empty_since_start)
    {
        funComparisons++;
        if (record->status == Occupied && record->value == key)
        {
            record->status = Empty;
            _size--;
        }
        else
        {
            currIndex = (currIndex + 1) % static_cast<int>(_capacity);
            record = _table + currIndex;
        }
    }

    // Reset comparison count
    _comparisons = funComparisons;
}

void IntSet::rehash(size_t newCapacity)
{
    // Empty optimization
    if (empty()) // O(1)
    {
        delete[] _table; // O(1)
        _table = new setRecord[newCapacity]; // O(1)
        _capacity = newCapacity; // O(1)
        _comparisons = 1; // O(1)
    }

    // Tracked function, we will reset comparison count later
    int funComparisons = 1; // 1 from empty check // O(1)

    setRecord* newTable = new setRecord[newCapacity]; // O(1)
    for (unsigned i = 0; i < _capacity; i++) // O(n)
    {
        funComparisons++; // O(1)
        if (_table[i].status == Occupied) // O(1)
        {
            // Debug print
            // cout << "Rehashing " << _table[i].value << " into our new table..." << endl;

            // We need to hash the value into the new table
            int newTableHash = hash(_table[i].value, newCapacity); // O(1)

            // Is this a comparison in the rehash????
            funComparisons++; // O(1)
            while (newTable[newTableHash].status == Occupied) // O(1) - O(n) depending on hash function, lean more towards O(1)
            {
                funComparisons++; // O(1)
                newTableHash = (newTableHash + 1) % static_cast<int>(newCapacity); // O(1)
            }

            // Debug print
            // cout << "Inserting into the new table at hash value " << newTableHash << ". capacity(" << newCapacity << ")" << endl;

            newTable[newTableHash].status = Occupied; // O(1)
            newTable[newTableHash].value = _table[i].value; // O(1)
        }
    }

    delete[] _table; // O(1)
    _table = newTable; // O(1)
    _capacity = newCapacity; // O(1)

    // Reset comparison count
    _comparisons = funComparisons; // O(1)
}

int IntSet::comparisons()
{
    return _comparisons;
}

size_t IntSet::size() const
{
    return _size;
}

size_t IntSet::capacity() const
{
    return _capacity;
}

bool IntSet::empty() const
{
    return _size == 0;
}

int IntSet::count(int key)
{
    // Empty optimization
    if (empty())
    {
        _comparisons = 1;
        return 0;
    }

    // Tracked function, we will reset comparison count later
    int funComparisons = 0;

    int currIndex = hash(key, _capacity);
    setRecord record = _table[currIndex];
    while (record.status != Empty_since_start)
    {
        funComparisons++;
        if (record.status == Occupied && record.value == key)
        {
            _comparisons = funComparisons;
            return 1;
        }
        else
        {
            currIndex = (currIndex + 1) % static_cast<int>(_capacity);
            record = _table[currIndex];
        }
    }

    _comparisons = funComparisons;
    return 0;
}

int IntSet::probe(int index) const
{
    int currIndex = index;
    while (!(_table[currIndex].status == Empty || _table[currIndex].status == Empty_since_start))
    {
        currIndex = (currIndex + 1) % static_cast<int>(_capacity);
    }

    return currIndex;
}

int IntSet::hash(int key, int cap) const
{
    int hash = hash_map(key);
    hash = compression_map(hash);

    return hash % cap;
}

int IntSet::hash_map(int key) const
{
    return (key / 6) + (key);
}

int IntSet::compression_map(int hash) const
{
    return hash < 0 ? hash * -1 : hash;
}

std::ostream &operator<<(std::ostream &out, const IntSet &intSet)
{
    for (unsigned i = 0; i < intSet._capacity; ++i)
    {
        if (intSet._table[i].status == intSet.Occupied)
        {
            cout << "[" << i << "] " << intSet._table[i].value << endl;
        }
    }

    return out;
}
