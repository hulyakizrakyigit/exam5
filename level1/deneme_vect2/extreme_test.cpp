#include "vect2.hpp"
#include <iostream>
#include <climits>

void test_critical_overflow() {
    std::cout << "=== CRITICAL OVERFLOW TESTS ===" << std::endl;
    
    // Test actual overflow scenarios
    vect2 max_vec(INT_MAX, INT_MAX);
    std::cout << "MAX vector: " << max_vec << std::endl;
    
    // This should cause overflow
    try {
        vect2 result = max_vec + vect2(1, 1);
        std::cout << "MAX + (1,1) = " << result << std::endl;
    } catch(...) {
        std::cout << "Exception caught in addition" << std::endl;
    }
    
    // Multiplication overflow
    vect2 big_vec(INT_MAX / 2, INT_MAX / 2);
    std::cout << "Big vector: " << big_vec << std::endl;
    vect2 mult_result = big_vec * 3;
    std::cout << "Big * 3 = " << mult_result << std::endl;
    
    // Division by zero behavior (no division operator, but let's test multiplication by 0)
    vect2 any_vec(123, 456);
    vect2 zero_mult = any_vec * 0;
    std::cout << "Any vector * 0 = " << zero_mult << std::endl;
    
    // Negative overflow
    vect2 min_vec(INT_MIN, INT_MIN);
    std::cout << "MIN vector: " << min_vec << std::endl;
    vect2 neg_result = min_vec - vect2(1, 1);
    std::cout << "MIN - (1,1) = " << neg_result << std::endl;
    
    // Unary minus on MIN value
    vect2 min_single(INT_MIN, 0);
    std::cout << "MIN value: " << min_single << std::endl;
    vect2 negated = -min_single;
    std::cout << "-MIN = " << negated << std::endl;
}

void test_assignment_chain() {
    std::cout << "\n=== ASSIGNMENT CHAIN TESTS ===" << std::endl;
    
    vect2 a(1, 1);
    vect2 b(2, 2);
    vect2 c(3, 3);
    vect2 d(4, 4);
    
    std::cout << "Initial: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
    
    // Chain assignment
    a = b = c = d;
    std::cout << "After a=b=c=d: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
    
    // Complex chain
    vect2 x(10, 20);
    vect2 y(30, 40);
    a += b *= c -= d;
    std::cout << "After a += b *= c -= d:" << std::endl;
    std::cout << "a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
}

void test_increment_decrement_edge() {
    std::cout << "\n=== INCREMENT/DECREMENT EDGE CASES ===" << std::endl;
    
    // Test with extreme values
    vect2 almost_max(INT_MAX - 1, INT_MAX - 1);
    std::cout << "Almost MAX: " << almost_max << std::endl;
    
    vect2 post_inc = almost_max++;
    std::cout << "Post increment result: " << post_inc << std::endl;
    std::cout << "After post increment: " << almost_max << std::endl;
    
    vect2 pre_inc = ++almost_max;
    std::cout << "Pre increment result: " << pre_inc << std::endl;
    std::cout << "After pre increment: " << almost_max << std::endl;
    
    // Test with negative values
    vect2 almost_min(INT_MIN + 1, INT_MIN + 1);
    std::cout << "Almost MIN: " << almost_min << std::endl;
    
    vect2 post_dec = almost_min--;
    std::cout << "Post decrement result: " << post_dec << std::endl;
    std::cout << "After post decrement: " << almost_min << std::endl;
    
    vect2 pre_dec = --almost_min;
    std::cout << "Pre decrement result: " << pre_dec << std::endl;
    std::cout << "After pre decrement: " << almost_min << std::endl;
}

int main() {
    std::cout << "🔥 EXTREME EDGE CASE TESTING 🔥\n" << std::endl;
    
    test_critical_overflow();
    test_assignment_chain();
    test_increment_decrement_edge();
    
    std::cout << "\n🎯 Extreme edge case tests completed!" << std::endl;
    return 0;
}
