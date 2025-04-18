#include <iostream>
#include "calculator.h"
#include <vector>

int main() {
    // Test function overloading
    Calculator calc;
    
    std::cout << "Testing function overloading:" << std::endl;
    std::cout << "Integer addition: " << calc.add(10, 20) << std::endl;
    std::cout << "Double addition: " << calc.add(3.14, 2.71) << std::endl;
    std::cout << "String concatenation: " << calc.add("C++", " Polymorphism") << std::endl;
    std::cout << "Triple integer addition: " << calc.add(5, 10, 15) << std::endl;
    
    // Test runtime polymorphism
    std::cout << "\nTesting runtime polymorphism:" << std::endl;
    std::vector<DeviceInterface*> devices;
    
    devices.push_back(new SmartPhone("Pixel 6", "Android", "Tensor"));
    devices.push_back(new Laptop("ThinkPad", "Linux", "AMD Ryzen"));
    
    for (auto device : devices) {
        std::cout << "Device info: " << device->getDeviceInfo() << std::endl;
        device->powerOn();
        device->performOperation("Run system check");
        device->powerOff();
        std::cout << std::endl;
    }
    
    // Clean up
    for (auto device : devices) {
        delete device;
    }
    
    return 0;
}