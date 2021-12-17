#include "catch.hpp"
#include "btree.hpp"
#include <stdlib.h>
#include <limits.h>
#include <time.h>

TEST_CASE("Test BTree Implementation"){
    ds::BTree<unsigned, unsigned> test(10);
    test.insert(0, 100);
    REQUIRE(test[0] == 100);
}

TEST_CASE("Test Large BTree"){
    ds::BTree<unsigned, unsigned> test(100);
    unsigned spec;
    for(unsigned i = 0; i < 1000000; i++){
        spec = rand() % UINT_MAX;
        test.insert(i, spec);
    }
    REQUIRE(test[999999] == spec);
}