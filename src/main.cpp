#include "btree.hpp"
#include "hash.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int main(int argc, char *argv[]){
    ds::BTree<unsigned, std::string> test(100);
    test.insert(alg::hash("test"), "sucess");
    test.insert(alg::hash("test"), "test");
    std::cout << test[alg::hash("test")];
}