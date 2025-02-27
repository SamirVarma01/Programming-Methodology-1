#include <stdio.h>

// Global temperature threshold
int MAX_TEMP = 100; // Maximum allowed temperature, global
int MIN_TEMP = 0; // Minimum allowed temperature, global

int invalid_max = 150; // Global max
int invalid_min = -50; // Global max

int main(void) {
    // Local temperature variables
    int current_temp; // current_temp, local
    int is_valid = 0; // Flag for temperature validity, local

    // Check if temperature is in range
    while (is_valid == 0) {
        printf("Enter current temperature: ");
        scanf("%d", &current_temp);
        if (current_temp >= MIN_TEMP && current_temp <= MAX_TEMP) {
            is_valid = 1; // Local to if block
            printf("Temperature %d is in valid range\n", current_temp);
        } else if (current_temp < MIN_TEMP && current_temp >= invalid_min) {
            printf("Warning: Temperature %d is lower than MIN_TEMP!\n", current_temp);
        } else if (current_temp > MAX_TEMP && current_temp <= invalid_max) {
            printf("Warning: Temperature %d is higher than MAX_TEMP!\n", current_temp);
        } else if (current_temp < invalid_min || current_temp > invalid_max) {
            printf("Warning: Temperature %d is invalid!\n", current_temp);
        }
    }
    // Block demonstrating variable shadowing
    {
        int MAX_TEMP = 80; // Shadows global MAX_TEMP
        printf("Local MAX_TEMP: %d\n", MAX_TEMP);
    }
    printf("Global MAX_TEMP %d\n", MAX_TEMP);
    
    return 0;
}