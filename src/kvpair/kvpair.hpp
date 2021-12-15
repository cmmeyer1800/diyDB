#pragma once

template<class K, class V>
struct KVPair{
    K key;
    V val;
    
    
    KVPair(K k, V v);
    KVPair();

    bool operator>(const KVPair<K,V> & other) const;
    bool operator<(const KVPair<K,V> & other) const;
    bool operator==(const KVPair<K,V> & other) const;
    bool operator!=(const KVPair<K,V> & other) const;
};


template<class K, class V>
KVPair<K,V>::KVPair(K k, V v) : key(k), val(v){}

template<class K, class V>
KVPair<K,V>::KVPair() : key(K()), val(V()){}

template<class K, class V>
bool KVPair<K,V>::operator>(const KVPair<K,V> & other) const{
    return key > other.key;
}

template<class K, class V>
bool KVPair<K,V>::operator<(const KVPair<K,V> & other) const{
    return other.key > key;
}

template<class K, class V>
bool KVPair<K,V>::operator==(const KVPair<K,V> & other) const{
    return key == other.key;
}

template<class K, class V>
bool KVPair<K,V>::operator!=(const KVPair<K,V> & other) const{
    return key != other.key;
}