#include "database.h"

#include <filesystem>
#include <iostream>
#include <string>

#include "dict.h"

#ifdef __linux
  namespace fs = std::filesystem;
#elif __APPLE__
  namespace fs = std::__fs::filesystem;
#endif

Database::Database() {
  std::string path = "/Users/Collin/bin/diyDB/";
  for (const auto& entry : fs::directory_iterator(path)) {
    std::string p = entry.path().string();
    if (p.length() < 4) {
      continue;
    } else if (p.substr(p.length() - 4, 4) != ".wal") {
      continue;
    } else {
      recreate(p.substr(2, p.length() - 2));
    }
  }
}

void Database::create(std::string name) {
  locs_[name] = dicts_.size() + 1;
  dicts_.push_back(ds::Dict(name));
}

void Database::recreate(std::string name) {
  locs_[name.substr(0, name.length() - 4)] = dicts_.size() + 1;
  dicts_.push_back(ds::Dict(name.substr(0, name.length() - 4), true));
}

std::vector<std::string> Database::getDicts() {
  std::vector<std::string> ret;
  for (auto& i : dicts_) {
    ret.push_back(i.getName());
  }
  return ret;
}

ds::Dict& Database::get(std::string name) { return dicts_.at(locs_[name] - 1); }

bool Database::check(std::string name) { return locs_[name]; }