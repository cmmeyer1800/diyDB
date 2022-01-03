#include "database.h"

#include <filesystem>
#include <iostream>
#include <string>

#include "dict.h"

#ifndef FILEPATH
#define FILEPATH "."
#endif

#ifdef __linux__
namespace fs = std::filesystem;
#elif __APPLE__
namespace fs = std::__fs::filesystem;
#endif

Database::Database() {
  for (const auto& entry : fs::directory_iterator(FILEPATH)) {
    std::string p = entry.path().string();
    if (p.length() < 4) {
      continue;
    } else if (p.substr(p.length() - 4, 4) != ".wal") {
      continue;
    } else {
      recreate(p);
    }
  }
}

void Database::create(std::string name) {
  locs_[name] = dicts_.size() + 1;
  dicts_.push_back(ds::Dict(name));
}

void Database::recreate(std::string filename) {
  std::string formatted;
  auto idx = filename.find_last_of('/');
  if (idx != std::string::npos) {
    formatted = filename.substr(idx + 1, filename.size() - idx - 1);
  }
  formatted = formatted.substr(0, formatted.length() - 4);
  locs_[formatted] = dicts_.size() + 1;
  dicts_.push_back(ds::Dict(formatted, filename));
}

std::vector<std::string> Database::getDicts() {
  std::vector<std::string> ret;
  for (auto& i : dicts_) {
    ret.push_back(i.getName());
  }
  return ret;
}

void Database::remove(std::string name) {
  get(name).clearWAL();
  size_t idx = locs_[name];
  locs_.erase(name);
  for (auto i : locs_) {
    if (i.second > idx) {
      i.second -= 1;
    }
  }
  dicts_.erase(dicts_.begin() + idx - 1);
}

ds::Dict& Database::get(std::string name) { return dicts_.at(locs_[name] - 1); }

bool Database::check(std::string name) { return locs_[name]; }