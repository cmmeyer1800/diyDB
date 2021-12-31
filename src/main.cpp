#include <iostream>
#include <string>

#include "db_shell.h"
#include "hashtable.hpp"
#include "dict.h"

int main(int argc, char* argv[]){
  bool running = true;
  std::string buffer;
  DBShell shell;

  shell.printWelcome();
  
  while(running){
    std::cout << "~ DBShell $ ";
    
    std::string input = shell.getInput();
    int select = shell.parseInput(input);
    if(!select){
      std::cout << shell.attr.red << shell.attr.bold << "Error: Command Could Not Be Understood" << shell.attr.none << std::endl;
    }
  }
  return 0;
}