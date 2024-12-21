#pragma once

#include <iostream>
#include <vector>
#include <cassert>  //assert

// Class Set represents a set of integers using an increasingly sorted singly-linked list
class Set {
public:
    // Default constructor
    Set();

    // Constructor: create a singleton {x}
    explicit Set(int x);

    // Constructor: create a set with elements
    // elements is not sorted and values in it may not be unique
    explicit Set(const std::vector<int>& elements);

    // Copy constructor
    Set(const Set& rhs);

    // Assignment operator
    Set& operator=(Set rhs);

    // Destructor
    ~Set();

    bool member(int x) const;         // Test if x is an element of the set
    bool empty() const;               // Test if set is empty
    std::size_t cardinality() const;  // Return number of elements in the set

    // Return true, if *this is a subset of Set b
    // Otherwise, false is returned
    bool is_subset(const Set& b) const;

    // Return a new Set representing the union of Sets *this and b
    Set set_union(const Set& b) const;

    // Return a new Set representing the intersection of Sets *this and b
    Set set_intersection(const Set& b) const;

    // Return a new Set representing the difference between Set *this and Set b
    Set set_difference(const Set& b) const;

    // Return number of existing nodes
    // Used only for debug purposes
    static std::size_t get_count_nodes();

private:
    class Node;  // class Node definition is in set.cpp

    Node* head;  // points to the first node
                 // Note: first node is a dummy node of the list

    std::size_t counter;  // number of elements in the Set

    friend std::ostream& operator<<(std::ostream& os, const Set& rhs);

    /* Add Auxiliarly functions, if needed */

    void SortInsert(int x);  //Sorteringsfunktion
    void insert(Node* p, int value);  // Funktion för att skapa noder
    void remove(Node* p);            // Funktion för att ta bort noder

};
