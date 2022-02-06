#define _GLIBCXX_USE_CXX11_ABI 0

#include "bloomFilter.h"
#include "hashTable.h"

#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, char** argv){
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
    
    float p = stof(ins[0]);
    int m = stoi(ins[1]), c = stoi(ins[2]), d = stoi(ins[3]);
    cout << "Experiment for values of:" << endl;
    cout << "p = " << p << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
    //cout << "q = " << q << endl;
    
    //Prep files
    ifstream input_file; 
    input_file.open(argv[2]);
    ifstream success;
    success.open(argv[3]); 
    ifstream fail;
    fail.open(argv[4]);
    ifstream remove;
    remove.open(argv[5]);

    int num_phase = 10;
    int insertions = 1000;
    int searches = 100;

    BloomFilter bloom_filter(p, m, c, d);

    int total_false_neg = 0;
    int total_false_pos = 0;
    for(int x = 0; x < num_phase; x++){
        cout << "Phase <" << (x+1) << ">" << endl; 
    
        for(int i = 0; i < insertions; i++){
            string input;
            input_file >> input;
            bloom_filter.insert(input);
        }

        int false_neg = 0;
        for(int i = 0; i < searches; i++){
            string search;
            success >> search;
            if(!bloom_filter.find(search)){
                false_neg++;
            }
        }

        total_false_neg += false_neg;

        string* falsePositives = new string[100];
        int false_pos = 0;
        for(int i = 0; i < searches; i++){
            string search;
            fail >> search;
            if(bloom_filter.find(search)){
                falsePositives[false_pos] = search;
                false_pos++;
            }

        }

        total_false_pos += false_pos;

        cout << "Number of false negatives:" << endl;
        cout << false_neg << endl;
        cout << "Number of false positives:" << endl;
        cout << false_pos << endl;
        cout << "Probability of false positives:" << endl;
        cout << setprecision(5) << false_pos / 100.0 << endl;
        cout << "False Positive Elements:" << endl;
        for(int i = 0; i < false_pos; i++){
            cout << i+1 << ": " << falsePositives[i] << endl;
        }

        cout << endl;
    }

    //Close all ifstreams
    input_file.close();
    success.close();
    fail.close();
    remove.close();

    bloom_filter.print();

    cout << "Total over "  << num_phase << " phase(s): " << endl;
    cout << "Number of false negatives:" << endl;
    cout << total_false_neg << endl;
    cout << "Number of false positives:" << endl;
    cout << total_false_pos << endl;
    cout << "Probability of false positives:" << endl;
    cout << total_false_pos / 1000.0 << endl;

    return 0;
}