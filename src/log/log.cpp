#include "log.h"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

#include "errors.h"

#ifndef FILEPATH
#define FILEPATH "."
#endif

void Log::write(std::ofstream& ofs, std::string str) {
  ofs << str;
  char null[1] = {0};
  ofs.write(null, 1);
}

void Log::commit(std::string key, std::string value) {
  std::ofstream file(std::string(FILEPATH).append(filename_),
                     std::ios::binary | std::ios::app);
  if (!file) {
    throw FileNotOpen();
  } else {
    write(file, key);
    write(file, value);
  }
  file.close();
}

char* Log::pull() {
  std::ifstream file(std::string(FILEPATH).append(filename_), std::ios::binary);
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

size_t Log::len() { return length_; }