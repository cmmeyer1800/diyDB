#include "btree.hpp"
#include "hash.h"
#include "dict.hpp"
#include "log.hpp"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char *argv[]){
  // ds::Dict<unsigned> d;
  // d.insert("Collin", 100);

  ds::Dict<unsigned> t(true);
  std::cout << t["Collin"];
}