#include "btree.hpp"
#include "hash.h"
#include "dict.hpp"
#include <iostream>
#include <string>
#include <limits.h>
#include <fstream>

using namespace std;

void write(){
    char * num = (char * )unsigned(89);
    ofstream file("file.bin", ios::out | ios::binary);
    file.write(num, sizeof(num));
    file.close();
}


void read () {

  std::ifstream is ("file.bin", std::ifstream::binary);
  if (is) {
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    char * buffer = new char [length];

    std::cout << "Reading " << length << " characters... " << std::endl;
    // read data as a block:
    is.read (buffer,length);

    std::cout << buffer << std::endl;

    if (is)
      std::cout << "all characters read successfully." << std::endl;
    else
      std::cout << "error: only " << is.gcount() << " could be read";
    is.close();

    // ...buffer contains the entire file...
    delete[] buffer;
  }
}

int main(int argc, char *argv[]){
    
}