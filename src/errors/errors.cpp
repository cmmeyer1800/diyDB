#include "errors.h"


const char * KeyNotFound::what () const throw (){
    return "Passed key was not found in the dictionary";
}

const char * DictOverflow::what () const throw (){
    return "Dictionary filled passed limit of 4294967295 key value pairs";
}