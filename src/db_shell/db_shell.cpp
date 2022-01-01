#include "db_shell.h"

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "database.h"

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
    if (words.size() != 2) {
      return false;
    } else {
      db_.create(words[1]);
    }
  }


  else if(first == "at"){
    if(words.size() != 3){
      std::cout << attr.red << attr.bold << "Error: Command Requires 3 Arguments" << attr.none << std::endl;
    }
    else{
      if(!db_.check(words[1])){
        std::cout << attr.red << attr.bold << "Error: Dict Not Found In Database" << attr.none << std::endl;
      }
      else{
        std::cout << db_.get(words[1]).find(words[2]) << std::endl;
      }
    }
  }


  else if(first == "set"){
    if(words.size() != 4){
      std::cout << attr.red << attr.bold << "Error: Command Requires 4 Arguments" << attr.none << std::endl;
    }
    else{
      if(!db_.check(words[1])){
        std::cout << attr.red << attr.bold << "Error: Dict Not Found In Database" << attr.none << std::endl;
      }
      else{
        db_.get(words[1]).insert(words[2], words[3]);
      }
    }
  }


  else if(first == "DELETE"){
    if(words.size() != 2){
      std::cout << attr.red << attr.bold << "Error: Command Requires 4 Arguments" << attr.none << std::endl;
    }
    else{
      if(!db_.check(words[1])){
        std::cout << attr.red << attr.bold << "Error: Dict Not Found In Database" << attr.none << std::endl;
      }
      else{
        db_.get(words[1]).clearWAL();
      }
    }

  
  } else {
    return false;
  }
  return true;
}