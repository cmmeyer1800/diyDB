#pragma once

#include <string.h>

#include <limits>
#include <string>

#include "btree.hpp"
#include "hash.h"
#include "log.hpp"

namespace ds {

template <class V>
class Dict {
 private:
  BTree<unsigned, V> tree_;

  Log<V> log_;

  unsigned count_;

  void rebuild() {
    V tr;
    size_t size = sizeof(tr);
    char t[size];
    bool inVal = false;
    std::string temp;
    size_t count = 0;

    char* memory = log_.pull();

    for (size_t i = 0; i <= log_.len(); i++) {
      if (inVal) {
        if (count >= size) {
          inVal = false;
          count = 0;
          DSet<V> d;
          strcpy(d.c, t);
          tree_.insert(alg::hash(temp), d.v);
          temp.clear();
          i -= 1;
          continue;
        } else {
          t[count] = memory[i];
          count++;
        }
      } else {
        if (memory[i] != 0) {
          temp.append(1, memory[i]);
        } else {
          inVal = true;
        }
      }
    }
    delete[] memory;
  }

 public:
  Dict(bool build = false) : tree_(100), count_(0) {
    if (build) {
      rebuild();
    }
  }

  void insert(std::string key, V value) {
    if (count_ > std::numeric_limits<unsigned>::max()) {
      throw DictOverflow();
    } else {
      tree_.insert(alg::hash(key), value);
      log_.commit(key, value);
      count_++;
    }
  }

  V operator[](std::string key) { return tree_.find(alg::hash(key)); }
};

};  // namespace ds