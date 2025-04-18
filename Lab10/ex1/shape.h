#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <iostream>

// Base class declaration
class Shape {
    // Protected member variables for shape name and color
protected:
    std::string name;
    std::string color;
    
public:
    // Constructor declarations
    Shape(std::string name = "Unknown", std::string color = "None");
    virtual ~Shape();
    
    // Method declarations for getting and setting shape information
    std::string getName() const;
    std::string getColor() const;
    void setName(std::string name);
    void setColor(std::string color);
    
    // Virtual method to calculate area
    virtual double calculateArea() const;
    
    // Virtual method to display shape information
    virtual void displayInfo() const;
};

// Derived class declaration - Circle
class Circle : public Shape {
    // Private member variable specific to Circle (radius)
private:
    double radius;
    
public:
    // Constructor declarations for Circle
    Circle(std::string name = "Unknown", std::string color = "None", double radius = 0);
    
    // Method declarations specific to Circle
    double getRadius() const;
    void setRadius(double radius);
    
    // Override the area calculation method
    double calculateArea() const override;
    
    // Override the display method
    void displayInfo() const override;
};

// Derived class declaration - Rectangle
class Rectangle : public Shape {
    // Private member variables specific to Rectangle (width, height)
private:
    double width;
    double height;
    
public:
    // Constructor declarations for Rectangle
    Rectangle(std::string name = "Unknown", std::string color = "None", double width = 0, double height = 0);
    
    // Method declarations specific to Rectangle
    double getWidth() const;
    double getHeight() const;
    void setWidth(double width);
    void setHeight(double height);
    
    // Override the area calculation method
    double calculateArea() const override;
    
    // Override the display method
    void displayInfo() const override;
};

#endif // SHAPE_H