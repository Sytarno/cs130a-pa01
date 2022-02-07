#define _GLIBCXX_USE_CXX11_ABI 0

#include "hashTable.h"
#include "api.h"

#include <string>
#include <iostream>

HashTable::HashTable(int q){
    this->q = q;
    this->table = new Node*[this->q]();
}

HashTable::~HashTable(){
    delete this->table;
}

void HashTable::insert(std::string element){
    unsigned int x = strToInt(element);
    int n = x % this->q;

    if(this->table[n]){
        Node *walker = this->table[n];
        
        while(walker->next){
            walker = walker->next;
        }
        Node *a = new Node();
        a->data = x;
        walker->next = a;
    }else{
        Node *a = new Node();
        a->data = x;
        this->table[n] = a;
    }
}

bool HashTable::find(std::string element){
    unsigned int x = strToInt(element);
    int n = x % this->q;

    if(this->table[n]){
        Node *walker = this->table[n];
        while(walker){
            std::cout << "looking for " << element << std::endl;
            if(walker->data == x){
                return true;
            }
            walker = walker->next;
        }
        return false;
    }else{
        return false;
    }
}

void HashTable::remove(std::string element){
    unsigned int x = strToInt(element);
    int n = x % this->q;

    if(this->table[n]){
        Node *walker = this->table[n];
        if(walker->data == x){
            std::cout << "case 1 " << std::endl;
            this->table[n] = walker->next;
            delete walker;
        }else{
            std::cout << "case 2 " << std::endl;
            while(walker->next){
                if(walker->next->data == x){
                    Node *temp = walker->next;
                    walker->next = walker->next->next;
                    delete temp;
                    break;
                }
                walker = walker->next;
            }
        }
    }
}