#include "counter.h"
#include <iostream>

int Counter::total_counters = 0;

// Default constructor
Counter::Counter() : value(0) {
    total_counters++;
}

// Parameterized constructor
Counter::Counter(int initial_value) : value(initial_value) {
    total_counters++;
}

// Destructor
Counter::~Counter() {
    total_counters--;
}

// Increment method
void Counter::increment() {
    value++;
}

// Decrement method
void Counter::decrement() {
    value--;
}

// Getter method for value
int Counter::getValue() const {
    return value;
}

// Static method to get total counter instances
int Counter::getTotalCounters() {
    return total_counters;
}