#include <iostream>
#include <fstream>  // for file I/O
#include <string>
#include <sstream>  // stringstream
#include <cstdlib>
#include <windows.h>

#include <bits/stdc++.h>    // for getting clock/time

#include "hashtable.h"
#include "hashfunction.h"
#include "hashtableprinter.h"

using std::cout;
using std::endl;
using std::string;
using namespace hash;

// function prototypes
void test_search(hash_table&, int[]);
void test_codes();


void read_csv_data(hash_table&);
void test_by_load_factor(int, const char*, hash_table*);
void create_hashtables();
void linear_search_worstcase();

const int numRecords = 121397;

#define NUM_HF 3    // number of hash functions

const string hf_names[NUM_HF] = {
    "Division Method",
    "Mid-Square Method",
    "Multiplicative Congruential Method"
};

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

    // Create hash tables
    hash_table hashTLoadFactor25[NUM_HF] = { hash_table(nLoadFactor25, hash::division_method),
        hash_table(nLoadFactor25, hash::mid_square_method),
        hash_table(nLoadFactor25, hash::multiplicative_congruential_method)
    };
    hash_table hashTLoadFactor50[NUM_HF] = { hash_table(nLoadFactor50, hash::division_method),
        hash_table(nLoadFactor50, hash::mid_square_method),
        hash_table(nLoadFactor50, hash::multiplicative_congruential_method)
    };
    hash_table hashTLoadFactor75[NUM_HF] = { hash_table(nLoadFactor75, hash::division_method),
        hash_table(nLoadFactor75, hash::mid_square_method),
        hash_table(nLoadFactor75, hash::multiplicative_congruential_method)
    };
    hash_table hashTLoadFactor100[NUM_HF] = { hash_table(nLoadFactor100, hash::division_method),
        hash_table(nLoadFactor100, hash::mid_square_method),
        hash_table(nLoadFactor100, hash::multiplicative_congruential_method)
    };
    hash_table hashTLoadFactor200[NUM_HF] = { hash_table(nLoadFactor200, hash::division_method),
        hash_table(nLoadFactor200, hash::mid_square_method),
        hash_table(nLoadFactor200, hash::multiplicative_congruential_method)
    };
    for (int i = 0; i < NUM_HF; ++i) {
        read_csv_data(hashTLoadFactor25[i]);
        read_csv_data(hashTLoadFactor50[i]);
        read_csv_data(hashTLoadFactor75[i]);
        read_csv_data(hashTLoadFactor100[i]);
        read_csv_data(hashTLoadFactor200[i]);
    }

    // function loop
    cout << "== CLOSED ADDRESS HASHING COMPARISON PROGRAM ==" << endl;
    int choice;
    do {
        cout << "(1) LOAD FACTOR 0.25" << endl
            << "(2) LOAD FACTOR 0.5" << endl
            << "(3) LOAD FACTOR 0.75" << endl
            << "(4) LOAD FACTOR 1.00" << endl
            << "(5) LOAD FACTOR 2.00" << endl
            << "(6) LINEAR SEARCH (FOR COMPARISON)" << endl
            << "(7) QUIT" << endl
            << "Enter option: ";
        scanf("%d", &choice);

        switch (choice) {
        case 1: test_by_load_factor(nLoadFactor25, "0.25", hashTLoadFactor25);
            break;
        case 2: test_by_load_factor(nLoadFactor50, "0.5", hashTLoadFactor50);
            break;
        case 3: test_by_load_factor(nLoadFactor75, "0.75", hashTLoadFactor75);
            break;
        case 4: test_by_load_factor(nLoadFactor100, "1.00", hashTLoadFactor100);
            break;
        case 5: test_by_load_factor(nLoadFactor200, "2.00", hashTLoadFactor200);
            break;
        case 6: linear_search_worstcase();
            break;
        case 7: // quit
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }

    } while (choice != 7);

    return 0;
}

void test_by_load_factor(int slots, const char* loadfactor, hash_table* hashtables) {
    cout << "Load Factor : " << loadfactor << " | No. of slots : " << slots << endl << endl;
    cout << "==== Key Distribution ====" << endl;
    for (int i = 0; i < NUM_HF; ++i) {
        cout << ">> " << hf_names[i] << endl;
        hash_table_printer::printKeyDistribution(hashtables[i]);
    }

    int choice;
    int successful_keys[10] = {18948, 258360, 329910, 417821, 536832, 618322, 669018, 751352, 807976, 821327};
    int unsuccessful_keys[10] = {89700, 209283, 349871, 426734, 518637, 579550, 658899, 757789, 807802, 807963};
    int *keys;

    do {
        cout << "======================" << endl
            << "(1) SUCCESSFUL SEARCH" << endl
            << "(2) UNSUCCESSFUL SEARCH" << endl
            << "(3) QUIT" << endl
            << "Enter option: ";
        scanf("%d", &choice);

        switch (choice) {
        case 1: keys = successful_keys;
            break;
        case 2: keys = unsuccessful_keys;
            break;
        case 3:
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
    } while (choice < 1 && choice > 3);

    if (choice == 3) return;

    cout << endl << "Key Search: " << endl;
    for (int i = 0; i < 10; ++i) {
        cout << keys[i] << " ";
    }
    cout << endl << endl << "==== Average CPU Time ====" << endl;

    for (int i = 0; i < NUM_HF; ++i) {
        cout << endl << ">> " << hf_names[i] << endl;
        test_search(hashtables[i], keys);
    }
}

void test_search(hash_table& hashtable, int keys[]) {
    LARGE_INTEGER freq, start, end;

    QueryPerformanceFrequency(&freq);

    int iterations = 10000;
    double time_taken = 0;

    // get average runtime out of 10000 iterations
    for (int i = 0; i < iterations; i++) {
        QueryPerformanceCounter(&start);
        for (int j = 0; j < 10; j++) {
            hashtable.get_value(keys[j]);
//            hashtable.find_key(key);
//            cout << "Key: " << key << endl;
//            cout << "Value: " << hashtable.get_value(key) << endl;
//            cout << "Key Comparisons Made: " << hashtable.find_key(key) << endl;
        }
        QueryPerformanceCounter(&end);
        time_taken += (double) (end.QuadPart - start.QuadPart) / freq.QuadPart;
    }
    cout << "Average runtime of 10 searches in microseconds: " << time_taken*1000000/iterations << endl << endl;
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

void linear_search_worstcase() {
    int arr[121397];

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    int iterations = 1000;
    double time_taken = 0;
    for (int x = 0; x < iterations; x++) {
        QueryPerformanceCounter(&start);
        for (int i = 0; i < 121397; ++i) {
            if (arr[i] == INT_MAX)
                break;
        }
        QueryPerformanceCounter(&end);
        time_taken += (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    }
    cout << "==== Average CPU Time ====" << endl;
    cout << "Average worst-case runtime in microseconds: " << time_taken * 1000000 / iterations << endl;
}
