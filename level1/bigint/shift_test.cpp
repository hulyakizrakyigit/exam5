#include "bigint.hpp"
#include <iostream>
using namespace std;

int main() {
    bigint num("123");
    bigint small_shift("3");
    bigint big_shift("25");
    
    cout << "123 << 3 = " << (num << small_shift) << endl;
    cout << "123 << 25 = " << (num << big_shift) << endl;
    
    return 0;
}
