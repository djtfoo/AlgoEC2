#ifndef HASHFUNCTION_H_INCLUDED
#define HASHFUNCTION_H_INCLUDED

#include <iostream>

namespace hash {

    static int division_method(int key, int tableSize) {
        //std::cout<< "Division Method" << std::endl;
        return key % tableSize;
    }
    static int folding_method(int key, int tableSize) {
        //std::cout<< "Folding Method" << std::endl;
        return key;
    }
    static int multiplicative_congruential_method(int key, int tableSize) {
        //std::cout<< "Multiplicative Congruential Method" << std::endl;
        return key;
    }
}

#endif // HASHFUNCTION_H_INCLUDED
