#ifndef HASHFUNCTION_H_INCLUDED
#define HASHFUNCTION_H_INCLUDED

#include <iostream>
#include <math.h>

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
        double multiplier = (sqrt(5) - 1)/2;  // reciprocal golden ratio
        return tableSize * (key*multiplier - floor(key*multiplier));
    }
}

#endif // HASHFUNCTION_H_INCLUDED
