#ifndef API_H
#define API_H

#include <string>
#include <climits>
#include <cmath>
#include <iostream>

namespace api{

    //Compute the bloom filter size based on the false positive probability desired,
    //and the expected number of strings to be inserted.
    //Scale the computed size by 'c' (for experimental purposes).
    // p := probability of a false positive
    // m := expected number of strings to be inserted
    // c := sclae factor of bloom filter size
    int bloomFilterSize(float p, int m, int c){
        int n = ceil(-((m * log(p)) / pow(log(2), 2)));
        return n*c;
    }

    //Compute the number of hash functiosn to use based on the bloom filter size,
    //and the expected number of strings to be inserted.
    //Scale the computed size by 'd' (for experimental purposes)
    //n := bloom filter size
    //m := expected number of strings to be inserted
    //d := scale factor of bloom filter size
    int numHashFunctions(int n, int m, int d){
        int k = ceil(static_cast<float>(n) / m * log(2));
        return k*d;
    }

    //String to integer conversion.
    //Needed for running the elements on the above hash functions.
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
}

#endif