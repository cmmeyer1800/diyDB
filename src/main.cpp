#include <fstream>
#include <iostream>
#include <string>

#include "binary_conv.hpp"
#include "btree.hpp"
#include "dict.hpp"
#include "hash.h"
#include "log.hpp"

int main(int argc, char *argv[]) {
  ds::Dict<unsigned> t(true);
  std::cout << t["Timmothy"] << std::endl;
}