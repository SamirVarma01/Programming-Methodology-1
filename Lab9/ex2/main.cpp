#include <iostream>
#include "counter.h"

// Test for Checkpoint 1: Object Creation and Destruction
void test_object_creation() {
    std::cout << "=== TEST 1: OBJECT CREATION AND DESTRUCTION ===" << std::endl;
    std::cout << "Total counters: " << Counter::getTotalCounters() << std::endl;
    
    {
        Counter c1;
        std::cout << "After creating c1, total counters: " << Counter::getTotalCounters() << std::endl;
        {
            Counter c2(10);
            std::cout << "After creating c2, total counters: " << Counter::getTotalCounters() << std::endl;
        }
        std::cout << "After c2 goes out of scope, total counters: " << Counter::getTotalCounters() << std::endl;
    }
    std::cout << "After all counters go out of scope, total counters: " << Counter::getTotalCounters() << std::endl;
}

// Test for Checkpoint 2: Member Methods and Variables
void test_member_methods() {
    std::cout << "\n=== TEST 2: MEMBER METHODS AND VARIABLES ===" << std::endl;
    Counter c1;
    std::cout << "Initial value: " << c1.getValue() << std::endl;
    
    c1.increment();
    c1.increment();
    std::cout << "After incrementing twice: " << c1.getValue() << std::endl;
    
    c1.decrement();
    std::cout << "After decrementing once: " << c1.getValue() << std::endl;

    Counter c2(5);
    std::cout << "c2 initial value: " << c2.getValue() << std::endl;
}

// Test for Checkpoint 3: Dynamic Object Creation
void test_dynamic_objects() {
    std::cout << "\n=== TEST 3: DYNAMIC OBJECT CREATION ===" << std::endl;
    std::cout << "Total counters before dynamic creation: " << Counter::getTotalCounters() << std::endl;
    
    Counter* dynamic_counter = new Counter(3);
    std::cout << "After dynamic creation, total counters: " << Counter::getTotalCounters() << std::endl;
    std::cout << "Dynamic counter value: " << dynamic_counter->getValue() << std::endl;
    
    dynamic_counter->increment();
    dynamic_counter->increment();
    std::cout << "After incrementing dynamic counter: " << dynamic_counter->getValue() << std::endl;
    
    delete dynamic_counter;
    std::cout << "After deleting dynamic counter, total counters: " << Counter::getTotalCounters() << std::endl;
}

// Main function that incorporates all tests
int main() {
    std::cout << "Starting program. Total counters: " << Counter::getTotalCounters() << std::endl;
    
    // Test automatic objects
    {
        Counter c1;
        std::cout << "Created c1. Total counters: " << Counter::getTotalCounters() << std::endl;
        std::cout << "c1 value: " << c1.getValue() << std::endl;
        
        c1.increment();
        c1.increment();
        std::cout << "c1 after incrementing twice: " << c1.getValue() << std::endl;
        
        Counter c2(10);
        std::cout << "Created c2. Total counters: " << Counter::getTotalCounters() << std::endl;
        std::cout << "c2 value: " << c2.getValue() << std::endl;
    }
    
    std::cout << "After block, total counters: " << Counter::getTotalCounters() << std::endl;
    
    // Test dynamic objects
    Counter* ptr = new Counter(5);
    std::cout << "Created dynamic counter. Total counters: " << Counter::getTotalCounters() << std::endl;
    std::cout << "Dynamic counter value: " << ptr->getValue() << std::endl;
    
    ptr->decrement();
    std::cout << "Dynamic counter after decrementing: " << ptr->getValue() << std::endl;
    
    delete ptr;
    std::cout << "Deleted dynamic counter. Total counters: " << Counter::getTotalCounters() << std::endl;
    
    test_object_creation();
    test_member_methods();
    test_dynamic_objects();
    
    return 0;
}