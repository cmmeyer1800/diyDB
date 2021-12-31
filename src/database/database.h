#pragma once

#include <map>
#include <tuple>

#include "dict.hpp"

class Database {
 private:
  std::map<std::string, unsigned> assign_;
  std::tuple<> dictionaries_;
  unsigned size_;

 public:
  Database() : size_(0) {}

  template <class T>
  void create(std::string name) {
    std::tuple<ds::Dict<T>> dict;
    dictionaries_ = std::tuple_cat(dictionaries_, dict);
    assign_[name] = size_;
    size_++;
  }
};