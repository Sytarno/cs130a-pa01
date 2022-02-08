#define _GLIBCXX_USE_CXX11_ABI 0

#include "api.h"

#include <string>
#include <climits>
#include <cmath>
#include <iostream>

int bloomFilterSize(float p, int m, float c){
    int n = ceil(-((m * log(p)) / pow(log(2), 2)));
    return n*c;
}

int numHashFunctions(int n, int m, int d){
    int k = ceil(static_cast<float>(n) / m * log(2));
    return k*d;
}

    
unsigned int strToInt(std::string element){
    //float c = 3;
    float c = 9.4; //completely random choice here, no explanation.

    bool overflow = false;
    unsigned long shift = -1;

    unsigned int x = 0;
    for(size_t i = 0; i < element.length(); i++){
        unsigned short val = element[i] * pow(c, i);
        //check for overflow
        if((x + val) < x){
            overflow = true;
            shift = element.length()-i;
            break;
        }else{
            x += val;
        }
    }

    //---What do we do if we overflow?
    //This does a left shift of every letter, meaning we omit the first letter
    //WHILST maintaining the same powers of N in C^N
    //This preserves the bias that this version of the string should have,
    //Since if we just spliced a letter, strings that have the same substring
    //would end up having the same hash code.
    if(overflow){
        x = 0;
        for(size_t i = shift; i < element.length(); i++){
            unsigned short val = static_cast<int>(element[i]) * pow(c, i);
            x += val;
        }
    }
    return x;
}

bool isPrime(int x){
    for(int i = 2; i <= ceil(x/2); i++){
        if(x % i == 0){
            return false;
        }
    }
    return true;
}

unsigned int nextPrime(int n){
    int res = n + 1;

    while(!isPrime(res)){
        res++;
    }
    return res;
}
