#include "db_shell.h"

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

void DBShell::printWelcome() {
  std::cout << attr.bold << "Welcome to the DiyDB shell\n"
            << attr.none << "Enter help for usage details" << std::endl;
}

std::string DBShell::getInput() {
  std::string ret;
  std::getline(std::cin, ret);
  return ret;
}

int DBShell::parseInput(std::string input) {
  std::vector<std::string> words;
  std::istringstream ss;
  ss.str(input.c_str());
  for (std::string word; std::getline(ss, word, ' ');) {
    words.push_back(word);
  }

  if (words.size() < 1) {
    return false;
  }

  std::string first = words[0];

  if (first == "q" || first == "quit" || first == "exit") {
    exit(0);
  } else if (first == "clear") {
    std::cout << "\033c";
  } else if (first == "create") {
    if (words.size() != 3) {
      return false;
    } else {
    }
  } else {
    return false;
  }
  return true;
}