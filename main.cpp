#include <iostream>
#include <fstream>  // for file I/O
#include <string>
#include <sstream>  // stringstream
#include <cstdlib>

#include <bits/stdc++.h>    // for getting clock/time

#include "hashtable.h"
#include "hashfunction.h"

using std::cout;
using std::endl;
using std::string;
using namespace hash;

// function prototypes
void test_codes();
void read_csv_data(hash_table&);

int main()
{
    // ==== TESTING ====
    //test_codes();   // test codes for testing out the hash table

    // ==== ACTUAL APPLICATION ====
    // create hash table
    int n = 500000;
    hash_table hashtable(n, hash::division_method);
    // read dataset into hash table
    read_csv_data(hashtable);   // read CSV file containing dataset into hash table

    // search/test codes here
    clock_t start, end;
    start = clock();
    cout << "Key: 545530                Value   : " << hashtable.get_value(545530) << endl;   // 16C YIO CHU KANG ROAD SINGAPORE 545530
    cout << "Key: 545530  Key Comparisons Made  : " << hashtable.find_key(545530) << endl; // 1, as n > dataset size
    end = clock();

    cout << "Number of clock ticks: " << end - start << endl;

    return 0;
}

void test_codes() {

    // create hash table
    hash_table hashtable(5, hash::division_method);

    // test insert & set value
    cout << hashtable.insert_element(7, "500") << endl;    // prints 1
    cout << hashtable.insert_element(2, "500") << endl;    // prints 1, but there will be collision in the hash table's slots
    cout << hashtable.insert_element(7, "555") << endl;    // prints 0; duplicate key
    cout << hashtable.set_value(7, "599") << endl;    // prints 1; new value set

    // test get values
    cout << "Key: 7  Value: " << hashtable.get_value(7) << endl;
    cout << "Key: 2  Value: " << hashtable.get_value(2) << endl;
    if (hashtable.get_value(8) == "")
        cout << "Key: 8  Value: (Not found)" << endl;
}

void read_csv_data(hash_table& hashtable) {

    // read file
    std::ifstream csvfile("csvdata_searchval.csv");
    if (csvfile.is_open()) {
        string line; // to store each line in the CSV
        while (getline(csvfile, line))
        {
            std::stringstream ss(line);
            string token;
            std::getline(ss, token, ',');   // token = postal code
            int postalCode = std::atoi(token.c_str());
            std::getline(ss, token, ',');   // token = street/building name
            hashtable.insert_element(postalCode, token);
        }
        csvfile.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}
