#include <iostream>
#include <sstream>
#include <cassert>

#include "set.hpp"


// Här i test.cpp så ska jag inte implementera något utan endast testa det som görs i set.cpp


int main() {
    /******************************************************
     * TEST PHASE 0                                       *
     * Default constructor                                *
     * constructor: int -> Set                            *
     * destructor: ~Set()                                 *
     * empty, operator<<                                  *
     ******************************************************/
    std::cout << "TEST PHASE 0: default constructor and constructor int -> Set\n";
    std::cout << "TEST PHASE 0: destructor\n";
    std::cout << "TEST PHASE 0: cardinality and empty\n";

    {
        Set S1{};
        assert(Set::get_count_nodes() == 1);

        assert(S1.cardinality() == 0);
        assert(S1.empty());

        Set S2{-5};
        assert(Set::get_count_nodes() == 3);

        assert(S2.cardinality() == 1);
        assert(!S2.empty());

        // Test
        std::ostringstream os{};
        os << S1 << " " << S2;

        std::string tmp{os.str()};
        assert((tmp == std::string{"Set is empty! { -5 }"}));
    }

    assert(Set::get_count_nodes() == 0);

    /******************************************************
     * TEST PHASE 1                                       *
     * Constructor: create a Set from a non-sorted vector *
     ******************************************************/
    std::cout << "\nTEST PHASE 1: constructor from a vector\n";
    std::cout << "TEST PHASE 1: cardinality and empty\n";

    {
        std::vector<int> A1{5, 3, 1};
        std::vector<int> A2{4, 3, 4, 20, 15};  // note the non-unique values

        Set S1{A1};
        assert(Set::get_count_nodes() == 4);

        assert(S1.cardinality() == 3);
        assert(!S1.empty());

        Set S2{A2};
        assert(Set::get_count_nodes() == 9);

        assert(S2.cardinality() == 4);
        assert(!S2.empty());

        // Test
        std::ostringstream os{};
        os << S1 << " " << S2;

        std::string tmp{os.str()};
        assert((tmp == std::string{"{ 1 3 5 } { 3 4 15 20 }"}));
    }

    assert(Set::get_count_nodes() == 0);

    /******************************************************
     * TEST PHASE 2                                       *
     * Copy constructor                                   *
     ******************************************************/
    std::cout << "\nTEST PHASE 2: copy constructor\n";

    {
        std::vector<int> A1{3, 3, 5, 1};

        Set S1{A1};
        assert(Set::get_count_nodes() == 4);

        Set S2{S1};
        assert(Set::get_count_nodes() == 8);

        assert(S1.cardinality() == S2.cardinality());

        // Test
        std::ostringstream os{};
        os << S1 << " " << S2;

        std::string tmp{os.str()};
        assert((tmp == std::string{"{ 1 3 5 } { 1 3 5 }"}));
    }

    assert(Set::get_count_nodes() == 0);

    /******************************************************
     * TEST PHASE 3                                       *
     * Assignment operator: operator=                     *
     ******************************************************/
    std::cout << "\nTEST PHASE 3: operator=\n";

    {
        Set S1{};

        assert(Set::get_count_nodes() == 1);

        std::vector<int> A1{1, 3, 5};
        Set S2{A1};
        assert(Set::get_count_nodes() == 5);

        std::vector<int> A2{3, 8, 2, -1};
        Set S3{A2};
        assert(Set::get_count_nodes() == 10);

        S1 = S2 = S3;
        assert(Set::get_count_nodes() == 15);
        assert(S1.cardinality() == S2.cardinality());
        assert(S2.cardinality() == S3.cardinality());

        // Test
        std::ostringstream os1{};
        os1 << S1 << " " << S2 << " " << S3;

        std::string tmp1{os1.str()};
        assert((tmp1 == std::string{"{ -1 2 3 8 } { -1 2 3 8 } { -1 2 3 8 }"}));

        S1 = Set{};
        assert(Set::get_count_nodes() == 11);
        assert(S1.empty());

        // Test
        std::ostringstream os2{};
        os2 << S1;

        std::string tmp2{os2.str()};
        assert((tmp2 == std::string{"Set is empty!"}));
    }

    assert(Set::get_count_nodes() == 0);

    /******************************************************
     * TEST PHASE 4                                       *
     * member                                             *
     ******************************************************/
    std::cout << "\nTEST PHASE 4: member\n";

    {
        std::vector<int> A1{5, 1, 3, 1};
        Set S1{A1};
        assert(Set::get_count_nodes() == 4);

        assert(S1.cardinality() == 3);

        // Test
        assert(S1.member(1));
        assert(S1.member(2) == false);
        assert(S1.member(3));
        assert(S1.member(5));
        assert(S1.member(99999) == false);
    }

    assert(Set::get_count_nodes() == 0);

    /*****************************************************
     * TEST PHASE 5                                       *
     * Subset                                             *
     ******************************************************/
    std::cout << "\nTEST PHASE 5: is_subset\n";

    {
        std::vector<int> A1{8, 3, 5, 1, 3};
        Set S1{A1};

        assert(Set::get_count_nodes() == 5);

        assert(S1.cardinality() == 4);

        std::vector<int> A2{3, 5};
        Set S2{A2};
        assert(Set::get_count_nodes() == 8);

        assert(S2.cardinality() == 2);

        // Test
        assert(S2.is_subset(S1));
        assert(S1.is_subset(S2) == false);
        assert(S1.is_subset(S1));

        assert(Set{}.is_subset(S1));
        assert(S1.is_subset(Set{}) == false);

        std::vector<int> A3{10, 3, 5, 8};
        assert((Set{A3}.is_subset(S2)) == false);
    }

    assert(Set::get_count_nodes() == 0);

    /******************************************************
     * TEST PHASE 6                                       *
     * union                                              *
     ******************************************************/
    std::cout << "\nTEST PHASE 6: union\n";

    {
        std::vector<int> A1{5, 3, 1, 8, 1};
        Set S1{A1};
        assert(Set::get_count_nodes() == 5);

        std::vector<int> A2{2, 7, 3};
        Set S2{A2};
        assert(Set::get_count_nodes() == 9);

        Set S3{};
        assert(Set::get_count_nodes() == 10);

        S3 = S1.set_union(S2);
        assert(Set::get_count_nodes() == 16);

        assert(S3.cardinality() == 6);

        // test
        std::vector<int> A3{1, 2, 3, 5, 7, 8};
        assert(S3.is_subset(Set{A3}) and Set{A3}.is_subset(S3));  // S3 == {1, 2, 3, 5, 7, 8}
        assert(Set::get_count_nodes() == 16);

        S3 = Set{}.set_union(S1).set_union(Set{});
        assert(Set::get_count_nodes() == 14);
        assert(S1.is_subset(S3) and S3.is_subset(S1));  // S1 == S3

        Set S5{S1.set_union(S1)};
        assert(S5.is_subset(S1) and S1.is_subset(S5));  // S1 == S5
    }

    assert(Set::get_count_nodes() == 0);

    /******************************************************
     * TEST PHASE 7                                       *
     * intersection                                       *
     ******************************************************/
    std::cout << "\nTEST PHASE 7: set_intersection\n";

    {
        std::vector<int> A1{5, 3, 1, 8, 1};
        Set S1{A1};
        assert(Set::get_count_nodes() == 5);

        std::vector<int> A2{2, 7, 3};
        Set S2{A2};
        assert(Set::get_count_nodes() == 9);

        Set S3{S1.set_intersection(S2)};
        assert(Set::get_count_nodes() == 11);

        assert(S3.cardinality() == 1);

        // test
        std::vector<int> A3{3};
        assert(S3.is_subset(Set{A3}) and Set{A3}.is_subset(S3));  // S3 == {3}

        Set S4{Set{}.set_intersection(S1)};
        assert(S4.empty());  // S4 == {}
    }

    assert(Set::get_count_nodes() == 0);

    /******************************************************
     * TEST PHASE 8                                       *
     * difference                                         *
     ******************************************************/
    std::cout << "\nTEST PHASE 8: difference\n";

    {
        std::vector<int> A1{5, 3, 1, 8, 1};
        Set S1{A1};
        assert(Set::get_count_nodes() == 5);

        std::vector<int> A2{2, 7, 3};
        Set S2{A2};
        assert(Set::get_count_nodes() == 9);

        Set S3 = S1.set_difference(S2);
        assert(Set::get_count_nodes() == 13);

        assert(S3.cardinality() == 3);

        // test
        std::vector<int> A3{1, 5, 8};
        assert(S3.is_subset(Set{A3}) and Set{A3}.is_subset(S3));  // S3 == {1, 5, 8}

        Set S4{S1.set_difference(Set{})};
        assert(S4.is_subset(S1) and S1.is_subset(S4));  // S1 == S4

        Set S5{S1.set_difference(S1)};
        assert(S5.empty());  // S5 == {}
    }

    assert(Set::get_count_nodes() == 0);

    /******************************************************
     * TEST PHASE 9                                      *
     * union, intersection, and difference               *
     ******************************************************/
    std::cout << "\nTEST PHASE 9: union, intersection, and difference\n";

    {
        std::vector<int> A1{1, 3, 5};
        std::vector<int> A2{3, 2, 4};
        std::vector<int> A3{10, 3};

        Set S1{A1};
        Set S2{A2};
        Set S3{A3};
        assert(Set::get_count_nodes() == 11);

        S3 = S1.set_difference(S1.set_union(S2));
        assert(Set::get_count_nodes() == 9);

        // test
        assert(S3.empty());  // S3 == {}

        S3 = S2.set_difference(Set{2}).set_intersection(S1.set_union(S3));
        assert(Set::get_count_nodes() == 10);

        // test
        assert(S3.is_subset(Set{3}) and Set{3}.is_subset(S3));  // S3 == {3}
    }

    assert(Set::get_count_nodes() == 0);
    std::cout << "\nSuccess!!\n";
}
