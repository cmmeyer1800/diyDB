#include "hash.h"
#include <string>
#include <limits>
#include <math.h>

namespace alg{

    unsigned hash(std::string input){
        unsigned ret = 0;
        for(size_t count = 0; count < input.length(); count++){
            ret += pow(static_cast<unsigned>(input.at(count)), count+1);
        }
        return ret % std::numeric_limits<unsigned>::max();
    }
};