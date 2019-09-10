#include <iostream>
#include <fstream>  // for file I/O
#include <string>
#include <sstream>  // stringstream
#include <cstdlib>
#include <windows.h>

#include <bits/stdc++.h>    // for getting clock/time

#include "hashtable.h"
#include "hashfunction.h"

using std::cout;
using std::endl;
using std::string;
using namespace hash;

// function prototypes
void test_search(hash_table&, int);
void test_codes();
void read_csv_data(hash_table&);

int main()
{
    // ==== TESTING ====
    //test_codes();   // test codes for testing out the hash table

    // ==== ACTUAL APPLICATION ====
    int nLoadFactor25 = 485587;
    int nLoadFactor50 = 242797;
    int nLoadFactor75 = 161869;
    int nLoadFactor100 = 121403;
    int nLoadFactor200 = 60703;

    // create hash table
    hash_table hashtable_division25(nLoadFactor25, hash::division_method);
    // read dataset into hash table
    read_csv_data(hashtable_division25);   // read CSV file containing dataset into hash table

    hash_table hashtable_division50(nLoadFactor50, hash::division_method);
    read_csv_data(hashtable_division50);

    hash_table hashtable_division75(nLoadFactor75, hash::division_method);
    read_csv_data(hashtable_division75);

    hash_table hashtable_mcm25(nLoadFactor25, hash::multiplicative_congruential_method);
    read_csv_data(hashtable_mcm25);

    hash_table hashtable_mcm50(nLoadFactor50, hash::multiplicative_congruential_method);
    read_csv_data(hashtable_mcm50);

    hash_table hashtable_mcm75(nLoadFactor75, hash::multiplicative_congruential_method);
    read_csv_data(hashtable_mcm75);

    cout << "=== DIVISION METHOD | LOAD FACTOR 0.25 | SUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_division25, 545530);

    cout << "=== DIVISION METHOD | LOAD FACTOR 0.25 | UNSUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_division25, 418526);

    cout << "=== DIVISION METHOD | LOAD FACTOR 0.50 | SUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_division50, 545530);

    cout << "=== DIVISION METHOD | LOAD FACTOR 0.50 | UNSUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_division50, 418526);

    cout << "=== DIVISION METHOD | LOAD FACTOR 0.75 | SUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_division75, 545530);

    cout << "=== DIVISION METHOD | LOAD FACTOR 0.75 | UNSUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_division75, 418526);

    cout << "=== MULTIPLICATIVE CONGRUENTIAL METHOD | LOAD FACTOR 0.25 | SUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_mcm25, 545530);

    cout << "=== MULTIPLICATIVE CONGRUENTIAL METHOD | LOAD FACTOR 0.25 | UNSUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_mcm25, 418526);

    cout << "=== MULTIPLICATIVE CONGRUENTIAL METHOD | LOAD FACTOR 0.50 | SUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_mcm50, 545530);

    cout << "=== MULTIPLICATIVE CONGRUENTIAL METHOD | LOAD FACTOR 0.50 | UNSUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_mcm50, 418526);

    cout << "=== MULTIPLICATIVE CONGRUENTIAL METHOD | LOAD FACTOR 0.75 | SUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_mcm75, 545530);

    cout << "=== MULTIPLICATIVE CONGRUENTIAL METHOD | LOAD FACTOR 0.75 | UNSUCCESSFUL SEARCH ===" << endl;
    test_search(hashtable_mcm75, 418526);

    return 0;
}

void test_search(hash_table& hashtable, int key) {
    LARGE_INTEGER freq, start, end;

    QueryPerformanceFrequency(&freq);

    int iterations = 10000;
    double time_taken = 0;

    // get average runtime out of 10000 iterations
    for (int i = 0; i < iterations; i++) {
        QueryPerformanceCounter(&start);
        hashtable.get_value(key);
//        hashtable.find_key(key);
//        cout << "Key: " << key << endl;
//        cout << "Value: " << hashtable.get_value(key) << endl;
//        cout << "Key Comparisons Made: " << hashtable.find_key(key) << endl;
        QueryPerformanceCounter(&end);
        time_taken += (double) (end.QuadPart - start.QuadPart) / freq.QuadPart;
    }
    cout << "Average runtime in microseconds: " << time_taken*1000000/iterations << endl << endl;
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
