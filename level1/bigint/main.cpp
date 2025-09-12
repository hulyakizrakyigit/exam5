// #include <iostream>
// #include "bigint.hpp"

// int main() {
//     // Création de bigints
//     bigint num1("00200"), num2("42"), num3, num4(100);
//     bigint num5 = num2;
//     const bigint numC(60);

//     // Test des opérateurs arithmétiques
//     std::cout << "num1 + num2 = " << (num1 + num2) << std::endl;
//     num3 = num1;
//     num3 += num2;
//     std::cout << "num3 += num2: " << num3 << std::endl;

//     // Test des comparaisons
//     std::cout << "num1 == num2: " << (num1 == num2) << std::endl;
//     std::cout << "num1 != num2: " << (num1 != num2) << std::endl;
//     std::cout << "num1 < num2: " << (num1 < num2) << std::endl;
//     std::cout << "num1 <= num2: " << (num1 <= num2) << std::endl;
//     std::cout << "num1 > num2: " << (num1 > num2) << std::endl;
//     std::cout << "num1 >= num2: " << (num1 >= num2) << std::endl;

//     // Test des décalages avec entiers
//     std::cout << "num1 << 2 = " << (num1 << 2) << std::endl;
//     std::cout << "num1 >> 2 = " << (num1 >> 2) << std::endl;

//     // Test des décalages avec bigint
//     std::cout << "num1 << num5 = " << (num1 << num5) << std::endl;
//     std::cout << "num1 >> num5 = " << (num1 >> num5) << std::endl;

//     // Test des décalages avec bigint constant
//     std::cout << "num1 << numC = " << (num1 << numC) << std::endl;
//     std::cout << "num1 >> numC = " << (num1 >> numC) << std::endl;

//     // Test des affectations combinées avec décalages
//     num3 = num1;
//     num3 <<= 2;
//     std::cout << "num3 <<= 2: " << num3 << std::endl;
//     num3 >>= 1;
//     std::cout << "num3 >>= 1: " << num3 << std::endl;

//     // Test des affectations combinées avec bigint
//     num3 = num1;
//     num3 <<= num5;
//     std::cout << "num3 <<= num5: " << num3 << std::endl;
//     num3 >>= num5;
//     std::cout << "num3 >>= num5: " << num3 << std::endl;
//     std::cout << bigint("0") << std::endl;           // 0
// std::cout << bigint("000000") << std::endl;      // 0
// std::cout << bigint("00000123") << std::endl;    // 123
// std::cout << bigint("98700") << std::endl;       // 98700

//     bigint b1("12345");
//     std::cout << "b1 (12345) = " << b1 << std::endl; // Beklenen: 12345

//     bigint b2("0000123");
//     std::cout << "b2 (0000123) = " << b2 << std::endl; // Beklenen: 123

//     bigint b3("0");
//     std::cout << "b3 (0) = " << b3 << std::endl; // Beklenen: 0

//     // Hatalı girişler
//     bigint b4("");            // boş string
//     std::cout << "b4 (\"\") = " << b4 << std::endl; // Beklenen: 0

//     bigint b5("12a34");       // içinde harf var
//     std::cout << "b5 (12a34) = " << b5 << std::endl; // Beklenen: 0

//     bigint b6("!@#111");         // tamamen geçersiz karakterler
//     std::cout << "b6 (!@#) = " << b6 << std::endl; // Beklenen: 0


//      bigint a("5");

//     std::cout << "Başlangıç: a = " << a << std::endl;

//     // Prefix increment
//     ++a;
//     std::cout << "Prefix ++a: " << a << std::endl; // 6

//     // Postfix increment
//     a++;
//     std::cout << "Postfix a++: " << a << std::endl; // 7

//     // Postfix sonucu atama
//     bigint b = a++;
//     std::cout << "Postfix atama b = a++: b = " << b << ", a = " << a << std::endl;
//     // b = 7, a = 8

//     // Prefix sonucu atama
//     bigint c = ++a;
//     std::cout << "Prefix atama c = ++a: c = " << c << ", a = " << a << std::endl;
//     // c = 9, a = 9

// bigint h("000");
// bigint j("0");
// std::cout << h << " == " << j << ": " << (h == j) << std::endl;
// std::cout << "h + j = " << (h + j) << std::endl; 


// bigint k("1000");
// std::cout << "k >> 3 = " << (k >> 3) << std::endl; // 1
// std::cout << "k << 2 = " << (k << 2) << std::endl; // 100000
// std::cout << "h + k = " << (h + k) << std::endl; //


// bigint l("999999999999999999999");
// std::cout<< "l: " << l << std::endl;
// bigint g("1");
// std::cout << "l + g = " << (l + g) << std::endl; // 1000000000000000000000
// // ===== EK TESTLER =====

// // 1. Büyük sayılarla toplama ve taşma
// bigint big1("999999999999999999999999999999");
// bigint big2("1");
// std::cout << "big1 + big2 = " << (big1 + big2) << std::endl; // taşma kontrolü

// // 2. Sıfır ve boş string kombinasyonları
// bigint zero1("0"), zero2("00000"), empty("");
// std::cout << "0 + 00000 = " << (zero1 + zero2) << std::endl;
// std::cout << "0 + \"\" = " << (zero1 + empty) << std::endl;

// // 3. Sadece sıfırlardan oluşan stringler
// bigint allZeros("0000000000");
// std::cout << "allZeros = " << allZeros << std::endl; // 0 olmalı

// // 4. Geçersiz karakterler
// bigint invalid1("12a34"), invalid2("!!@@##");
// std::cout << "invalid1 = " << invalid1 << std::endl; // 0 olmalı
// std::cout << "invalid2 = " << invalid2 << std::endl; // 0 olmalı

// // 5. Shift ile sınır durumları
// bigint shiftTest("1");
// std::cout << "1 << 0 = " << (shiftTest << 0) << std::endl; // değişmemeli
// std::cout << "1 >> 0 = " << (shiftTest >> 0) << std::endl; // değişmemeli
// std::cout << "1 << 100 = " << (shiftTest << 100) << std::endl; // çok büyük shift
// std::cout << "1 >> 100 = " << (shiftTest >> 100) << std::endl; // çok büyük shift, 0 olmalı

// // 6. Increment / Decrement sınırları
// bigint incDec("0");
// ++incDec;
// std::cout << "++0 = " << incDec << std::endl; // 1


// // 7. Karşılaştırma özel durumları
// bigint cmp1("00123"), cmp2("123"), cmp3("124");
// std::cout << "cmp1 == cmp2: " << (cmp1 == cmp2) << std::endl; // 1
// std::cout << "cmp1 < cmp3: " << (cmp1 < cmp3) << std::endl;   // 1
// std::cout << "cmp3 > cmp2: " << (cmp3 > cmp2) << std::endl;   // 1

// // 8. Toplama sonucu sıfır olması
// bigint negSum1("0"), negSum2("0");
// std::cout << "0 + 0 = " << (negSum1 + negSum2) << std::endl; // 0 olmalı




//     return 0;
// }



#include "bigint.hpp"
#include <iostream>

int main() {
    std::cout << "BigInt Test Starting..." << std::endl;
    
    // Test constructor
    bigint a("123");
    bigint b("456");
    
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    
    // Test addition
    bigint c = a + b;
    std::cout << "a + b = " << c << std::endl;
    
    // Test shift operations if they exist
    try {
        bigint d = a << bigint("2");
        std::cout << "a << 2 = " << d << std::endl;
        
        bigint e = a >> 1;
        std::cout << "a >> 1 = " << e << std::endl;
    } catch (...) {
        std::cout << "Shift operations not available" << std::endl;
    }
    
    // Test leading zero cases
    std::cout << "\n=== Leading Zero Tests ===" << std::endl;
    
    bigint zero1("0");
    bigint zero2("00");
    bigint zero3("000");
    bigint zero4("0000");
    
    std::cout << "bigint(\"0\") = " << zero1 << std::endl;
    std::cout << "bigint(\"00\") = " << zero2 << std::endl;
    std::cout << "bigint(\"000\") = " << zero3 << std::endl;
    std::cout << "bigint(\"0000\") = " << zero4 << std::endl;
    
    bigint leading1("007");
    bigint leading2("00123");
    bigint leading3("000456");
    bigint leading4("0000000789");
    
    std::cout << "bigint(\"007\") = " << leading1 << std::endl;
    std::cout << "bigint(\"00123\") = " << leading2 << std::endl;
    std::cout << "bigint(\"000456\") = " << leading3 << std::endl;
    std::cout << "bigint(\"0000000789\") = " << leading4 << std::endl;
    
    // Test arithmetic with leading zeros
    std::cout << "\n=== Arithmetic with Leading Zeros ===" << std::endl;
    bigint sum1 = leading2 + leading3;  // 00123 + 000456
    std::cout << "00123 + 000456 = " << sum1 << std::endl;
    
    bigint sum2 = zero1 + leading1;     // 0 + 007  
    std::cout << "0 + 007 = " << sum2 << std::endl;
    
    // Test shift operations with leading zeros
    std::cout << "\n=== Shift Operations with Leading Zeros ===" << std::endl;
    try {
        bigint shift1 = leading1 << 2;      // 007 << 2
        std::cout << "007 << 2 = " << shift1 << std::endl;
        
        bigint shift2 = leading2 << 1;      // 00123 << 1  
        std::cout << "00123 << 1 = " << shift2 << std::endl;
        
        bigint shift3 = leading4 >> 2;      // 0000000789 >> 2
        std::cout << "0000000789 >> 2 = " << shift3 << std::endl;
        
        bigint shift4 = zero3 << 5;         // 000 << 5
        std::cout << "000 << 5 = " << shift4 << std::endl;
        
        bigint shift5 = leading3 >> 1;      // 000456 >> 1
        std::cout << "000456 >> 1 = " << shift5 << std::endl;
        
    } catch (...) {
        std::cout << "Leading zero shift operations failed" << std::endl;
    }
    
    // Test big number shift operations
    std::cout << "\n=== Big Number Shift Tests ===" << std::endl;
    
    bigint big1("123456789012345");
    bigint big2("999999999999999999999");
    bigint big3("1000000000000000000000000");
    
    std::cout << "big1 = " << big1 << std::endl;
    std::cout << "big2 = " << big2 << std::endl;
    std::cout << "big3 = " << big3 << std::endl;
    
    try {
        // Large left shifts
        bigint bigShift1 = big1 << 5;
        std::cout << "123456789012345 << 5 = " << bigShift1 << std::endl;
        
        bigint bigShift2 = big1 << 10;
        std::cout << "123456789012345 << 10 = " << bigShift2 << std::endl;
        
        bigint bigShift3 = big2 << 3;
        std::cout << "999999999999999999999 << 3 = " << bigShift3 << std::endl;
        
        // Large right shifts
        bigint bigShift4 = big3 >> 6;
        std::cout << "1000000000000000000000000 >> 6 = " << bigShift4 << std::endl;
        
        bigint bigShift5 = big2 >> 10;
        std::cout << "999999999999999999999 >> 10 = " << bigShift5 << std::endl;
        
        // Edge case: shift more than digits
        bigint bigShift6 = big1 >> 20;
        std::cout << "123456789012345 >> 20 = " << bigShift6 << std::endl;
        
        bigint bigShift7 = bigint("1") << 500;
        std::cout << "1 << 50 = " << bigShift7 << std::endl;
        
    } catch (...) {
        std::cout << "Big number shift operations failed" << std::endl;
    }
    
    std::cout << "Test completed!" << std::endl;
    return 0;
}
