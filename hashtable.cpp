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
            //cout << "Deleting key " << temp->key << endl;
            delete temp;
        }
    }
    cout << "Deleting buckets" << endl;
    delete[] buckets;
}

bool hash_table::insert_element(int key, std::string value) {

    int hashedKey = hashfunc(key, tableSize);
    if (hashedKey >= tableSize)   // hash function failed
    {
        cout << "hash function failed" << endl;
        return false;   // invalid key; failed to insert
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

std::string hash_table::get_value(int key) {

    int hashedKey = hashfunc(key, tableSize);
    if (hashedKey >= tableSize)   // hash function failed
    {
        cout << "hash function failed" << endl;
        return "";   // invalid key
    }

    /*if (buckets[hashedKey] == NULL) {   // key not found
        return "";  // key not found
    }*/
    //else {  // collision; check nodes in bucket
    node* ptr = buckets[hashedKey];
    while (ptr != NULL) {
        if (ptr->key == key)    // key already exists
            return ptr->value;
        ptr = ptr->next;
    }
    return "";    // not found in the collision linked list
    //}
}

// number of key comparisons made to find the key. if key not found, return -1
int hash_table::find_key(int key) {

    int hashedKey = hashfunc(key, tableSize);
    if (hashedKey >= tableSize)   // hash function failed
    {
        cout << "hash function failed" << endl;
        return -1;   // invalid key
    }

    /*if (buckets[hashedKey] == NULL) {   // key not found
        return -1;  // key not found
    }*/
    //else {  // collision; check nodes in bucket
    int keyComp = 0;
    node* ptr = buckets[hashedKey];
    while (ptr != NULL) {
        ++keyComp;
        if (ptr->key == key)    // key already exists
            return keyComp;
        ptr = ptr->next;
    }
    return keyComp;   // not found in the collision linked list
    //}
}

bool hash_table::set_value(int key, std::string newValue) {

    int hashedKey = hashfunc(key, tableSize);
    if (hashedKey >= tableSize)   // hash function failed
    {
        cout << "hash function failed" << endl;
        return false;   // invalid key; failed to set value
    }

    if (buckets[hashedKey] == NULL) {   // key not found
        return false;   // key does not exist; failed to set value
    }
    else {  // collision; check nodes in bucket
        node* ptr = buckets[hashedKey];
        do {
            if (ptr->key == key)    // key already exists
            {
                ptr->value = newValue;
                return true;
            }
            ptr = ptr->next;
        } while (ptr != NULL);
        return false;   // key not found in the collision linked list
    }
}
