#pragma once

#include <cstddef>
#include <fstream>
#include <string>

class Log {
 private:
  std::string filename_;

  size_t length_;

  void write(std::ofstream& ofs, std::string val);

 public:
  Log(std::string name) : filename_(name), length_(0) {
    filename_.append(".wal");
  }

  void commit(std::string key, std::string value);

  char* pull();

  size_t len();
};