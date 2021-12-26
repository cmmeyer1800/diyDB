#pragma once

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
    V t = V();
    size_t size = sizeof(t);
    bool inVal = false;
    std::string temp;
    size_t count = 0;

    char* memory = log_.pull();

    for (size_t i = 0; i <= log_.len(); i++) {
      if (inVal) {
        if (count >= size) {
          inVal = false;
          count = 0;
          // std::cout << temp << " , " << t << std::endl;
          tree_.insert(alg::hash(temp), t);
          temp.clear();
          i -= 1;
          continue;
        } else {
          t = t | (((unsigned)(memory[i])) << (8 * (size - count - 1)));
          count += 1;
        }
      } else {
        if (memory[i] != 0) {
          temp.append(1, memory[i]);
        } else {
          inVal = true;
          t = V();
          i += 1;
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