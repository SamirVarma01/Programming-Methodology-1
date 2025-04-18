#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

namespace calculator {
    double add(double a, double b);         
    double subtract(double a, double b);    
    double multiply(double a, double b);    
    double divide(double a, double b);                                                 
    
    void display_result(const std::string& operation, double a, double b, 
                      double result);
}

#endif 