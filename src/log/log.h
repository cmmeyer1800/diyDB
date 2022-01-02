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
  Log(std::string filename) : filename_(filename), length_(0) {}

  void commit(std::string key, std::string value);

  char* pull();

  size_t len();
};