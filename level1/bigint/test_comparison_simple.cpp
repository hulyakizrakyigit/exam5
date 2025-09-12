#include <iostream>
#include "bigint.hpp"

int main() {
    bigint num1("200");
    bigint num2("42");
    
    std::cout << "num1 = " << num1 << std::endl;
    std::cout << "num2 = " << num2 << std::endl;
    std::cout << "num1 < num2: " << (num1 < num2) << std::endl;
    std::cout << "num1 > num2: " << (num1 > num2) << std::endl;
    std::cout << "num1 == num2: " << (num1 == num2) << std::endl;
    
    return 0;
}
