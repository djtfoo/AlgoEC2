#include "hashtable.h"

hash_table::hash_table(int bucket) {
    buckets = new node*[bucket];
}

hash_table::~hash_table() {
    // delete individual nodes
    delete[] buckets;
}

int hash_table::insert_element(int key) {

    return -1;
}
