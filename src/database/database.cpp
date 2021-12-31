#include "database.h"
#include "dict.h"

#include <string>

void Database::create(std::string name){
    locs_[name] = dicts_.size() + 1;
    dicts_.push_back(ds::Dict(name));
}

ds::Dict & Database::get(std::string name){
    return dicts_.at(locs_[name] - 1);
}

bool Database::check(std::string name){
    return locs_[name];
}