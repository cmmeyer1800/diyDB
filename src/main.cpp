#include <iostream>
#include <string>
#include <chrono>

#include "db_shell.h"
#include "hashtable.hpp"
#include "dict.h"
#include "database.h"

std::string random_string( size_t length )
{
  auto randchar = []() -> char
  {
    const char charset[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (sizeof(charset) - 1);
    return charset[ rand() % max_index ];
  };
  std::string str(length,0);
  std::generate_n( str.begin(), length, randchar );
  return str;
}

int main(int argc, char* argv[]){
  if(argc < 2){
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
  }
  else{
    if(!strcmp(argv[1], "-s")){
      size_t upper = std::stoi(argv[2]);
      Database db;
      db.create("SpeedTest");
      auto start = std::chrono::high_resolution_clock::now();
      for(size_t idx = 0; idx < upper; idx++){
        db.get("SpeedTest").insert(random_string(10), "blah blah blah");
      }
      auto end = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
      std::cout << duration.count()/upper;
    }
    else{
      return 1;
    }
  }
  return 0;
}