#ifndef BLOOM_H
#define BLOOM_H

#include <string>

class BloomFilter{
    int size;
    int numHash;
    bool *filter;

    // p := probability of a false positive
    // m := expected number of strings to be inserted
    // c := scale factor of bloom filter size
    // d := scale factor of number of hash functions
    public:
    BloomFilter(float p, int m, float c, float d);

    //Insert a string into the bloom filter.
    void insert(std::string element);

    //Delete an element from the bloom filter.
    //This will use an auxiliary hash table. defined below.
    void remove(std::string element);

    //Return true if the element is in the bloom filter,
    //otherwise returns false.
    bool find(std::string element);

    //Testing
    void print();
    
    //Dumps information of the entire filter. For debugging.
    void dumpAll();

    //Family of hash functions
    //The index specifies which hash function should be used
    int hash(unsigned int element, int index);
};

#endif