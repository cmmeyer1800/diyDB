#include "dict.h"

#include <stdio.h>

#include <iostream>
#include <limits>
#include <string>

#include "errors.h"
#include "hashtable.hpp"
#include "log.h"

void ds::Dict::rebuild() {
  std::string buffer;
  std::string key;
  char* memory = log_.pull();
  bool complete = false;

  for (size_t i = 0; i < log_.len(); i++) {
    if (memory[i] == 0) {
      if (complete) {
        table_[key] = buffer;
        key.clear();
        complete = false;
      } else {
        key = buffer;
        complete = true;
      }
      buffer.clear();
    } else {
      buffer.append(1, memory[i]);
    }
  }

  delete[] memory;
}

void ds::Dict::insert(std::string key, std::string value) {
  table_[key] = value;
  log_.commit(key, value);
}

std::string ds::Dict::find(std::string key) { return table_[key]; }

void ds::Dict::remove(std::string key) {
  if (!table_.contains(key)) {
    throw KeyNotFound();
  } else {
    table_.erase(key);
  }
}

void ds::Dict::clearWAL() { ::remove(name_.append(".wal").c_str()); }