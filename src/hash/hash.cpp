#include "hash.h"

#include <math.h>

#include <limits>
#include <string>

namespace alg {

unsigned hash(std::string input) {
  unsigned hash = 0;
  for (size_t i = 0; i < input.length(); i++) {
    hash += input[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}
};  // namespace alg