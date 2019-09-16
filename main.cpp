#include <iostream>
#include <fstream>  // for file I/O
#include <string>
#include <sstream>  // stringstream
#include <cstdlib>
#include <windows.h>

#include "hashtable.h"
#include "hashfunction.h"
#include "hashtableprinter.h"

using std::cout;
using std::endl;
using std::string;
using namespace hash;

// function prototypes
void test_search(hash_table&, int[], int);
void hash_demo();

void read_sampled_csv(int*, int, const char*);
void read_csv_data(hash_table**, int);
void test_by_load_factor(int, const char*, hash_table**);
void create_hashtables(hash_table**, int);
void linear_search_worstcase();
void hash_function_runtimes();

const int numRecords = 121397;

#define NUM_HF 3    // number of hash functions

const string hf_names[NUM_HF] = {
    "Division Method",
    "Mid-Square Method",
    "Multiplicative Congruential Method"
};

const int numSamples = 12000;   // 10% of data
int sampled_keys[numRecords];
int unsuccessful_keys[numSamples];

/*const int nLoadFactor25 = 485587;
const int nLoadFactor50 = 242797;
const int nLoadFactor75 = 161869;
const int nLoadFactor100 = 121403;
const int nLoadFactor200 = 60703;//262144;//200000;//50000;//100000;//65536;
//const int power2_16 = 65536;
*/

int tableSizesPrime[5] = {
    485587, // around 0.25
    242797, // around 0.5
    161869, // around 0.75
    121403, // around 1.00
    60703   // around 2.00
};

int tableSizes10Multiples[5] = {
    486000, // around 0.25
    243000, // around 0.5
    162000, // around 0.75
    121000, // around 1.00
    60700   // around 2.00
};

/*int tableSizesBase2[5] = {

};*/

int tableSizesExact[5] = {
    numRecords / 0.25,
    numRecords / 0.5,
    numRecords / 0.75,
    numRecords,
    numRecords / 2
};

int *tableSizes;

int main()
{
    // ==== TESTING ====
    //hash_demo();   // test codes for testing out the hash table

    // ==== ACTUAL APPLICATION ====
    // Create hash tables
    /*hash_table hashTLoadFactor25[NUM_HF] = { hash_table(nLoadFactor25, hash::division_method),
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
    // read csv data
    read_csv_data(hashTLoadFactor25, NUM_HF);
    read_csv_data(hashTLoadFactor50, NUM_HF);
    read_csv_data(hashTLoadFactor75, NUM_HF);
    read_csv_data(hashTLoadFactor100, NUM_HF);
    read_csv_data(hashTLoadFactor200, NUM_HF);*/

    // read sampled data subset
    //read_sampled_csv(sampled_keys, numSamples, "sample12000.csv");
    read_sampled_csv(sampled_keys, numRecords, "csvdata_searchval.csv");
    read_sampled_csv(unsuccessful_keys, numSamples, "unsuccessful.csv");

    cout << log2(65536)/2;

    // array of hash_table pointers
    hash_table** hash_tables = new hash_table*[NUM_HF]();
    tableSizes = &tableSizesPrime[0];

    // function loop
    cout << "== CLOSED ADDRESS HASHING COMPARISON PROGRAM ==" << endl;
    int choice;
    do {
        cout << "(1) LOAD FACTOR 0.25" << endl
            << "(2) LOAD FACTOR 0.5" << endl
            << "(3) LOAD FACTOR 0.75" << endl
            << "(4) LOAD FACTOR 1.00" << endl
            << "(5) LOAD FACTOR 2.00" << endl
            << "(6) SET TABLE SIZES TO PRIME NUMBERS" << endl
            << "(7) SET TABLE SIZES TO MULTIPLES OF 10" << endl
            << "(8) SET TABLE SIZES TO EXACT" << endl
            << "(9) LINEAR SEARCH (FOR COMPARISON)" << endl
            << "(10) HASH FUNCTION RUNTIMES" << endl
            << "(11) HASH TABLE DEMO" << endl
            << "(12) QUIT" << endl
            << "Enter option: ";
        scanf("%d", &choice);

        switch (choice) {
        case 1: create_hashtables(hash_tables, tableSizes[0]);
            test_by_load_factor(tableSizes[0], "0.25", hash_tables);
            break;
        case 2: create_hashtables(hash_tables, tableSizes[1]);
            test_by_load_factor(tableSizes[1], "0.5", hash_tables);
            break;
        case 3: create_hashtables(hash_tables, tableSizes[2]);
            test_by_load_factor(tableSizes[2], "0.75", hash_tables);
            break;
        case 4: create_hashtables(hash_tables, tableSizes[3]);
            test_by_load_factor(tableSizes[3], "1.00", hash_tables);
            break;
        case 5: create_hashtables(hash_tables, tableSizes[4]);
            test_by_load_factor(tableSizes[4], "2.00", hash_tables);
            break;
        case 6: tableSizes = &tableSizesPrime[0];
            cout << "Table sizes set to prime numbers" << endl << endl;
            break;
        case 7: tableSizes = &tableSizes10Multiples[0];
            cout << "Table sizes set to multiples of 10" << endl << endl;
            break;
        case 8: tableSizes = &tableSizesExact[0];
            cout << "Table sizes set to exact" << endl << endl;
            break;
        case 9: linear_search_worstcase();
            break;
        case 10: hash_function_runtimes();
            break;
        case 11: hash_demo();
            break;
        case 12: // quit
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }

    } while (choice != 12);

    delete hash_tables[0];
    delete hash_tables[1];
    delete hash_tables[2];
    delete[] hash_tables;

    return 0;
}

void test_by_load_factor(int slots, const char* loadfactor, hash_table** hashtables) {
    cout << "Load Factor : " << loadfactor << " | No. of slots : " << slots << endl << endl;
    cout << "==== Key Distribution ====" << endl;
    for (int i = 0; i < NUM_HF; ++i) {
        cout << ">> " << hf_names[i] << endl;
        int successful_key_comparisons = hash_table_printer::printKeyDistribution(*(hashtables[i]));
        cout << "Average key comparisons: " << (double) successful_key_comparisons/numRecords << endl << endl;
    }

    int choice;
    //int successful_keys[10] = {18948, 258360, 329910, 417821, 536832, 618322, 669018, 751352, 807976, 821327};
    //int unsuccessful_keys[10] = {89700, 209283, 349871, 426734, 518637, 579550, 658899, 757789, 807802, 807963};
    int *keys;

    do {
        cout << "======================" << endl
            << "(1) SUCCESSFUL SEARCH" << endl
            << "(2) UNSUCCESSFUL SEARCH" << endl
            << "Enter option: ";
        scanf("%d", &choice);

        switch (choice) {
        case 1: keys = sampled_keys;
            break;
        case 2: keys = unsuccessful_keys;
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
    } while (choice < 1 && choice > 2);

    //cout << endl << "Key Search: " << numSamples << " records" << endl;
    //for (int i = 0; i < 10; ++i) {
    //    cout << keys[i] << " ";
    //}
    cout << endl << "==== Average CPU Time ====" << endl;

    for (int i = 0; i < NUM_HF; ++i) {
        cout << endl << ">> " << hf_names[i] << endl;
        if (choice == 1)
            test_search(*(hashtables[i]), keys, numRecords);
        else // (choice == 2)
            test_search(*(hashtables[i]), keys, numSamples);
    }
}

void test_search(hash_table& hashtable, int keys[], int keysSize) {
    LARGE_INTEGER freq, start, end;

    QueryPerformanceFrequency(&freq);

    int iterations = 1;
    double time_taken = 0;

    cout << "Number of keys : " << keysSize <<endl;

    //int numKeyComp = 0;

    // get average runtime out of number of iterations
    for (int i = 0; i < iterations; i++) {
        QueryPerformanceCounter(&start);
        for (int j = 0; j < keysSize; j++) {
            //int keycomp = hashtable.find_key(keys[j]);
            //numKeyComp +=keycomp;
            hashtable.find_key(keys[j]);
//            hashtable.find_key(key);
//            cout << "Key: " << key << endl;
//            cout << "Value: " << hashtable.get_value(key) << endl;
//            cout << "Key Comparisons Made: " << hashtable.find_key(key) << endl;
        }
        QueryPerformanceCounter(&end);
        time_taken += (double) (end.QuadPart - start.QuadPart) / freq.QuadPart;
    }
    //float numComps = (float)numKeyComp/ (float)keysSize;
    int unitSize = 10;
    double unitSizePerKeysSize = (double)unitSize / keysSize;
    cout << "Average runtime of " << unitSize << " searches in microseconds: " << time_taken*(1000000/iterations)*unitSizePerKeysSize << endl;
    //cout << "Number of key comp: " << numComps << endl << endl;
}

void hash_demo() {

    // create hash table
    hash_table *hashtable;
    int bucketSize = 0;

    cout << "==== HASH TABLE DEMO ====" << endl;
    // select load factor
    cout << ">>Select Load Factor" << endl;
    cout << "(1) Load Factor 0.25" << endl
        << "(2) Load Factor 0.5" << endl
        << "(3) Load Factor 0.75" << endl
        << "(4) Load Factor 1.00" << endl
        << "(5) Load Factor 2.00" << endl;
    cout << "Enter option: ";
    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1: bucketSize = tableSizes[0];
        break;
    case 2: bucketSize = tableSizes[1];
        break;
    case 3: bucketSize = tableSizes[2];
        break;
    case 4: bucketSize = tableSizes[3];
        break;
    case 5: bucketSize = tableSizes[4];
        break;
    default:
        break;
    }

    // select hash function
    cout << endl << ">>Select Hash Function" << endl;
    cout << "(1) " << hf_names[0] << endl
        << "(2) " << hf_names[1] << endl
        << "(3) " << hf_names[2] << endl;
    cout << "Enter option: ";
    scanf("%d", &choice);
    switch (choice) {
    case 1: hashtable = new hash_table(bucketSize, hash::division_method);
        break;
    case 2: hashtable = new hash_table(bucketSize, hash::mid_square_method);
        break;
    case 3: hashtable = new hash_table(bucketSize, hash::multiplicative_congruential_method);
        break;
    default:
        break;
    }
    read_csv_data(&hashtable, 1);
    cout << "Hash Table created!" << endl;

    // test out key searches
    do {
        cout << endl
            << "(1) Find Key" << endl
            << "(2) Quit" << endl;
        cout << "Enter option: ";
        scanf("%d", &choice);
        switch (choice) {
        case 1:
        {
            int key;
            cout << "Enter target key: ";
            scanf("%d", &key);

            LARGE_INTEGER freq, start, end;
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&start);
            int numComparisons;
            for (int i = 0; i < 10; ++i) {
                numComparisons = hashtable->find_key(key);
            }
            QueryPerformanceCounter(&end);
            double time_taken = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;

            if (numComparisons == -1) { // error in hash function
                cout << "Hash function error" << endl;
            }
            else if (numComparisons == 0) { // key not found
                cout << "Key not found" << endl;
            }
            else {
                cout << "Key found! Number of Key Comparisons Made: " << numComparisons << endl;
                cout << "Value: " << hashtable->get_value(key) << endl;
            }
            cout << "Runtime (in microseconds): " << time_taken * (1000000/10) << endl;
        }
            break;
        case 2: // quit
            break;
        default: cout << "Invalid option" << endl;
            break;
        }
    } while (choice != 2);

    delete hashtable;

    // test insert & set value
    /*cout << hashtable.insert_element(7, "500") << endl;    // prints 1
    cout << hashtable.insert_element(2, "500") << endl;    // prints 1, but there will be collision in the hash table's slots
    cout << hashtable.insert_element(7, "555") << endl;    // prints 0; duplicate key
    cout << hashtable.set_value(7, "599") << endl;    // prints 1; new value set

    // test get values
    cout << "Key: 7  Value: " << hashtable.get_value(7) << endl;
    cout << "Key: 2  Value: " << hashtable.get_value(2) << endl;
    if (hashtable.get_value(8) == "")
        cout << "Key: 8  Value: (Not found)" << endl;*/
}

void read_csv_data(hash_table** hashtables, int n) {

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
            for (int i = 0; i < n; ++i) {
                hashtables[i]->insert_element(postalCode, token);
            }
        }
        csvfile.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

void linear_search_worstcase() {
    int arr[1213970] = {0};

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    int iterations = 100;
    double time_taken = 0;
    for (int x = 0; x < iterations; x++) {
        QueryPerformanceCounter(&start);
        for (int i = 0; i < 1213970; ++i) {
            if (arr[i] == INT_MAX)
                break;
        }
        QueryPerformanceCounter(&end);
        time_taken += (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    }
    cout << "==== Average CPU Time ====" << endl;
    cout << "Average worst-case runtime in microseconds: " << time_taken * 1000000 / iterations << endl;
}

void hash_function_runtimes() {

    cout << "==== Average Runtime of Hash Functions ====" << endl;

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    int iterations = 10000;
    int key = 123456;
    double time_taken = 0;
    for (int x = 0; x < NUM_HF; ++x) {
        cout << ">> " << hf_names[x] << endl;

        QueryPerformanceCounter(&start);
        for (int i = 0; i < iterations; ++i) {
            switch (x) {
            case 1: hash::division_method(key, 485587);
                break;
            case 2: hash::mid_square_method(key, 485587);
                break;
            case 3: hash::multiplicative_congruential_method(key, 485587);
                break;
            default:
                break;
            }
        }
        QueryPerformanceCounter(&end);

        time_taken += (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
        cout << "Time Taken in microseconds : " << time_taken * 1000000 / iterations << endl << endl;
    }
}

void read_sampled_csv(int* arr, int n, const char* filepath) {

    // read file
    std::ifstream csvfile(filepath);
    if (csvfile.is_open()) {
        string line; // to store each line from the CSV
        int i = 0;
        while (getline(csvfile, line))
        {
            std::stringstream ss(line);
            string token;
            std::getline(ss, token, ',');   // token = postal code
            int postalCode = std::atoi(token.c_str());
            arr[i++] = postalCode;
        }
        csvfile.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

void create_hashtables(hash_table** hash_tables, int tableSize) {

    if (hash_tables[0] != NULL) {

        delete hash_tables[0];
        delete hash_tables[1];
        delete hash_tables[2];
    }

    hash_tables[0] = new hash_table(tableSize, hash::division_method);
    hash_tables[1] = new hash_table(tableSize, hash::mid_square_method);
    hash_tables[2] = new hash_table(tableSize, hash::multiplicative_congruential_method);

    read_csv_data(hash_tables, NUM_HF);
}
