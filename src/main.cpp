#include "btree.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int main(int argc, char *argv[]){
    if(argc == 1){
        std::cout << "\e[31m" << "Error:" << "\e[0m" << " No input parameters given" << std::endl;
        exit(1);
    }
    ds::BTree<int, int> test(100);
    size_t size = std::stoi(std::string(argv[1]));
    for(unsigned i = 0; i < size; i++){
        test.insert(i, rand() % INT_MAX);
    }
}