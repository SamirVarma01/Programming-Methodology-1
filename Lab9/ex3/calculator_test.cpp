#include <iostream>
#include <iomanip>
#include "calculator.h"

// Test for Checkpoint 1: Namespace Implementation
void test_calculator_namespace() {
    std::cout << "\n=== TEST 1: CALCULATOR NAMESPACE IMPLEMENTATION ===\n" << std::endl;
    
    double a = 10.5, b = 5.25;
    
    std::cout << "Testing with values: a = " << a << ", b = " << b << std::endl;
    
    // Test addition
    double result = calculator::add(a, b);
    calculator::display_result("+", a, b, result);
    
    // Test subtraction
    result = calculator::subtract(a, b);
    calculator::display_result("-", a, b, result);
    
    // Test multiplication
    result = calculator::multiply(a, b);
    calculator::display_result("*", a, b, result);
    
    // Test division
    result = calculator::divide(a, b);
    calculator::display_result("/", a, b, result);
    
    // Test division by zero
    std::cout << "\nTesting division by zero:" << std::endl;
    result = calculator::divide(a, 0);
}

// Test for Checkpoint 2: Using std Namespace and iostream
int test_iostream() {
    std::cout << "\n=== TEST 2: USING STD NAMESPACE AND IOSTREAM ===\n" << std::endl;
    
    // Using fully qualified names
    std::cout << "Enter two numbers: ";
    double num1, num2;
    std::cin >> num1 >> num2;
    
    // Using manipulators for formatting
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Sum: " << num1 + num2 << std::endl;
    
    // Stream formatting
    std::cout << std::setw(10) << "Number 1" << std::setw(10) << "Number 2" << std::endl;
    std::cout << std::setw(10) << num1 << std::setw(10) << num2 << std::endl;
    
    return 0;
}

// Test for Checkpoint 3: I/O Manipulators
void demonstrate_manipulators() {
    std::cout << "\n=== TEST 3: I/O MANIPULATORS ===\n" << std::endl;
    
    double value = 3.14159265359;
    
    // Precision
    std::cout << "Default: " << value << std::endl;
    std::cout << "Fixed with 2 decimal places: " << std::fixed << std::setprecision(2) << value << std::endl;
    std::cout << "Scientific: " << std::scientific << value << std::endl;
    
    // Reset format
    std::cout.unsetf(std::ios::fixed | std::ios::scientific);
    std::cout << std::setprecision(6);
    
    // Width and fill
    std::cout << "Width of 10, right-aligned: |" << std::setw(10) << value << "|" << std::endl;
    std::cout << "Width of 10, left-aligned: |" << std::left << std::setw(10) << value << "|" << std::endl;
    std::cout << "Width of 10, filled with *: |" << std::right << std::setfill('*') << std::setw(10) << value << "|" << std::endl;
    
    // Boolean values
    bool flag = true;
    std::cout << "Boolean (default): " << flag << std::endl;
    std::cout << "Boolean (as text): " << std::boolalpha << flag << std::endl;
    
    // Integer bases
    int num = 255;
    std::cout << "Decimal: " << num << std::endl;
    std::cout << "Hexadecimal: " << std::hex << num << std::endl;
    std::cout << "Octal: " << std::oct << num << std::endl;
}

int main() {
    std::cout << "C++ I/O and Namespaces Exercise" << std::endl;
    std::cout << "================================" << std::endl;
    
    test_calculator_namespace();
    demonstrate_manipulators();
    test_iostream();
    
    return 0;
}