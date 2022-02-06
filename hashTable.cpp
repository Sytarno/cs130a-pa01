#include "hashTable.h"

#include <string>

HashTable::HashTable(int q){
    this->q = q;
    this->table = new Node[this->q];
}

//void HashTable::insert(std::string element){}
