#pragma once

#include <string>
#include <limits>
#include "hash.h"
#include "btree.hpp"

namespace ds{

    template<class V>
    class Dict{

        private:

            BTree<unsigned, V> tree_;

            unsigned count_;

        public:

            Dict() : tree_(100), count_(0){}

            void insert(std::string key, V value){
                if(count_ > std::numeric_limits<unsigned>::max()){
                    throw DictOverflow();
                }
                else{
                    tree_.insert(alg::hash(key), value);
                    count_++;
                }
            }

            V operator[](std::string key){
                return tree_.find(alg::hash(key));
            }
    };

};