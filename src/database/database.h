#pragma once

#include <map>
#include <vector>

#include "dict.h"

class Database {
 private:
  std::vector<ds::Dict> dicts_;
  std::map<std::string, unsigned> locs_;

 public:
  Database();

  void create(std::string name);

  void recreate(std::string name);

  ds::Dict& get(std::string name);

  std::vector<std::string> getDicts();

  bool check(std::string name);
};