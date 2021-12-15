#include "catch.hpp"
#include "btree.hpp"

TEST_CASE("Test BTree Implementation"){
    ds::BTree<unsigned, unsigned> test(10);
    ds::BTree<unsigned, unsigned>::Node * testNode = test.getRoot();
    REQUIRE(testNode->elems[0].val == 0);
}