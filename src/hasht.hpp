#include <string>
#include <math.h>
#include <iostream>

template <class T>
class hashTable{
    public:
        hashTable();

        hashTable(unsigned size);

        ~hashTable();

        T & operator[](std::string);

        void insert(std::string key, T val);

    private:
        T * arr;

        unsigned arrSize;

        unsigned hash(std::string input);
};

template <class T>
hashTable<T>::hashTable(){
    arr = new T[100];
    for(unsigned i = 0; i < 100; i++){
        arr[i] = T();
    }
    arrSize = 100;
}

template <class T>
hashTable<T>::hashTable(unsigned size){
    arr = new T[size];
    for(unsigned i = 0; i < size; i++){
        arr[i] = T();
    }
    arrSize = size;
}

template <class T>
hashTable<T>::~hashTable(){
    delete [] arr;
}

template <class T>
void hashTable<T>::insert(std::string key, T val){
    
}

template <class T>
unsigned hashTable<T>::hash(std::string input){
    unsigned sum;
    for(unsigned i = 0; i < input.size(); i++){
        sum += pow(unsigned(input[i]), i);
    }
    return sum % arrSize;
}

template <class T>
T & hashTable<T>::operator[](std::string key){
    T &val = arr[hash(key)];
    return val;
}

