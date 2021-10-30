#include <string>
#include "btree.hpp"
#include "userid.hpp"
#include "contact.hpp"
#include <iostream>

class CLI{
    private:

        std::string optPrint = "Please choose option:\n\tQuit [0]\n\tNew user [1]";

        int parseInput(std::string in);

    public:

        bool takeOptions();
};

int CLI::parseInput(std::string in){
    for(unsigned i = 0; i < in.size(); i++){
        if(!isdigit(in[i])) return -1;
    }
    int opt = std::stoi(in);
    return opt;
}

bool CLI::takeOptions(){
    std::cout << optPrint << std::endl;
    std::cout << "Choice: ";
    std::string option;
    std::cin >> option;
    int opt = parseInput(option);
    switch(opt){
        case 0:
            return false;

        default:
            std::cout << "ERROR: option must be a valid number" << std::endl;
    }
    return true;
}