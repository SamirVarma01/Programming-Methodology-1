#include <iostream>
#include "matrix.h"

int main() {
    // Create 2x2 matrices
    Matrix<double, 2, 2> m1{{{1.0, 2.0}, {3.0, 4.0}}};
    Matrix<double, 2, 2> m2{{{2.0, 0.0}, {1.0, 3.0}}};

    // Test operations
    std::cout << "m1:\n" << m1 << std::endl;
    std::cout << "m2:\n" << m2 << std::endl;
    std::cout << "m1 + m2:\n" << (m1 + m2) << std::endl;
    std::cout << "m1 * m2:\n" << (m1 * m2) << std::endl;

    // For 2x2 specialization
    std::cout << "det(m1) = " << m1.determinant() << std::endl;
    auto m1_inv = m1.inverse();
    std::cout << "inv(m1):\n" << m1_inv << std::endl;

    // Test system solving
    std::array<double, 2> b = {5.0, 11.0};
    auto x = m1.solve(b);
    std::cout << "Solution: x = " << x[0]
              << ", y = " << x[1] << std::endl;
              
    // Test subscript operator
    std::cout << "m1[0][0] = " << m1[0][0] << std::endl;
    
    // Test scalar multiplication
    std::cout << "2 * m1:\n" << (2.0 * m1) << std::endl;
    
    // Test with a different size matrix
    Matrix<int, 3, 3> m3{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
    std::cout << "3x3 matrix m3:\n" << m3 << std::endl;
    
    // Test multiplication with different sized matrices
    Matrix<int, 3, 2> m4{{{1, 2}, {3, 4}, {5, 6}}};
    Matrix<int, 2, 4> m5{{{1, 2, 3, 4}, {5, 6, 7, 8}}};
    std::cout << "3x2 matrix m4:\n" << m4 << std::endl;
    std::cout << "2x4 matrix m5:\n" << m5 << std::endl;
    std::cout << "m4 * m5 (3x4 result):\n" << (m4 * m5) << std::endl;

    return 0;
}