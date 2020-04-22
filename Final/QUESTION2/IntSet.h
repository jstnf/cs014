#ifndef __INTSET_H_
#define __INTSET_H_

#include <fstream>

class IntSet
{
    enum Status { Empty_since_start, Empty, Occupied };

    struct setRecord
    {
        int value;
        Status status = Empty_since_start;
    };

    friend std::ostream& operator<<(std::ostream&,const IntSet&);
  private:
    int _comparisons = 0;
    size_t _size = 0;
    size_t _capacity;
    setRecord *_table;

  public:
    IntSet(); // Default capacity is 1
    explicit IntSet(int n); // Set the capacity to n
    IntSet(const IntSet &);
    ~IntSet() { delete[] _table; };

    void insert(int); // Insert the element into the set
    void erase(int); // Erase the element from the set if it exists
    void rehash(size_t);

    int comparisons(); // Returns the number of comparisons from the last operation performed
    size_t size() const; // Returns the size
    size_t capacity() const; // Returns the capacity
    bool empty() const;
    int count(int); // Returns 1 if the key passed in exists in the set and 0 otherwise.

  private:
    int probe(int) const; // Return the next free index based on the passed in index
    int hash(int,int=0) const;
    int hash_map(int) const;
    int compression_map(int) const;
};

#endif // __INTSET_H_
