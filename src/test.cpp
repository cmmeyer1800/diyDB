#include "catch.hpp"
#include "btree.hpp"

TEST_CASE("Test BTree Implementation"){
    ds::BTree<unsigned, unsigned> test(10);
    ds::BTree<unsigned, unsigned>::Node * testNode = test.getRoot();
    REQUIRE(testNode->elems[0].val == 0);
    testNode->elems[0].val = 10;
    ds::BTree<unsigned, unsigned> test2(test);
    REQUIRE(test2.getRoot()->elems[0].val == testNode->elems[0].val);
}