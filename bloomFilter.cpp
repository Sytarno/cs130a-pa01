#define _GLIBCXX_USE_CXX11_ABI 0

#include "api.h"
#include "bloomFilter.h"

#include <sstream>
#include <math.h>
#include <climits>
#include <iostream>

BloomFilter::BloomFilter(float p, int m, float c, float d){
        this->size = bloomFilterSize(p, m, c);
        this->numHash = numHashFunctions(this->size, m, d);

        this->filter = new bool[this->size]();
}

void BloomFilter::insert(std::string element){
        unsigned int x = strToInt(element);
        for(int i = 0; i < numHash; i++){
                int n = hash(x, i);
                this->filter[n] = true;
        }
}      

bool BloomFilter::find(std::string element){
        unsigned int x = strToInt(element);
        for(int i = 0; i < numHash; i++){
                int n = hash(x, i);
                if(!this->filter[n]){
                        return false;
                }
        }
        return true;
}

int BloomFilter::hash(unsigned int element, int index){
        return static_cast<int>(element * (log(index+2))) % (this->size+1);
        //return static_cast<int>(element * (index+3)) % (this->size);
}

void BloomFilter::print(){
        std::cout << "created a bloom filter of size " << this->size << std::endl;
        std::cout << "with hash functions: " << this->numHash << std::endl;

        
        std::cout << "contents:" << std::endl;
        for(int i = 0; i < this->size; i++){
                std::cout << this->filter[i];
        }
        std::cout << std::endl;
}