#pragma once

#include <string>
#include <map>
#include <dict.hpp>

#include "database.h"

class DBShell {

 private:

  Database db_;  

 public:

  struct {
    const std::string none = "\e[0m";
    const std::string bold = "\e[1m";
    const std::string dim = "\e[2m";
    const std::string underline = "\e[4m";
    const std::string blink = "\e[5m";
    const std::string inv = "\e[7m";
    const std::string black = "\e[30m";
    const std::string red = "\e[31m";
    const std::string green = "\e[32m";
    const std::string yellow = "\e[33m";
    const std::string blue = "\e[34m";
    const std::string magenta = "\e[35m";
    const std::string cyan = "\e[36m";
    const std::string lgray = "\e[37m";
    const std::string dgray = "\e[90m";
  } attr;

  void printWelcome();

  std::string getInput();

  int parseInput(std::string input);
};