#include "btree.hpp"
#include "hash.h"
#include "dict.hpp"
#include "log.hpp"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char *argv[]){
  Log<unsigned> log;
  log.commit("Collin", 100);
  log.commit("Megan", 20);
  log.pull();
}