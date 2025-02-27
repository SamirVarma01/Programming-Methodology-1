#include <stdio.h>

// Function for converting C to F
float celsiusToFahrenheit(float celsius) {
    return (celsius * 9/5) + 32;
}

// Function for converting F to C
float fahrenheitToCelsius(float fahrenheit) {
    return (fahrenheit - 32) * 5/9;
}

// Function for printing temperature values
void printTemperature(float temp, char unit) {
    printf("%.1f deg %c", temp, unit);
}

// Main function -- takes user inputs and prints conversion 
int main() {

    // Define local variables
    float temp;
    float converted;
    char unit;
    int is_valid = 0;

    // Take user inputs
    printf("Enter a temperature: ");
    scanf("%f", &temp);

    // Check for valid unit character
    while (is_valid == 0) {
        printf("Enter a unit: ");
        scanf(" %c", &unit);
        if (unit == 'F' || unit == 'C') {
            is_valid = 1;
        } else {
            printf("Please use unit C or F.\n");
        }
    }
    
    // Print correct conversion for either C or F
    if (unit == 'C') {
        converted = celsiusToFahrenheit(temp);
        printTemperature(temp, unit);
        printf(" = ");
        printTemperature(converted, 'F');
    } else if (unit == 'F') {
        converted = fahrenheitToCelsius(temp);
        printTemperature(temp, unit);
        printf(" = ");
        printTemperature(converted, 'C');
    }

    return 0;
}