#include <iostream>
#include "vector.h"

int main() {
    // Test numeric vectors
    Vector<int> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    
    Vector<int> v2(3);
    v2[0] = 4; v2[1] = 5; v2[2] = 6;
    
    auto v3 = v1 + v2;
    v3 *= 2;
    
    std::cout << "v1: ";
    for(size_t i = 0; i < v1.getSize(); ++i) {
        std::cout << v1[i] << " ";
    }
    std::cout << "\n";
    
    // Test boolean vectors
    Vector<bool> bv1(10);
    bv1[0] = true;
    bv1[1] = false;
    bv1[2] = true;
    
    Vector<bool> bv2(10);
    bv2[0] = true;
    bv2[1] = true;
    bv2[2] = false;
    
    auto bv3 = bv1 + bv2;  // Should perform logical OR
    
    // Let's print the boolean vectors to verify
    std::cout << "bv1: ";
    for(size_t i = 0; i < 5; ++i) {  // Just print first 5 for brevity
        std::cout << (bv1[i] ? "true" : "false") << " ";
    }
    std::cout << "\n";
    
    std::cout << "bv2: ";
    for(size_t i = 0; i < 5; ++i) {
        std::cout << (bv2[i] ? "true" : "false") << " ";
    }
    std::cout << "\n";
    
    std::cout << "bv3 (bv1 + bv2): ";
    for(size_t i = 0; i < 5; ++i) {
        std::cout << (bv3[i] ? "true" : "false") << " ";
    }
    std::cout << "\n";
    
    // Let's also test the compound assignment operators
    std::cout << "v3 (v1 + v2) * 2: ";
    for(size_t i = 0; i < v3.getSize(); ++i) {
        std::cout << v3[i] << " ";
    }
    std::cout << "\n";
    
    // Test equality operators
    Vector<int> v4 = v1;
    std::cout << "v1 == v4: " << (v1 == v4 ? "true" : "false") << "\n";
    std::cout << "v1 != v2: " << (v1 != v2 ? "true" : "false") << "\n";
    
    return 0;
}