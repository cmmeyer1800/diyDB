#pragma once

#include <fstream>

template<class K, class V>
class Log{

    private:

        std::ofstream file;

    public:

        Log() : file("wal.bin"){}

        write()

};