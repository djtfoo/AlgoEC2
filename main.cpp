#include <iostream>
#include "hashtable.h"
#include "hashfunction.h"

using std::cout;
using std::endl;

int main()
{
    hash_table hashtable(5, hash_function::division_method);
    cout << hashtable.insert_element(7, "500") << endl;    // prints 1
    cout << hashtable.insert_element(2, "500") << endl;    // prints 1, but there will be collision in the hash table's slots
    cout << hashtable.insert_element(7, "555") << endl;    // prints 0; duplicate key
    cout << hashtable.set_value(7, "555") << endl;    // will succeed

    // checking of get values
    cout << "Key: 7  Value: " << hashtable.get_value(7) << endl;
    cout << "Key: 2  Value: " << hashtable.get_value(2) << endl;
    if (hashtable.get_value(8) == NULL)
        cout << "Key: 8  Value: (NULL)" << endl;

    //delete hashtable;
    return 0;
}
