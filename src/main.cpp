#include "btree.hpp"
#include "hash.h"
#include "dict.hpp"
#include "log.hpp"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char *argv[]){
  ds::Dict<unsigned> t(true);
  // t.insert("test", 123);
  // t.insert("test2", 321);
  std::cout << t["test"] << std::endl;
}