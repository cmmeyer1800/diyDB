// #include "btree.hpp"
// #include "hash.h"
// #include "dict.hpp"
// #include <iostream>
// #include <string>
// #include <limits.h>
// 
// int main(int argc, char *argv[]){
//     ds::Dict<double> gpa;
//     gpa.insert("Collin_Meyer", 3.72);
//     std::cout << gpa["Collin_Meyer"];
//     //std::cout << gpa["test"];
// }

#include <fstream>
using namespace std;
int main(){
    int num = 162;
    ofstream file("file.bin", ios::binary);
    file.write(reinterpret_cast<const char *>(&num), sizeof(num));
    file.close(); 
    return 0;
}