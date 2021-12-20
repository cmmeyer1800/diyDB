#pragma once

#include "errors.h"
#include "binary_conv.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <cstddef>

#define LOGFILENAME "wal.bin"

template<class V>
class Log{

    private:

        std::string filename;

        void write(std::ofstream & ofs, std::string key){
            const char * out = key.c_str();
            ofs.write(out, sizeof(out));
        }

        void write(std::ofstream & ofs, V value){
            const char * mem = binary_conv<V>(value);
            ofs.write(mem, sizeof(mem)/2);
            delete[] mem;
        }

    public:

        Log() : filename(LOGFILENAME){}

        void commit(std::string key, V value){
            std::ofstream file(filename, std::ios::binary | std::ios::app);
            if(!file){
                throw FileNotOpen();
            }
            else{
                write(file, key);
                write(file, value);
            }
            file.close();
        }

        char *  pull(){
            std::ifstream file(filename, std::ios::binary);
            if(!file){
                throw FileNotOpen();
                return NULL;
            }
            else{
                file.seekg(0, file.end);
                unsigned length = file.tellg();
                file.seekg(0, file.beg);
                char * buffer = new char[length];
                file.read(buffer,length);
                file.close();
                return buffer;
            }
            return NULL;
        }
};