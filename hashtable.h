#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include "node.h"
#include "hashfunction.h"

namespace hash {
    class hash_table    // closed address hash table
    {
        node** buckets; // pointer to a pointer to create dynamic array of node pointers
        int tableSize;  // number of buckets (slots) in the hash table
        int (*hashfunc)(int,int);   // pointer to the hash function

    public:
        hash_table(int bucketsSize, int(*func)(int,int) = hash::division_method);   // constructor
        virtual ~hash_table();  // destructor

        bool insert_element(int key, char* value);  // insert key into hash table if it does not exist
        char* get_value(int key);   // get value corresponding to key
        char* set_value(int key, char* newValue);   // set new value corresponding to key
    };
}

#endif // HASHTABLE_H_INCLUDED
