#include <stdio.h>

// Function for addition -- int because adding two integers produces an integer
int add(int a, int b) {
    return a + b;
} 

// Function for subtraction -- int because subtracting two integers produces an integer
int subtract(int a, int b) {
    return a - b;
}

// Function for multiplication -- int because multiplying two integers produces an integer
int multiply(int a, int b) {
    return a * b;
}

// Function for division -- float because dividing two integers can result in a decimal value
float divide(int a, int b) {
    return a / b;
}

// Main function, takes user inputted numbers and performs all basic mathematical operations
int main() {
    int a, b; // Define local variables

    // Take inputs
    printf("Enter first number: ");
    scanf("%d", &a);
    printf("Enter second number: ");
    scanf("%d", &b);

    // Perform operations
    int addition = add(a, b);
    int subtraction = subtract(a, b);
    int multiplication = multiply(a, b);
    float division = divide(a, b);
    
    // Print results
    printf("\nResults: \n");
    printf("%d + %d = %d\n", a, b, addition);
    printf("%d - %d = %d\n", a, b, subtraction);
    printf("%d * %d = %d\n", a, b, multiplication);
    
    // Handle division by 0 after all other functions performed
    if (b == 0) {
        printf("Cannot divide by 0.");
    } else {
        printf("%d + %d = %.1f\n", a, b, division);
    }
    return 0;
}