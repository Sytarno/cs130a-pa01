#define _GLIBCXX_USE_CXX11_ABI 0

#include "bloomFilter.h"
#include "hashTable.h"

#include <iostream>
#include <fstream>
#include <climits>
#include <string>

using namespace std;

int main(int argc, char** argv){
    /**
    //test overflow
    string start = "a";
    for(int i = 0; i < 50; i++){
        start += "a";
        cout << "string: " << strToInt(start) << endl;
    }

    //test similarity
    cout << "1 : " << strToInt("gog") << endl;
    cout << "2 : " << strToInt("dog") << endl;
    **/

    HashTable htable(5);
    //BloomFilter bloom_filter(1, 1, 1, 1);

    ifstream setup_file;
    string ins[4];
    setup_file.open(argv[1]);
    
    if(argc){}

    if(setup_file.is_open()){
        for(int i = 0; i < 4; i++){
            setup_file >> ins[i];
        }
    }
    setup_file.close();
    //
    float p = stof(ins[0]);
    int c = stoi(ins[1]), d = stoi(ins[2]), q = stoi(ins[3]);
    cout << "Experiment for values of:" << endl;
    cout << "p = " << p << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
    cout << "q = " << q << endl;
    
    //Prep files
    ifstream input_file; 
    input_file.open(argv[2]);
    ifstream success;
    success.open(argv[3]); 
    ifstream fail;
    fail.open(argv[4]);
    ifstream remove;
    remove.open(argv[5]);

    for(int x = 0; x < 2; x++){
        cout << "Phase <" << (x+1) << ">" << endl; 
        BloomFilter bloom_filter(p, 1000, c, d);
        string* inputSet = new string[1000];
    
        for(int i = 0; i < 1000; i++){
            string input;
            input_file >> input;
            inputSet[i] = input;
            bloom_filter.insert(input);
        }
        bloom_filter.print();
    }


    //Close all ifstreams
    input_file.close();
    success.close();
    fail.close();
    remove.close();

    return 0;
}