#include <iostream>
#include "bigint.hpp"

int main() {
    // Création de bigints
    bigint num1("00200"), num2("42"), num3, num4(100);
    bigint num5 = num2;
    const bigint numC(60);

    // Test des opérateurs arithmétiques
    std::cout << "num1 + num2 = " << (num1 + num2) << std::endl;
    num3 = num1;
    num3 += num2;
    std::cout << "num3 += num2: " << num3 << std::endl;

    // Test des comparaisons
    std::cout << "num1 == num2: " << (num1 == num2) << std::endl;
    std::cout << "num1 != num2: " << (num1 != num2) << std::endl;
    std::cout << "num1 < num2: " << (num1 < num2) << std::endl;
    std::cout << "num1 <= num2: " << (num1 <= num2) << std::endl;
    std::cout << "num1 > num2: " << (num1 > num2) << std::endl;
    std::cout << "num1 >= num2: " << (num1 >= num2) << std::endl;

    // Test des décalages avec entiers
    std::cout << "num1 << 2 = " << (num1 << 2) << std::endl;
    std::cout << "num1 >> 2 = " << (num1 >> 2) << std::endl;

    // Test des décalages avec bigint
    std::cout << "num1 << num5 = " << (num1 << num5) << std::endl;
    std::cout << "num1 >> num5 = " << (num1 >> num5) << std::endl;

    // Test des décalages avec bigint constant
    std::cout << "num1 << numC = " << (num1 << numC) << std::endl;
    std::cout << "num1 >> numC = " << (num1 >> numC) << std::endl;

    // Test des affectations combinées avec décalages
    num3 = num1;
    num3 <<= 2;
    std::cout << "num3 <<= 2: " << num3 << std::endl;
    num3 >>= 1;
    std::cout << "num3 >>= 1: " << num3 << std::endl;

    // Test des affectations combinées avec bigint
    num3 = num1;
    num3 <<= num5;
    std::cout << "num3 <<= num5: " << num3 << std::endl;
    num3 >>= num5;
    std::cout << "num3 >>= num5: " << num3 << std::endl;
    std::cout << bigint("0") << std::endl;           // 0
std::cout << bigint("000000") << std::endl;      // 0
std::cout << bigint("00000123") << std::endl;    // 123
std::cout << bigint("98700") << std::endl;       // 98700

    bigint b1("12345");
    std::cout << "b1 (12345) = " << b1 << std::endl; // Beklenen: 12345

    bigint b2("0000123");
    std::cout << "b2 (0000123) = " << b2 << std::endl; // Beklenen: 123

    bigint b3("0");
    std::cout << "b3 (0) = " << b3 << std::endl; // Beklenen: 0

    // Hatalı girişler
    bigint b4("");            // boş string
    std::cout << "b4 (\"\") = " << b4 << std::endl; // Beklenen: 0

    bigint b5("12a34");       // içinde harf var
    std::cout << "b5 (12a34) = " << b5 << std::endl; // Beklenen: 0

    bigint b6("!@#111");         // tamamen geçersiz karakterler
    std::cout << "b6 (!@#) = " << b6 << std::endl; // Beklenen: 0


     bigint a("5");

    std::cout << "Başlangıç: a = " << a << std::endl;

    // Prefix increment
    ++a;
    std::cout << "Prefix ++a: " << a << std::endl; // 6

    // Postfix increment
    a++;
    std::cout << "Postfix a++: " << a << std::endl; // 7

    // Postfix sonucu atama
    bigint b = a++;
    std::cout << "Postfix atama b = a++: b = " << b << ", a = " << a << std::endl;
    // b = 7, a = 8

    // Prefix sonucu atama
    bigint c = ++a;
    std::cout << "Prefix atama c = ++a: c = " << c << ", a = " << a << std::endl;
    // c = 9, a = 9

bigint h("000");
bigint j("0");
std::cout << h << " == " << j << ": " << (h == j) << std::endl;
std::cout << "h + j = " << (h + j) << std::endl; 


bigint k("1000");
std::cout << "k >> 3 = " << (k >> 3) << std::endl; // 1
std::cout << "k << 2 = " << (k << 2) << std::endl; // 100000
std::cout << "h + k = " << (h + k) << std::endl; //


bigint l("999999999999999999999");
std::cout<< "l: " << l << std::endl;
bigint g("1");
std::cout << "l + g = " << (l + g) << std::endl; // 1000000000000000000000
// ===== EK TESTLER =====

// 1. Büyük sayılarla toplama ve taşma
bigint big1("999999999999999999999999999999");
bigint big2("1");
std::cout << "big1 + big2 = " << (big1 + big2) << std::endl; // taşma kontrolü

// 2. Sıfır ve boş string kombinasyonları
bigint zero1("0"), zero2("00000"), empty("");
std::cout << "0 + 00000 = " << (zero1 + zero2) << std::endl;
std::cout << "0 + \"\" = " << (zero1 + empty) << std::endl;

// 3. Sadece sıfırlardan oluşan stringler
bigint allZeros("0000000000");
std::cout << "allZeros = " << allZeros << std::endl; // 0 olmalı

// 4. Geçersiz karakterler
bigint invalid1("12a34"), invalid2("!!@@##");
std::cout << "invalid1 = " << invalid1 << std::endl; // 0 olmalı
std::cout << "invalid2 = " << invalid2 << std::endl; // 0 olmalı

// 5. Shift ile sınır durumları
bigint shiftTest("1");
std::cout << "1 << 0 = " << (shiftTest << 0) << std::endl; // değişmemeli
std::cout << "1 >> 0 = " << (shiftTest >> 0) << std::endl; // değişmemeli
std::cout << "1 << 100 = " << (shiftTest << 100) << std::endl; // çok büyük shift
std::cout << "1 >> 100 = " << (shiftTest >> 100) << std::endl; // çok büyük shift, 0 olmalı

// 6. Increment / Decrement sınırları
bigint incDec("0");
++incDec;
std::cout << "++0 = " << incDec << std::endl; // 1


// 7. Karşılaştırma özel durumları
bigint cmp1("00123"), cmp2("123"), cmp3("124");
std::cout << "cmp1 == cmp2: " << (cmp1 == cmp2) << std::endl; // 1
std::cout << "cmp1 < cmp3: " << (cmp1 < cmp3) << std::endl;   // 1
std::cout << "cmp3 > cmp2: " << (cmp3 > cmp2) << std::endl;   // 1

// 8. Toplama sonucu sıfır olması
bigint negSum1("0"), negSum2("0");
std::cout << "0 + 0 = " << (negSum1 + negSum2) << std::endl; // 0 olmalı

    return 0;
}