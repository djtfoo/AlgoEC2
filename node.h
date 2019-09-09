#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <string>

// node of a hash table
namespace hash {
    struct node
    {
        int key;
        std::string value;
        node* next;

        node(int key, std::string value) : key(key), value(value), next(0) {}
    };
}

#endif  // NODE_H_INCLUDED
