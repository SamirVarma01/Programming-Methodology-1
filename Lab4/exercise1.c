#include <stdio.h>

/* Function declaration */
double computeAverage(int values[], int size);

int main() {
    int numbers[] = {15, 24, 33, 42, 51};
    int size = 5;

    // Using the function with type casting
    double result = computeAverage(numbers, size);
    printf("Average with type casting: %.2f\n", result);

    // Manual calculation without type casting
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }
    int intResult = sum / size; // Integer division
    printf("Average without type casting: %d\n", intResult);

    return 0;
}

/* Function definition */
double computeAverage(int values[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += values[i];
    }
    return (double)sum / size;
}


/*
Samir Varma 

Exercise 1

a) This program outputs both 33.00 (double) and 33 (int). This is because result 
is type casted as a double, performing floating point division, while intResult has no 
type casting and is thus produced as an integer.

b) The type casting in result ensures the use of floating point division as 
opposed to integer division.

c) Simply removing the (double) cast from the computeAverage function causes the
returned result of computeAverage to still be 33.00, but it is now converted to a
float because it is formatted as %.2f in the print statement. This can cause a loss
in precision as doubles are more precise than floats, so in a case where our average
was not an integer, we may get less accurate results.

d) Type casting helps ensure precision is preserved in edge cases where our average
is not a perfect integer.asm

*/