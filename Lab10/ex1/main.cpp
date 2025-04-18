#include <iostream>
#include "shape.h"
#include <vector>

int main() {
    // Create base and derived objects
    Shape baseShape("Base Shape", "White");
    Circle circle("Red Circle", "Red", 4.0);
    Rectangle rectangle("Blue Rectangle", "Blue", 5.0, 3.0);
    
    // Test base class methods on derived objects
    std::cout << "Circle name: " << circle.getName() << std::endl;
    std::cout << "Rectangle color: " << rectangle.getColor() << std::endl;
    
    // Test overridden methods
    std::cout << "Base shape area: " << baseShape.calculateArea() << std::endl;
    std::cout << "Circle area: " << circle.calculateArea() << std::endl;
    std::cout << "Rectangle area: " << rectangle.calculateArea() << std::endl;
    
    // Test polymorphism with a vector of base class pointers
    std::vector<Shape*> shapes;
    shapes.push_back(&baseShape);
    shapes.push_back(&circle);
    shapes.push_back(&rectangle);
    
    std::cout << "\nPolymorphic display of all shapes:" << std::endl;
    for (Shape* s : shapes) {
        s->displayInfo();
        std::cout << "Area: " << s->calculateArea() << "\n\n";
    }
    
    return 0;
}