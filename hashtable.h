#pragma once
#include "node.h"

class hash_table
{
    node** buckets;

public:
    hash_table(int bucket);
    ~hash_table();

    int insert_element(int key);
};
