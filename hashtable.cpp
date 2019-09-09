#include "hashtable.h"
#include <iostream>

using std::cout;
using std::endl;
using hash::hash_table;

// initialize tableSize and hashFunction
hash_table::hash_table(int tableSize, int(*func)(int,int)) : tableSize(tableSize), hashfunc(func) {

    // create dynamic array of node pointers (slots in the hash table)
    buckets = new node*[tableSize]();   // create an array of node pointers; () sets every pointer to null
}

hash_table::~hash_table() {

    cout << "Destroying hash table" << endl;

    for (int i = 0; i < tableSize; ++i) {
        while (buckets[i] != NULL) {
            node *temp = buckets[i];
            buckets[i] = buckets[i]->next;
            cout << "Deleting key " << temp->key << endl;
            delete temp;
        }
    }
    cout << "Deleting buckets" << endl;
    delete[] buckets;
}

bool hash_table::insert_element(int key, char* value) {

    int hashedKey = hashfunc(key, tableSize);
    if (hashedKey >= tableSize)   // hash function failed
    {
        cout << "FUck, our hash function failed" << endl;
        return false;   // failed to insert
    }

    if (buckets[hashedKey] == NULL) {   // no collision
        buckets[hashedKey] = new node(key, value);
        return true;
    }
    else {  // collision; insert
        node* ptr = buckets[hashedKey];
        while (ptr->next != NULL) {
            if (ptr->key == key)    // key already exists
                return false;
            ptr = ptr->next;
        }
        if (ptr->key == key)    // key already exists
            return false;
        ptr->next = new node(key, value);
        return true;
    }
}

char* hash_table::get_value(int key) {

    int hashedKey = hashfunc(key, tableSize);
    if (hashedKey >= tableSize)   // hash function failed
    {
        cout << "FUck, our hash function failed" << endl;
        return false;   // failed to insert
    }

    if (buckets[hashedKey] == NULL) {   // key not found
        return NULL;
    }
    else {  // collision; check nodes in bucket
        node* ptr = buckets[hashedKey];
        do {
            if (ptr->key == key)    // key already exists
                return ptr->value;
            ptr = ptr->next;
        } while (ptr != NULL);
        return NULL;    // not found in the collision linked list
    }
}

char* hash_table::set_value(int key, char* newValue) {

    int hashedKey = hashfunc(key, tableSize);
    if (hashedKey >= tableSize)   // hash function failed
    {
        cout << "FUck, our hash function failed" << endl;
        return false;   // failed to insert
    }

    if (buckets[hashedKey] == NULL) {   // key not found
        return NULL;
    }
    else {  // collision; check nodes in bucket
        node* ptr = buckets[hashedKey];
        do {
            if (ptr->key == key)    // key already exists
            {
                ptr->value = newValue;
                return ptr->value;
            }
            ptr = ptr->next;
        } while (ptr != NULL);
        return NULL;    // not found in the collision linked list
    }
}
