#pragma once

template<class K, class V>
struct KVPair{
    K key;
    V val;
    KVPair(K k, V v);
    KVPair();
};