#include <stdint.h>
#include <iostream>

struct UUID{
    int32_t val;

    UUID(){
        val = static_cast<int32_t>(-1);
    }

    UUID(int newVal){
        val = static_cast<int32_t>(newVal);
    }

    friend std::ostream &operator<<(std::ostream &output, const UUID &id){
        output << "ID: " << id.val <<std::endl;
        return output;
    }

    bool operator==(const UUID &other) const{
        return val == other.val;
    }

    bool operator>(const UUID &other) const{
        return val > other.val;
    }

    bool operator<(const UUID &other) const{
        return val < other.val;
    }

    bool operator!=(const UUID &other) const{
        return val != other.val;
    }
};