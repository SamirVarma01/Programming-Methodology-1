#include "calculator.h"
#include <iostream>
#include <string>

// Implement Calculator methods with overloading
int Calculator::add(int a, int b) {
    return a + b;
}

double Calculator::add(double a, double b) {
    return a + b;
}

std::string Calculator::add(const std::string& a, const std::string& b) {
    return a + b;
}

int Calculator::add(int a, int b, int c) {
    return a + b + c;
}

int Calculator::subtract(int a, int b) {
    return a - b;
}

double Calculator::subtract(double a, double b) {
    return a - b;
}

int Calculator::multiply(int a, int b) {
    return a * b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

void Calculator::display() const {
    std::cout << "Calculator with method overloading for arithmetic operations" << std::endl;
}

// Implement DeviceInterface methods
DeviceInterface::DeviceInterface(const std::string& name) : name(name) {
    std::cout << "DeviceInterface constructor called for " << name << std::endl;
}

DeviceInterface::~DeviceInterface() {
    std::cout << "DeviceInterface destructor called for " << name << std::endl;
}

std::string DeviceInterface::getDeviceInfo() const {
    return name;
}

// Implement SmartPhone methods
SmartPhone::SmartPhone(const std::string& name, const std::string& os, const std::string& processor)
    : DeviceInterface(name), os(os), processor(processor) {
    std::cout << "SmartPhone constructor called for " << name << std::endl;
}

SmartPhone::~SmartPhone() {
    std::cout << "SmartPhone destructor called for " << name << std::endl;
}

void SmartPhone::powerOn() {
    std::cout << name << " powered on" << std::endl;
}

void SmartPhone::powerOff() {
    std::cout << name << " powered off" << std::endl;
}

void SmartPhone::performOperation(const std::string& operation) {
    std::cout << name << " performing: " << operation << std::endl;
}

void SmartPhone::makeCall(const std::string& number) {
    std::cout << name << " calling " << number << std::endl;
}

// Implement Laptop methods
Laptop::Laptop(const std::string& name, const std::string& os, const std::string& processor)
    : DeviceInterface(name), os(os), processor(processor) {
    std::cout << "Laptop constructor called for " << name << std::endl;
}

Laptop::~Laptop() {
    std::cout << "Laptop destructor called for " << name << std::endl;
}

void Laptop::powerOn() {
    std::cout << name << " powered on" << std::endl;
}

void Laptop::powerOff() {
    std::cout << name << " powered off" << std::endl;
}

void Laptop::performOperation(const std::string& operation) {
    std::cout << name << " performing: " << operation << std::endl;
}

void Laptop::runProgram(const std::string& program) {
    std::cout << name << " running program: " << program << std::endl;
}