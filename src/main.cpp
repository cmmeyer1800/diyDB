#include "main.h"
#include "btree.h"
#include <iostream>

int main(){
    BTree<int, std::string> test;
    test.insert(5, "collin");
    return 0;
}