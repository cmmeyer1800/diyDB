#pragma once

template<class K, class V>
struct KVPair{
    K key;
    V val;
    
    KVPair(K k, V v);
    KVPair();

    inline bool operator<(const KVPair& rhs) const{
        return this->key < rhs.key;
    }

    inline bool operator<(const K& rhs) const{
        return this->key < rhs;
    }

    inline friend bool operator<(const K& lhs, const KVPair& rhs)
    {
        return lhs < rhs.key;
    }

    inline bool operator>(const KVPair& rhs) const{
        return this->key > rhs.key;
    }

    inline friend bool operator>(const K& lhs, const KVPair& rhs){
        return lhs > rhs.key;
    }

    inline bool operator>(const K& rhs) const{
        return this->key > rhs;
    }

    inline bool operator==(const KVPair& rhs) const{
        return this->key == rhs.key;
    }

    inline bool operator==(const K& rhs) const{
        return this->key == rhs;
    }

    inline friend bool operator==(const K& lhs, const KVPair& rhs){
        return lhs == rhs.key;
    }
};


template<class K, class V>
KVPair<K,V>::KVPair(K k, V v) : key(k), val(v){}

template<class K, class V>
KVPair<K,V>::KVPair() : key(K()), val(V()){}