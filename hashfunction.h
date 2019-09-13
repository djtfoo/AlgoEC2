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
        int n1 = (key%10)*10 + (key%100)/10;
        key /= 100;
        int n2 = (key%10)*10 + (key%100)/10;
        key /= 100;
        int n3 = (key%10)*10 + (key%100)/10;

        return (n1*n2*n3) % tableSize;
    }
    static int multiplicative_congruential_method(int key, int tableSize) {
        //std::cout<< "Multiplicative Congruential Method" << std::endl;
        double multiplier = (sqrt(5) - 1)/2;  // reciprocal golden ratio
        return tableSize * (key*multiplier - floor(key*multiplier));
    }
}

#endif // HASHFUNCTION_H_INCLUDED
