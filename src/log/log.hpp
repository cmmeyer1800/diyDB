#pragma once

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

#include "binary_conv.hpp"
#include "errors.h"

#define LOGFILENAME "wal.bin"

template <class V>
class Log {
 private:
  std::string filename;

  size_t length_;

  void write(std::ofstream& ofs, std::string key) {
    ofs << key;
    char null[1] = {0};
    ofs.write(null, 1);
  }

  void write(std::ofstream& ofs, V value) {
    DSet<V> ds = {value};
    ofs.write(ds.c, sizeof(ds.c));
  }

 public:
  Log() : filename(LOGFILENAME), length_(0) {}

  void commit(std::string key, V value) {
    std::ofstream file(filename, std::ios::binary | std::ios::app);
    if (!file) {
      throw FileNotOpen();
    } else {
      write(file, key);
      write(file, value);
    }
    file.close();
  }

  char* pull() {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
      throw FileNotOpen();
      return NULL;
    } else {
      file.seekg(0, file.end);
      unsigned length = file.tellg();
      length_ = length;
      file.seekg(0, file.beg);
      char* buffer = new char[length];
      file.read(buffer, length);
      file.close();
      return buffer;
    }
    return NULL;
  }

  size_t len() { return length_; }
};