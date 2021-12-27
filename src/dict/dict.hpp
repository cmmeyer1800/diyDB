#pragma once

#include <stdio.h>
#include <string.h>

#include <limits>
#include <string>

#include "hashtable.hpp"
#include "log.hpp"

namespace ds {

template <class V>
class Dict {
 private:
  robin_hood::unordered_map<std::string, V> table_;

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
          table_[temp] = d.v;
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
  Dict(bool build = false) : count_(0) {
    if (build) {
      rebuild();
    }
  }

  void insert(std::string key, V value) {
    if (count_ > std::numeric_limits<unsigned>::max()) {
      throw DictOverflow();
    } else {
      table_[key] = value;
      log_.commit(key, value);
      count_++;
    }
  }

  V find(std::string key) {
    if (!table_.contains(key)) {
      throw KeyNotFound();
    } else {
      return table_[key];
    }
  }

  void remove(std::string key) {
    if (!table_.contains(key)) {
      throw KeyNotFound();
    } else {
      table_.erase(key);
    }
  }

  void clearWAL() { remove("wal.bin"); }
};

};  // namespace ds