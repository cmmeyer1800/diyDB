#pragma once

#include "dict.h"

#include <map>
#include <vector>

class Database {
 private:
   std::vector<ds::Dict> dicts_;
   std::map<std::string, unsigned> locs_;

 public:
  Database() : size_(0) {}

<<<<<<< HEAD
  template <class T>
  void create(std::string name) {
    std::tuple<ds::Dict<T>> dict;
    dictionaries_ = std::tuple_cat(dictionaries_, dict);
    assign_[name] = size_;
    size_++;
  }
=======
  Database();

   void create(std::string name);

   void recreate(std::string name);

   ds::Dict & get(std::string name);

  bool check(std::string name);
    
>>>>>>> strings
};