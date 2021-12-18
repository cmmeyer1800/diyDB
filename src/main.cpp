#include "btree.hpp"
#include "hash.h"
#include "dict.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int main(int argc, char *argv[]){
    ds::Dict<double> gpa;
    gpa.insert("Collin_Meyer", 3.72);
    std::cout << gpa["Collin_Meyer"];
    std::cout << gpa["test"];
}