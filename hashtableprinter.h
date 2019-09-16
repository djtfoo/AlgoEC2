#ifndef HASHTABLEPRINTER_H_INCLUDED
#define HASHTABLEPRINTER_H_INCLUDED

#include <iostream>
#include <map>
#include "hashtable.h"
#include "node.h"

namespace hash {
    class hash_table_printer
    {
    public:
        static int printKeyDistribution(const hash_table& hashtable) {

            std::map<int, int> counts;
            int key_comparisons = 0;

            for (int i = 0; i < hashtable.tableSize; ++i) {
                int counter = 0;
                for (node* ptr = hashtable.buckets[i]; ptr != NULL; ptr = ptr->next)
                    ++counter;
                if (counts.find(counter) == counts.end())
                    counts.insert(std::pair<int, int>(counter, 1));
                else
                    counts[counter] += 1;
            }

            // print key distribution
            for (std::map<int, int>::iterator it = counts.begin(); it != counts.end(); ++it) {
                std::cout << "Slots with " << it->first << " keys : " << it->second << std::endl;
                for (int i = 1; i <= it->first; ++i)
                    key_comparisons += i * it->second;
            }

            std::cout << std::endl;

            return key_comparisons;
        }
    };
}
#endif // HASHTABLEPRINTER_H_INCLUDED
