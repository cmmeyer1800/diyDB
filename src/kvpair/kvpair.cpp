#include "kvpair.h"

template<class K, class V>
KVPair<K,V>::KVPair(K k, V v) : key(k), val(v){}

template<class K, class V>
KVPair<K,V>::KVPair() : key(K()), val(V()){}