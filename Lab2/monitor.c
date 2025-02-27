# include <stdio.h>

// Temperature thresholds ( matching lecture examples )
const int MAX_TEMP = 100; // Maximum allowed temperature
const int MIN_TEMP = 0; // Minimum allowed temperature

float min(float a, float b) {
    return (a < b) ? a : b;
}

float max(float a, float b) {
    return (a > b) ? a : b;
}

int main(void) {
    int choice;
    float temp1 , temp2 , temp3 , temp4 , temp5; // Individual temperature variables
    float minTemp;
    float maxTemp;
    float avgTemp;
    int valid_temps = 0;


    do {// Display menu
        int is_choice_valid = 0;
        printf ("\nTemperature Monitor Menu :\n");
        printf ("1. Enter temperatures \n");
        printf ("2. Check temperature status \n");
        printf ("3. Display statistics \n");
        printf ("4. Exit\n");

        while (is_choice_valid == 0) {
            printf("Enter choice: ");
            if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 4) {
                is_choice_valid = 1;
            } else {
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
                while (getchar() != '\n'); // Clear input buffer
            }
        }
            

        switch (choice) {
            case 1: {
                int is_temp_valid = 0;
                while (is_temp_valid == 0) {
                    printf ("Enter temperature 1: ");
                    scanf("%f", &temp1);
                    printf ("Enter temperature 2: ");
                    scanf("%f", &temp2);
                    printf ("Enter temperature 3: ");
                    scanf("%f", &temp3);
                    printf ("Enter temperature 4: ");
                    scanf("%f", &temp4);
                    printf ("Enter temperature 5: ");
                    scanf("%f", &temp5);
                    if (temp1 >= -50 && temp1 <= 150 &&
                        temp2 >= -50 && temp2 <= 150 &&
                        temp3 >= -50 && temp3 <= 150 &&
                        temp4 >= -50 && temp4 <= 150 &&
                        temp5 >= -50 && temp5 <= 150) {
                        is_temp_valid = 1; // Valid temperatures, exit loop
                    } else {
                        printf("Invalid temperature entered! Please enter values between -50 and 150.");
                        while (getchar() != '\n'); // Clear input buffer
                    }
                }
                break;
            }

            case 2:
                printf (" Temperature 1: %.1f\n", temp1);
                if (temp1 > MAX_TEMP) {
                    printf("Warning: temp1 exceeds max temperature!");
                } else if (temp1 < MIN_TEMP) {
                    printf("Warning: temp1 is below min temperature!");
                } else {
                    printf("temp1 in range.");
                    valid_temps++;
                }
                printf (" Temperature 2: %.1f\n", temp2);
                if (temp2 > MAX_TEMP) {
                    printf("Warning: temp2 exceeds max temperature!");
                } else if (temp2 < MIN_TEMP) {
                    printf("Warning: temp2 is below min temperature!");
                } else {
                    printf("temp2 in range.");
                    valid_temps++;
                }
                printf (" Temperature 3: %.1f\n", temp3);
                if (temp3 > MAX_TEMP) {
                    printf("Warning: temp3 exceeds max temperature!");
                } else if (temp3 < MIN_TEMP) {
                    printf("Warning: temp3 is below min temperature!");
                } else {
                    printf("temp3 in range.");
                    valid_temps++;
                }
                printf (" Temperature 4: %.1f\n", temp4);
                if (temp4 > MAX_TEMP) {
                    printf("Warning: temp4 exceeds max temperature!");
                } else if (temp4 < MIN_TEMP) {
                    printf("Warning: temp4 is below min temperature!");
                } else {
                    printf("temp4 in range.");
                    valid_temps++;
                }
                printf (" Temperature 5: %.1f\n", temp5);
                if (temp5 > MAX_TEMP) {
                    printf("Warning: temp5 exceeds max temperature!");
                } else if (temp5 < MIN_TEMP) {
                    printf("Warning: temp5 is below min temperature!");
                } else {
                    printf("temp5 in range.");
                    valid_temps++;
                }
                break;

            case 3:
                printf (" Statistics to be implemented \n");
                minTemp = min(temp1, min(temp2, min(temp3, min(temp4, temp5))));
                maxTemp = max(temp1, max(temp2, max(temp3, max(temp4, temp5))));
                avgTemp = (temp1 + temp2 + temp3 + temp4 + temp5) / 5;
                printf("Minimum Temperature: %.1f\n", minTemp);
                printf("Maximum Temperature: %.1f\n", maxTemp);
                printf("Average Temperature: %.1f\n", avgTemp);
                printf("Temperatures in range: %d\n", valid_temps);
                break;

            case 4:
                printf (" Exiting program.\n");
                break;

            default :
                printf (" Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}