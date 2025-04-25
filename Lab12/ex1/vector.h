#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
public:
    // Default constructor - creates an empty vector
    // Good to have a default state for any container class
    Vector(size_t size = 0) {
        if (size > 0) {
            data = new T[size];
            this->size = size;
            // Initialize elements to default value for type T
            for (size_t i = 0; i < size; i++) {
                data[i] = T(); // Using default constructor of T
            }
        } else {
            data = nullptr;
            this->size = 0;
        }
    }
    
    // Copy constructor - important for avoiding shallow copies
    // Creates a new vector that's a copy of another one
    Vector(const Vector& other) {
        size = other.size;
        if (size > 0) {
            data = new T[size];
            // Copy each element over to maintain independence
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }
    
    // Destructor - clean up allocated memory to prevent leaks
    // Always need to free what we've allocated with new[]
    ~Vector() {
        delete[] data; // Safely handles nullptr too
    }
    
    // Subscript operator - provides read/write access to elements
    // Returns a reference so it can be used on the left side of assignment
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    // Const subscript operator - provides read-only access to elements
    // Important for const Vector objects or using a Vector as a const parameter
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    // Gets the current size of the vector
    // Simple accessor to allow safe reading of private member
    size_t getSize() const {
        return size;
    }
    
    // Assignment operator - handles proper cleanup and deep copying
    // Critical for managing resources and preventing memory leaks
    Vector& operator=(const Vector& other) {
        // Check for self-assignment (a common pitfall)
        if (this == &other) {
            return *this; // Nothing to do
        }
        
        // Free existing resource
        delete[] data;
        
        // Copy from the other vector
        size = other.size;
        if (size > 0) {
            data = new T[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
        
        return *this; // Allow assignment chaining (a = b = c)
    }
    
    // ----- Arithmetic Operators -----
    
    // Addition - creates a new vector that's the sum of two vectors
    // Vectors must be the same size for this to work
    Vector operator+(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be the same size for addition");
        }
        
        Vector result(size);
        for (size_t i = 0; i < size; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }
    
    // Subtraction - creates a new vector that's the difference of two vectors
    // Again, sizes must match to perform element-wise subtraction
    Vector operator-(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be the same size for subtraction");
        }
        
        Vector result(size);
        for (size_t i = 0; i < size; i++) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }
    
    // Scalar multiplication - scales each element by a constant
    // This is a common operation in linear algebra and graphics
    Vector operator*(const T& scalar) const {
        Vector result(size);
        for (size_t i = 0; i < size; i++) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }
    
    // ----- Comparison Operators -----
    
    // Equality - checks if two vectors have the same elements
    // Must check both size and each element value
    bool operator==(const Vector& other) const {
        if (size != other.size) {
            return false; // Different sizes mean definitely not equal
        }
        
        for (size_t i = 0; i < size; i++) {
            if (data[i] != other.data[i]) {
                return false; // Found a difference
            }
        }
        return true; // All elements match
    }
    
    // Inequality - the logical opposite of equality
    // Reusing the equality operator keeps the code DRY
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }
    
    // ----- Compound Assignment Operators -----
    
    // Compound addition - adds another vector to this one in-place
    // Modifies the vector instead of creating a new one
    Vector& operator+=(const Vector& other) {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be the same size for compound addition");
        }
        
        for (size_t i = 0; i < size; i++) {
            data[i] += other.data[i];
        }
        return *this;
    }
    
    // Compound subtraction - subtracts another vector from this one in-place
    // Similar to += but with subtraction
    Vector& operator-=(const Vector& other) {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be the same size for compound subtraction");
        }
        
        for (size_t i = 0; i < size; i++) {
            data[i] -= other.data[i];
        }
        return *this;
    }
    
    // Compound scalar multiplication - scales this vector in-place
    // Efficient for repeated scaling operations
    Vector& operator*=(const T& scalar) {
        for (size_t i = 0; i < size; i++) {
            data[i] *= scalar;
        }
        return *this;
    }
    
private:
    T* data;       // Pointer to dynamically allocated array
    size_t size;   // Current number of elements in the vector
};

template <>
class Vector<bool> {
public:
    // Default constructor - creates an empty boolean vector
    // Same interface as generic vector, but different implementation
    Vector(size_t size = 0) {
        // Calculate number of bytes needed (round up to nearest byte)
        bytesNeeded = (size + 7) / 8;
        if (bytesNeeded > 0) {
            // Allocate packed data array
            data = new unsigned char[bytesNeeded];
            // Initialize all bits to 0
            for (size_t i = 0; i < bytesNeeded; i++) {
                data[i] = 0;
            }
            this->size = size;
        } else {
            data = nullptr;
            this->size = 0;
        }
    }
    
    // Copy constructor - maintains the bit-packing optimization
    // while preserving the same interface for users
    Vector(const Vector& other) {
        size = other.size;
        bytesNeeded = other.bytesNeeded;
        if (bytesNeeded > 0) {
            data = new unsigned char[bytesNeeded];
            // Copy each byte (which contains 8 boolean values)
            for (size_t i = 0; i < bytesNeeded; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }
    
    // Destructor - clean up allocated memory
    ~Vector() {
        delete[] data;
    }
    
    // Helper class for individual bit access via []
    // This is a proxy class that represents a reference to a single bit
    class BitReference {
    public:
        BitReference(unsigned char* byte_ptr, unsigned char bit_mask)
            : byte_ptr(byte_ptr), bit_mask(bit_mask) {}
        
        // Conversion operator - allows reading the bit value
        operator bool() const {
            return (*byte_ptr & bit_mask) != 0;
        }
        
        // Assignment operator - allows writing to the bit
        BitReference& operator=(bool value) {
            if (value) {
                *byte_ptr |= bit_mask;  // Set the bit
            } else {
                *byte_ptr &= ~bit_mask; // Clear the bit
            }
            return *this;
        }
        
    private:
        unsigned char* byte_ptr; // Pointer to the byte containing our bit
        unsigned char bit_mask;  // Mask to isolate the specific bit
    };
    
    // Subscript operator - provides interface consistent with generic Vector
    // but returns a reference to a single bit instead of a bool&
    BitReference operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        // Calculate which byte and bit position we need
        size_t byte_index = index / 8;
        unsigned char bit_pos = index % 8;
        unsigned char bit_mask = 1 << bit_pos;
        
        return BitReference(&data[byte_index], bit_mask);
    }
    
    // Const subscript operator - read-only access to elements
    bool operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        // Calculate which byte and bit position we need
        size_t byte_index = index / 8;
        unsigned char bit_pos = index % 8;
        unsigned char bit_mask = 1 << bit_pos;
        
        return (data[byte_index] & bit_mask) != 0;
    }
    
    // Gets the current size (number of boolean elements)
    size_t getSize() const {
        return size;
    }
    
    // Assignment operator - handles proper cleanup and copying
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        
        delete[] data;
        
        size = other.size;
        bytesNeeded = other.bytesNeeded;
        if (bytesNeeded > 0) {
            data = new unsigned char[bytesNeeded];
            for (size_t i = 0; i < bytesNeeded; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
        
        return *this;
    }
    
    // ----- Arithmetic Operators -----
    
    // Addition (logical OR for booleans)
    Vector operator+(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be the same size for addition");
        }
        
        Vector result(size);
        // For booleans, addition is equivalent to logical OR
        for (size_t i = 0; i < bytesNeeded; i++) {
            // Handle all complete bytes
            if (i < bytesNeeded - 1 || size % 8 == 0) {
                result.data[i] = data[i] | other.data[i];
            } else {
                // For the last byte, we need to be careful not to access bits beyond size
                unsigned char mask = (1 << (size % 8)) - 1;
                result.data[i] = (data[i] | other.data[i]) & mask;
            }
        }
        return result;
    }
    
    // Subtraction (for booleans, this is a bit trickier - implementing as A AND (NOT B))
    Vector operator-(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be the same size for subtraction");
        }
        
        Vector result(size);
        // For booleans, we'll define subtraction as: A AND (NOT B)
        for (size_t i = 0; i < bytesNeeded; i++) {
            // Handle all complete bytes
            if (i < bytesNeeded - 1 || size % 8 == 0) {
                result.data[i] = data[i] & (~other.data[i]);
            } else {
                // For the last byte, we need to be careful not to access bits beyond size
                unsigned char mask = (1 << (size % 8)) - 1;
                result.data[i] = (data[i] & (~other.data[i])) & mask;
            }
        }
        return result;
    }
    
    // Scalar multiplication (for booleans, multiply by scalar is only meaningful if scalar is 0 or 1)
    Vector operator*(const bool& scalar) const {
        Vector result(size);
        if (scalar) {
            // If scalar is true (1), return a copy of this vector
            for (size_t i = 0; i < bytesNeeded; i++) {
                result.data[i] = data[i];
            }
        } else {
            // If scalar is false (0), return a vector of all zeros
            // Already initialized to zero in constructor
        }
        return result;
    }
    
    // ----- Comparison Operators -----
    
    // Equality - checks if two vectors have the same elements
    bool operator==(const Vector& other) const {
        if (size != other.size) {
            return false;
        }
        
        // Check each byte except potentially the last one
        for (size_t i = 0; i < bytesNeeded - 1; i++) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        
        // For the last byte, we need to check only the valid bits
        if (bytesNeeded > 0) {
            // Create a mask for valid bits in the last byte
            unsigned char mask = (size % 8 == 0) ? 0xFF : ((1 << (size % 8)) - 1);
            if ((data[bytesNeeded - 1] & mask) != (other.data[bytesNeeded - 1] & mask)) {
                return false;
            }
        }
        
        return true;
    }
    
    // Inequality - the logical opposite of equality
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }
    
    // ----- Compound Assignment Operators -----
    
    // Compound addition (OR assignment)
    Vector& operator+=(const Vector& other) {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be the same size for compound addition");
        }
        
        for (size_t i = 0; i < bytesNeeded; i++) {
            data[i] |= other.data[i];
        }
        
        // If size is not a multiple of 8, clear any unused bits in the last byte
        if (size % 8 != 0) {
            unsigned char mask = (1 << (size % 8)) - 1;
            data[bytesNeeded - 1] &= mask;
        }
        
        return *this;
    }
    
    // Compound subtraction (A AND= (NOT B))
    Vector& operator-=(const Vector& other) {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must be the same size for compound subtraction");
        }
        
        for (size_t i = 0; i < bytesNeeded; i++) {
            data[i] &= ~other.data[i];
        }
        
        // If size is not a multiple of 8, clear any unused bits in the last byte
        if (size % 8 != 0) {
            unsigned char mask = (1 << (size % 8)) - 1;
            data[bytesNeeded - 1] &= mask;
        }
        
        return *this;
    }
    
    // Compound scalar multiplication
    Vector& operator*=(const bool& scalar) {
        if (!scalar) {
            // If scalar is false (0), set all bits to 0
            for (size_t i = 0; i < bytesNeeded; i++) {
                data[i] = 0;
            }
        }
        // If scalar is true (1), do nothing as multiplying by 1 doesn't change values
        
        return *this;
    }
    
private:
    unsigned char* data;  // Pointer to bit-packed array (each byte holds 8 booleans)
    size_t size;          // Number of boolean elements
    size_t bytesNeeded;   // Number of bytes allocated
};

#endif 