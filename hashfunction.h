#ifndef HASHFUNCTION_H_INCLUDED
#define HASHFUNCTION_H_INCLUDED

#include <iostream>
#include <math.h>

namespace hash {

    static int division_method(int key, int tableSize) {
        //std::cout<< "Division Method" << std::endl;
        return key % tableSize;
    }
    static int mid_square_method(int key, int tableSize) {
        //std::cout<< "Folding Method" << std::endl;
        unsigned long long keySquared = key * key / 1000;
        return (keySquared % 1000000) % tableSize;
    }
    static int multiplicative_congruential_method(int key, int tableSize) {
        //std::cout<< "Multiplicative Congruential Method" << std::endl;
        double multiplier = (2.2360679775 - 1)/2;  // reciprocal golden ratio
        return tableSize * (key*multiplier - (int)(key*multiplier));
    }
}

#endif // HASHFUNCTION_H_INCLUDED
