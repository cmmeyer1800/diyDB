#pragma once

#include "dict.h"

#include <map>
#include <vector>

class Database {
 private:
   std::vector<ds::Dict> dicts_;
   std::map<std::string, unsigned> locs_;

 public:

   void create(std::string name);

   ds::Dict & get(std::string name);

  bool check(std::string name);
    
};