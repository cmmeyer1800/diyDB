#pragma once

#include <vector>
#include "kvpair.hpp" 

namespace ds{

    template<class K, class V>
    class BTree{
        public:
            class Node{
                public:

                    std::vector<KVPair<K,V>> elems;
                    std::vector<Node *> children;
                    Node(size_t order);
            };
            Node * getRoot(){return root_;}
            BTree(size_t order);

        private:

            size_t order_;
            Node * root_;
    };

}

template<class K, class V>
ds::BTree<K,V>::Node::Node(size_t order){
    elems = std::vector<KVPair<K,V>>(order, KVPair<K,V>());
    children = std::vector<Node *>(order, NULL);
}

template<class K, class V>
ds::BTree<K,V>::BTree(size_t order) : order_(order){
    root_ = new Node(order_);
}