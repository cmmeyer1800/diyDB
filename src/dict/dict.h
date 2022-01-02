#pragma once

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <limits>
#include <string>

#include "hashtable.hpp"
#include "log.h"

#ifndef FILEPATH
#define FILEPATH "."
#endif

namespace ds {

class Dict {
 private:
  robin_hood::unordered_map<std::string, std::string> table_;

  Log log_;

  std::string name_;

  std::string filename_;

  void rebuild();

 public:
  Dict(std::string name)
      : name_(name), log_(std::string(FILEPATH).append(name).append(".wal")) {
    filename_ = std::string(FILEPATH).append(name).append(".wal");
  }

  Dict(std::string name, std::string filename)
      : name_(name), log_(filename), filename_(filename) {
    rebuild();
  }

  void insert(std::string key, std::string value);

  std::string find(std::string key);

  void remove(std::string key);

  std::string getName() { return name_; }

  void clearWAL();
};

};  // namespace ds