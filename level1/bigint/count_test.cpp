#include "bigint.hpp"
#include <iostream>
using namespace std;
int main() {
    bigint num("123");
    bigint shift("50");
    bigint result = num << shift;
    cout << "Result: " << result << endl;
    cout << "Length: " << result.toString().length() << endl;
    return 0;
}
