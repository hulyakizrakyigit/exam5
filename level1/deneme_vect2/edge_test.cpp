#include "vect2.hpp"
#include <iostream>
#include <climits>

void test_extreme_values() {
    std::cout << "=== Testing Extreme Values ===" << std::endl;
    
    vect2 v_max(INT_MAX, INT_MAX);
    vect2 v_min(INT_MIN, INT_MIN);
    vect2 v_zero(0, 0);
    
    std::cout << "INT_MAX vector: " << v_max << std::endl;
    std::cout << "INT_MIN vector: " << v_min << std::endl;
    std::cout << "Zero vector: " << v_zero << std::endl;
    
    // Test overflow conditions
    std::cout << "\n--- Overflow Tests ---" << std::endl;
    vect2 v_big(INT_MAX - 1, INT_MAX - 1);
    std::cout << "Before increment: " << v_big << std::endl;
    v_big++;
    std::cout << "After increment (overflow): " << v_big << std::endl;
    
    vect2 v_small(INT_MIN + 1, INT_MIN + 1);
    std::cout << "Before decrement: " << v_small << std::endl;
    v_small--;
    std::cout << "After decrement (underflow): " << v_small << std::endl;
}

void test_self_operations() {
    std::cout << "\n=== Testing Self Operations ===" << std::endl;
    
    vect2 v(5, 10);
    std::cout << "Original v: " << v << std::endl;
    
    // Self assignment
    v = v;
    std::cout << "After self assignment: " << v << std::endl;
    
    // Self operations
    v = v + v;
    std::cout << "v = v + v: " << v << std::endl;
    
    v = v - v;
    std::cout << "v = v - v: " << v << std::endl;
    
    vect2 v2(3, 4);
    v2 = v2 * v2;
    std::cout << "v2 = v2 * v2: " << v2 << std::endl;
}

void test_chained_operations() {
    std::cout << "\n=== Testing Complex Chained Operations ===" << std::endl;
    
    vect2 a(1, 2);
    vect2 b(3, 4);
    vect2 c(5, 6);
    
    std::cout << "a: " << a << "b: " << b << "c: " << c << std::endl;
    
    // Complex expression
    vect2 result = (a + b) * (c - a) + (b * 2);
    std::cout << "(a+b)*(c-a)+(b*2): " << result << std::endl;
    
    // Chained assignments
    a += b += c;
    std::cout << "After a += b += c:" << std::endl;
    std::cout << "a: " << a << "b: " << b << "c: " << c << std::endl;
}

void test_index_edge_cases() {
    std::cout << "\n=== Testing Index Edge Cases ===" << std::endl;
    
    vect2 v(100, 200);
    std::cout << "v: " << v << std::endl;
    
    // Valid indices
    std::cout << "v[0]: " << v[0] << std::endl;
    std::cout << "v[1]: " << v[1] << std::endl;
    
    // Invalid indices (should return y according to implementation)
    std::cout << "v[2]: " << v[2] << std::endl;
    std::cout << "v[-1]: " << v[-1] << std::endl;
    std::cout << "v[999]: " << v[999] << std::endl;
    
    // Modify through invalid index
    v[5] = 777;
    std::cout << "After v[5] = 777: " << v << std::endl;
    
    const vect2 cv(50, 60);
    std::cout << "const vector cv[0]: " << cv[0] << std::endl;
    std::cout << "const vector cv[10]: " << cv[10] << std::endl;
}

void test_comparison_edge_cases() {
    std::cout << "\n=== Testing Comparison Edge Cases ===" << std::endl;
    
    vect2 v1(0, 0);
    vect2 v2(0, 0);
    vect2 v3(0, 1);
    vect2 v4(1, 0);
    
    std::cout << "v1(0,0) == v2(0,0): " << (v1 == v2) << std::endl;
    std::cout << "v1(0,0) == v3(0,1): " << (v1 == v3) << std::endl;
    std::cout << "v1(0,0) == v4(1,0): " << (v1 == v4) << std::endl;
    
    std::cout << "v1(0,0) != v2(0,0): " << (v1 != v2) << std::endl;
    std::cout << "v1(0,0) != v3(0,1): " << (v1 != v3) << std::endl;
    
    // Edge case: one component same, other different
    vect2 v5(INT_MAX, 0);
    vect2 v6(INT_MAX, 1);
    std::cout << "v5(MAX,0) == v6(MAX,1): " << (v5 == v6) << std::endl;
    std::cout << "v5(MAX,0) != v6(MAX,1): " << (v5 != v6) << std::endl;
}

void test_operator_precedence() {
    std::cout << "\n=== Testing Operator Precedence ===" << std::endl;
    
    vect2 a(2, 3);
    vect2 b(4, 5);
    
    std::cout << "a: " << a << "b: " << b << std::endl;
    
    // Test precedence: multiplication vs addition
    vect2 r1 = a + b * 2;  // Should be a + (b * 2)
    vect2 r2 = (a + b) * 2;
    
    std::cout << "a + b * 2: " << r1 << std::endl;
    std::cout << "(a + b) * 2: " << r2 << std::endl;
    
    // Test with unary minus
    vect2 r3 = -a + b;
    vect2 r4 = -(a + b);
    
    std::cout << "-a + b: " << r3 << std::endl;
    std::cout << "-(a + b): " << r4 << std::endl;
}

void test_copy_semantics() {
    std::cout << "\n=== Testing Copy Semantics ===" << std::endl;
    
    vect2 original(10, 20);
    std::cout << "Original: " << original << std::endl;
    
    // Copy constructor
    vect2 copy1(original);
    std::cout << "Copy constructor: " << copy1 << std::endl;
    
    // Assignment operator
    vect2 copy2;
    copy2 = original;
    std::cout << "Assignment operator: " << copy2 << std::endl;
    
    // Modify original, check copies are independent
    original[0] = 999;
    std::cout << "After modifying original[0] to 999:" << std::endl;
    std::cout << "Original: " << original << std::endl;
    std::cout << "Copy1: " << copy1 << std::endl;
    std::cout << "Copy2: " << copy2 << std::endl;
}

int main() {
    std::cout << "🧪 COMPREHENSIVE EDGE CASE TESTING FOR vect2 🧪\n" << std::endl;
    
    test_extreme_values();
    test_self_operations();
    test_chained_operations();
    test_index_edge_cases();
    test_comparison_edge_cases();
    test_operator_precedence();
    test_copy_semantics();
    
    std::cout << "\n✅ All edge case tests completed!" << std::endl;
    return 0;
}
