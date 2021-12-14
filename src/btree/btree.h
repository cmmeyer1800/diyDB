#pragma once

#include <vector>
#include "kvpair.h" 

namespace ds{

    template<class K, class V>
    class BTree{
        private:

            class Node{
                public:

                    std::vector<KVPair<K,V>> elems;
                    std::vector<Node *> children;
                    Node();
            };

        public:


    };

}