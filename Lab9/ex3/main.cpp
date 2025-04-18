#include "calculator.h"
#include <iostream>
#include <iomanip>
#include <limits>

int main() {
    std::cout << "Welcome to the Calculator Program!" << std::endl;
    std::cout << "=================================" << std::endl;
    
    double a, b;
    
    // Get user input with error handling
    std::cout << "Enter first number: ";
    while (!(std::cin >> a)) {
        std::cin.clear(); // Clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid input. Please enter a number: ";
    }
    
    std::cout << "Enter second number: ";
    while (!(std::cin >> b)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number: ";
    }
    
    // Using fully qualified namespace
    double sum = calculator::add(a, b);
    calculator::display_result("+", a, b, sum);
    
    double difference = calculator::subtract(a, b);
    calculator::display_result("-", a, b, difference);
    
    // Using using directive for the next operations
    using namespace calculator;
    
    double product = multiply(a, b);
    display_result("*", a, b, product);
    
    double quotient = divide(a, b);
    display_result("/", a, b, quotient);
    
    // Demonstrate iostream manipulators
    std::cout << "\nFormatting Examples:" << std::endl;
    std::cout << "====================" << std::endl;
    
    std::cout << "Scientific notation: " << std::scientific << sum << std::endl;
    std::cout << "Fixed notation (3 decimals): " << std::fixed << std::setprecision(3) << sum << std::endl;
    
    std::cout << "Right-aligned in field of width 15: |" << std::setw(15) << sum << "|" << std::endl;
    std::cout << "Left-aligned in field of width 15: |" << std::left << std::setw(15) << sum << "|" << std::endl;
    
    return 0;
}