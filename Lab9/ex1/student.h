#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;


class Student 
{
    private:
        string name;
        int id;
        float gpa;
    
    public:
        // Constructors
        Student();
        Student(const string& studentName, int studentId, float studentGpa);

        // Getters
        std :: string getName() const;
        int getId() const;
        float getGpa() const;

        // Setters
        void setName(const string& studentName);
        void setId(int studentId);
        void setGpa(float studentGpa);

        // Scholarship
        bool isEligibleForScholarship() const;
};

#endif