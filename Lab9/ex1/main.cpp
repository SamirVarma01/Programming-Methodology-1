#include <iostream>
#include "student.h"

// Test for Checkpoint 1: Class Definition with Access Modifiers
int test_class_definition() {
    Student s1("John Doe", 12345, 3.7);
    std::cout << "Student ID: " << s1.getId() << std::endl;
    std::cout << "Student Name: " << s1.getName() << std::endl;
    std::cout << "Student GPA: " << s1.getGpa() << std::endl;
    
    return 0;
}

// Test for Checkpoint 2: Constructors and Initialization
int test_constructors() {
    Student s1;
    std::cout << "Default student: " << s1.getName() << ", ID: " << s1.getId() 
              << ", GPA: " << s1.getGpa() << std::endl;
    
    Student s2("Jane Smith", 67890, 3.9);
    std::cout << "Student 2: " << s2.getName() << ", ID: " << s2.getId() 
              << ", GPA: " << s2.getGpa() << std::endl;
    
    return 0;
}

// Test for Checkpoint 3: Method Implementation
int test_methods() {
    Student s1;
    s1.setName("Alice Johnson");
    s1.setId(54321);
    s1.setGpa(3.5);
    
    std::cout << "Student: " << s1.getName() << ", ID: " << s1.getId() 
              << ", GPA: " << s1.getGpa() << std::endl;
    
    if (s1.isEligibleForScholarship()) {
        std::cout << s1.getName() << " is eligible for a scholarship." << std::endl;
    } else {
        std::cout << s1.getName() << " is not eligible for a scholarship." << std::endl;
    }
    
    // Test with lower GPA
    s1.setGpa(3.2);
    std::cout << "Updated student: " << s1.getName() << ", ID: " << s1.getId() 
              << ", GPA: " << s1.getGpa() << std::endl;
    if (s1.isEligibleForScholarship()) {
        std::cout << s1.getName() << " is eligible for a scholarship." << std::endl;
    } else {
        std::cout << s1.getName() << " is not eligible for a scholarship." << std::endl;
    }
    
    return 0;
}

int main() {
    std::cout << "=== Checkpoint 1: Class Definition with Access Modifiers ===" << std::endl;
    test_class_definition();
    
    std::cout << "\n=== Checkpoint 2: Constructors and Initialization ===" << std::endl;
    test_constructors();
    
    std::cout << "\n=== Checkpoint 3: Method Implementation ===" << std::endl;
    test_methods();
    
    return 0;
}