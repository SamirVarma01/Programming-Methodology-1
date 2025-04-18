// shape.cpp
#include "shape.h"
#include <iostream>
#include <cmath>

// TODO: Implement Shape constructors
Shape::Shape(std::string name, std::string color) 
    : name(name), color(color) {
}

Shape::~Shape() {
    // Virtual destructor for proper cleanup in inheritance hierarchy
}

// TODO: Implement Shape methods
std::string Shape::getName() const {
    return name;
}

std::string Shape::getColor() const {
    return color;
}

void Shape::setName(std::string name) {
    this->name = name;
}

void Shape::setColor(std::string color) {
    this->color = color;
}

double Shape::calculateArea() const {
    return 0;
}

void Shape::displayInfo() const {
    std::cout << "Shape Information:" << std::endl;
    std::cout << "  Name: " << name << std::endl;
    std::cout << "  Color: " << color << std::endl;
    std::cout << "  Area: " << calculateArea() << std::endl;
}

// TODO: Implement Circle constructors
Circle::Circle(std::string name, std::string color, double radius)
    : Shape(name, color), radius(radius) {
}

// TODO: Implement Circle methods
double Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(double radius) {
    this->radius = radius;
}

double Circle::calculateArea() const {
    return M_PI * radius * radius;
}

void Circle::displayInfo() const {
    std::cout << "Circle Information:" << std::endl;
    std::cout << "  Name: " << getName() << std::endl;
    std::cout << "  Color: " << getColor() << std::endl;
    std::cout << "  Radius: " << radius << std::endl;
    std::cout << "  Area: " << calculateArea() << std::endl;
}

// TODO: Implement Rectangle constructors
Rectangle::Rectangle(std::string name, std::string color, double width, double height)
    : Shape(name, color), width(width), height(height) {
}

// TODO: Implement Rectangle methods
double Rectangle::getWidth() const {
    return width;
}

double Rectangle::getHeight() const {
    return height;
}

void Rectangle::setWidth(double width) {
    this->width = width;
}

void Rectangle::setHeight(double height) {
    this->height = height;
}

double Rectangle::calculateArea() const {
    return width * height;
}

void Rectangle::displayInfo() const {
    std::cout << "Rectangle Information:" << std::endl;
    std::cout << "  Name: " << getName() << std::endl;
    std::cout << "  Color: " << getColor() << std::endl;
    std::cout << "  Width: " << width << std::endl;
    std::cout << "  Height: " << height << std::endl;
    std::cout << "  Area: " << calculateArea() << std::endl;
}