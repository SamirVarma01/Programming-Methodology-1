#include "calculator.h"
#include <iostream>
#include <iomanip>

namespace calculator {
    double add(double a, double b) {
        return a + b;
    }
    
    double subtract(double a, double b) {
        return a - b;
    }
    
    double multiply(double a, double b) {
        return a * b;
    }
    
    double divide(double a, double b) {
        if (b == 0) {
            std::cerr << "Error: Division by zero!" << std::endl;
            return 0;
        }
        return a / b;
    }
    
    void display_result(const std::string& operation, double a, double b, double result) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << a << " " << operation << " " << b << " = " << result << std::endl;
    }
}