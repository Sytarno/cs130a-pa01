#define _GLIBCXX_USE_CXX11_ABI 0

#ifndef API_H
#define API_H

#include <string>

//Compute the bloom filter size based on the false positive probability desired,
//and the expected number of strings to be inserted.
//Scale the computed size by 'c' (for experimental purposes).
// p := probability of a false positive
// m := expected number of strings to be inserted
// c := sclae factor of bloom filter size
int bloomFilterSize(float p, int m, int c);

//Compute the number of hash functiosn to use based on the bloom filter size,
//and the expected number of strings to be inserted.
//Scale the computed size by 'd' (for experimental purposes)
//n := bloom filter size
//m := expected number of strings to be inserted
//d := scale factor of bloom filter size
int numHashFunctions(int n, int m, int d);

//String to integer conversion.
//Needed for running the elements on the above hash functions.
unsigned int strToInt(std::string element);

//Helper method to determine if a number is a prime.
bool isPrime(int x);

//Helper method to determine next larger prime. 
//Also assumes we never throw a value less than 3.
unsigned int nextPrime(int n);

#endif