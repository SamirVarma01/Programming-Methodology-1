#include "student.h"
#include <iostream>

// Constructor
Student::Student() {
    name = "";
    id = 0;
    gpa = 0.0;
}

Student::Student(const string& studentName, int studentId, float studentGpa) {
    name = studentName;
    id = studentId;
    gpa = studentGpa;
}

// Getters
string Student::getName() const {
    return name;
}

int Student::getId() const {
    return id;
}

float Student::getGpa() const {
    return gpa;
}

// Setters
void Student::setName(const string& studentName) {
    name = studentName;
}

void Student::setId(int studentId) {
    id = studentId;
}

void Student::setGpa(float studentGpa) {
    gpa = studentGpa;
}

// Are they eligible for the scholarship?
bool Student::isEligibleForScholarship() const {
    return gpa >= 3.5;
}