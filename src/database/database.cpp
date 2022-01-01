#include "database.h"
#include "dict.h"

#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::__fs::filesystem;

Database::Database(){
    std::string path = ".";
    for(const auto & entry : fs::directory_iterator(path)){
        std::string p = entry.path().string();
        if(p.length() < 4){
            continue;
        }
        else if(p.substr(p.length()-4, 4) != ".wal"){
            continue;
        }
        else{
            recreate(p.substr(2, p.length() - 2));
        }
    }
}

void Database::create(std::string name){
    locs_[name] = dicts_.size() + 1;
    dicts_.push_back(ds::Dict(name));
}

void Database::recreate(std::string name){
    locs_[name.substr(0, name.length() - 4)] = dicts_.size() + 1;
    dicts_.push_back(ds::Dict(name.substr(0, name.length() - 4), true));
}

ds::Dict & Database::get(std::string name){
    return dicts_.at(locs_[name] - 1);
}

bool Database::check(std::string name){
    return locs_[name];
}