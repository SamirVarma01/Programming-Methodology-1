#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <iostream>

// Calculator class with method overloading
class Calculator {
public:
    // Method overloading for add() with different parameter types
    int add(int a, int b);
    double add(double a, double b);
    std::string add(const std::string& a, const std::string& b);
    int add(int a, int b, int c);
    
    // Method overloading for subtract() with different parameter types
    int subtract(int a, int b);
    double subtract(double a, double b);
    
    // Method overloading for multiply() with different parameter types
    int multiply(int a, int b);
    double multiply(double a, double b);
    
    // display() method to show calculator information
    void display() const;
};

// Base DeviceInterface class for runtime polymorphism
class DeviceInterface {
public:
    // Constructor and destructor
    DeviceInterface(const std::string& name);
    virtual ~DeviceInterface();
    
    // Pure virtual methods for power on/off functionality
    virtual void powerOn() = 0;
    virtual void powerOff() = 0;
    
    // Pure virtual method for performing device operations
    virtual void performOperation(const std::string& operation) = 0;
    
    // Non-virtual method for getting device information
    std::string getDeviceInfo() const;
    
protected:
    std::string name;
};

// SmartPhone derived class
class SmartPhone : public DeviceInterface {
private:
    // Relevant member variables
    std::string os;
    std::string processor;
    
public:
    // Constructor and destructor
    SmartPhone(const std::string& name, const std::string& os, const std::string& processor);
    ~SmartPhone() override;
    
    // Override power on/off methods
    void powerOn() override;
    void powerOff() override;
    
    // Override performOperation method
    void performOperation(const std::string& operation) override;
    
    // Smartphone-specific methods
    void makeCall(const std::string& number);
};

// Laptop derived class
class Laptop : public DeviceInterface {
private:
    // Relevant member variables
    std::string os;
    std::string processor;
    
public:
    // Constructor and destructor
    Laptop(const std::string& name, const std::string& os, const std::string& processor);
    ~Laptop() override;
    
    // Override power on/off methods
    void powerOn() override;
    void powerOff() override;
    
    // Override performOperation method
    void performOperation(const std::string& operation) override;
    
    // Laptop-specific methods
    void runProgram(const std::string& program);
};

#endif 