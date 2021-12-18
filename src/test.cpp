#include "catch.hpp"
#include "hash.h"
#include "btree.hpp"
#include <stdlib.h>
#include <limits.h>
#include <time.h>

TEST_CASE("Test BTree Implementation"){
    ds::BTree<unsigned, unsigned> test(10);
    test.insert(0, 100);
    REQUIRE(test[0] == 100);
}

TEST_CASE("Test Large BTree: UINT Key"){
    ds::BTree<unsigned, unsigned> test(100);
    unsigned spec;
    for(unsigned i = 0; i < 1000000; i++){
        spec = rand() % UINT_MAX;
        test.insert(i, spec);
    }
    REQUIRE(test[999999] == spec);
}

TEST_CASE("String Key BTree"){
    ds::BTree<unsigned, std::string> test(100);
    test.insert(alg::hash("test"), "success");

    SECTION("Find Missing Key"){
        REQUIRE(test[22] == std::string());
    }

    SECTION("Find On Small BTree"){
        REQUIRE(test.find(alg::hash("test")) == "success");
    }

    SECTION("Find On Large BTree"){
        for(size_t i = 0; i < 100000; i++){
            if(i == 5000){
                test.insert(i, "blah");
            }
            else{
                test.insert(i, "test");
            }
        }
        REQUIRE(test[5000] == "blah");
    }
}