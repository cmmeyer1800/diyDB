#pragma once

#include <stdio.h>
#include <string.h>

#include <limits>
#include <string>

#include "hashtable.hpp"
#include "log.h"

namespace ds {

class Dict {
 private:
  robin_hood::unordered_map<std::string, std::string> table_;

  Log log_;

  std::string name_;

  void rebuild();

 public:

  Dict(std::string name, bool build = false) : name_(name), log_(name) {
    if (build) {
      rebuild();
    }
  }

  void insert(std::string key, std::string value);

  std::string find(std::string key);

  void remove(std::string key);

  void clearWAL();
};

};  // namespace ds