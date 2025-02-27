#include <stdio.h>
#include "grade_functions.h"

// Function for calculating average grade
float calculateAverage(float g1, float g2, float g3) {
    return (g1 + g2 + g3) / 3;
}

// Function for finding letter grade
char determineLetterGrade(float grade) {
    if (grade >= 0 && grade < 60) {
        return 'F';
    } else if (grade >= 60 && grade < 70) {
        return 'D';
    } else if (grade >= 70 && grade < 80) {
        return 'C';
    } else if (grade >= 80 && grade < 90) {
        return 'B';
    } else if (grade >= 90 && grade <= 100) {
        return 'A';
    } else {
        return '?'; // Default case if avg out of range 0-100
    }
}

// Print grade report based on average grade and letter grade
int printGradeReport(float avg, char letter) {
    printf("Your number grade is %.2f\n", avg);
    printf("Your letter grade is %c\n", letter);
    return 0;
}
