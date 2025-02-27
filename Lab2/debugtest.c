# include <stdio.h>

 // Temperature thresholds ( matching lecture examples )
const int MAX_TEMP = 100; // Maximum allowed temperature
const int MIN_TEMP = 0; // Minimum allowed temperature

// Function to process temperatures
void process_temperatures (void) {
    float temperatures[5];
    float sum = 0; 

 // Bug 1: Infinite Loop
    int count = 0;
    while (count <= 4) {
        printf ("Enter temperature %d: ", count + 1);
        scanf("%f", &temperatures[count]);
        sum += temperatures[count];
        count++;
    }

 // Bug 2: Uninitialized Variable Usage
    printf ("Sum of temperatures : %.1f\n", sum);

 // Bug 3: Logic Error in Temperature Check
    if ( temperatures[0] > MIN_TEMP && temperatures[0] < MAX_TEMP ) {
        printf (" Temperature 1 is in range\n");
    }
    if ( temperatures[1] > MIN_TEMP && temperatures[1] < MAX_TEMP ) {
        printf (" Temperature 2 is in range\n");
    }
    if ( temperatures[2] > MIN_TEMP && temperatures[2] < MAX_TEMP ) {
        printf (" Temperature 3 is in range\n");
    }
    if ( temperatures[3] > MIN_TEMP && temperatures[3] < MAX_TEMP ) {
        printf (" Temperature 4 is in range\n");
    }
    if ( temperatures[4] > MIN_TEMP && temperatures[4] < MAX_TEMP ) {
        printf (" Temperature 5 is in range\n");
    }

 // Bug 4: Incorrect Average Calculation
    float average = sum / 5; 
    printf (" Average temperature : %.2f\n", average );
}

int main(void) {
    process_temperatures ();
    return 0;
}