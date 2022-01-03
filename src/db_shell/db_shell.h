#pragma once

#include <dict.h>

#include <map>
#include <string>

#include "database.h"

#define HELP_MESSAGE \
  "\
Welcome to diyDB Shell Help\n\
Commands for Database Interaction\n\
quit:\n\
  \tUsage: quit or q or exit\n\
  \tAction: terminates shell execution\n\
clear:\n\
  \tUsage: clear\n\
  \tAction: clears the terminal while in shell\n\
CREATE:\n\
  \tUsage: CREATE DictionaryName\n\
  \tAction: creates a new dictionary with name DictionaryName that can be used to store key value pairs\n\
SET:\n\
  \tUsage: SET DictionaryName Key Value\n\
  \tAction: sets the Key to Value for database DictionaryName\n\
GET:\n\
  \tUsage: GET DictionaryName Key\n\
  \tAction: outputs the value at Key in DictionaryName\n\
LIST:\n\
  \tUsage: LIST\n\
  \tAction: outputs the names of all the dictionaries in the database\n\
"

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