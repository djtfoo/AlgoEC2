#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include "node.h"
#include "hashfunction.h"

class hash_table
{
    node** buckets;
    int tableSize;
    int (*hashfunc)(int,int);

public:
    hash_table(int bucketsSize, int(*func)(int,int) = hash_function::division_method);
    virtual ~hash_table();

    bool insert_element(int key, char* value);
    char* get_value(int key);
    char* set_value(int key, char* newValue);
};

#endif // HASHTABLE_H_INCLUDED
