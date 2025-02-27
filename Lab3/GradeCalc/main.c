#include <stdio.h>
#include "grade_functions.h" // Include header

// Takes grade inputs and print number/letter grade averages
int main() {
    float grade1, grade2, grade3;
    int is_valid = 0;
    float avg;
    char letter;

    // Ensure grade inputs are between 0-100
    while (is_valid == 0) {
        printf("Enter 3 grades: ");
        scanf("%f %f %f", &grade1, &grade2, &grade3);
        if (grade1 < 0 || grade1 > 100 || grade2 < 0 || grade2 > 100 || grade3 < 0 || grade3 > 100) {
            printf("Please enter grades between 0-100.\n");
        } else {
            is_valid = 1;
        }
    }

    // Find average and letter grade
    avg = calculateAverage(grade1, grade2, grade3);
    letter = determineLetterGrade(avg);

    // Print report
    printGradeReport(avg, letter);

    return 0;
}