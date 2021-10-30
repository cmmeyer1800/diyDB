#include "main.h"
#include "cli.hpp"

int main(){
    CLI cli;
    std::cout << "\x1B[2J\x1B[H";
    bool running = true;
    while(running){
        if(!cli.takeOptions()){
            running = false;
        }
        std::cout << "\x1B[2J\x1B[H";
    }
    return 0;
}