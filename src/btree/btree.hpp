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
                    Node(const Node & other);
            };

            BTree(size_t order);
            BTree(const BTree & other);
            const BTree<K, V> & operator=(const BTree & other);


            ~BTree();

            Node * getRoot(){return root_;}

        private:

            size_t order_;
            Node * root_;

            void del(Node * subroot);
            Node * copy(const Node * subroot);
    };

};

template<class K, class V>
ds::BTree<K,V>::Node::Node(size_t order){
    elems = std::vector<KVPair<K,V>>(order, KVPair<K,V>());
    children = std::vector<Node *>(order, NULL);
}

template<class K, class V>
ds::BTree<K,V>::Node::Node(const Node & other) : elems(other.elems), children(other.children){}

template<class K, class V>
ds::BTree<K,V>::BTree(size_t order) : order_(order){
    root_ = new Node(order_);
}

template<class K, class V>
ds::BTree<K,V>::~BTree(){
    del(root_);
}

template<class K, class V>
void ds::BTree<K,V>::del(Node * subroot){
    for(auto i : subroot->children){
        if(i != NULL){
            del(i);
        }
    }
    delete subroot;
    subroot = NULL;
}

template <class K, class V>
ds::BTree<K, V>::BTree(const BTree & other){
    del(root_);
    root_ = copy(other.root_);
}

template <class K, class V>
const ds::BTree<K, V> & ds::BTree<K, V>::operator=(const BTree & other){
    if (this != & other) {
        clear(root_);
        root_ = copy(other.root_);
    }
    return *this;
}

template <class K, class V>
typename ds::BTree<K, V>::Node * ds::BTree<K, V>::copy(const Node * subroot){
    if (subroot == NULL) {
        return NULL;
    }

    Node * new_node = new Node(*subroot);
    for(auto & child : subroot->children) {
        new_node->children.push_back(copy(child));
    }
    return new_node;
}