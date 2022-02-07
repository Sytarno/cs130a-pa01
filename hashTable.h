#ifndef HASH_H
#define HASH_H

#include <string>

//Linked List Node
struct Node{
    unsigned int data;
    Node* next;
};

class HashTable{
    public:

    int q;
    Node** table;

    //Separate Chaining Hash Table
    //This will be used for your removed elements of the bloom filter.
    // q := the size of the hash table (prime number)
    HashTable(int q);
    ~HashTable();

    //Insert a string into the hash table.
    void insert(std::string element);

    //Delete an element from the hash table.
    void remove(std::string element);

    //Return true if the element is in the hash table, 
    //otherwise return false.
    bool find(std::string element);
};

#endif