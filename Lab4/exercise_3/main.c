#include <stdio.h>

// Function declarations
void reverseArray(int arr[], int size);
int findMax(int arr[], int size);
float calculateAverage(int arr[], int size);
void printArray(int arr[], int size);

void reverseArray(int arr[], int size) {
    int l = 0, r = size - 1;
    while (l < r) {
        int temp = arr[l]; // Initialize temp variable for swapping
        arr[l] = arr[r];
        arr[r] = temp;
        // Increment/Decrement along array from both ends
        l++;
        r--;
    }
}

int findMax(int arr[], int size) {
    if (size == 0) return -1; // Handle empty array case

    int max = arr[0]; // Start with the first element
    for (int i = 1; i < size; i++) { // Iterate along array to check for max
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

float calculateAverage(int arr[], int size) {
    if (size == 0) return 0; // Handle empty array case

    float sum = 0;
    for (int i = 0; i < size; i++) { // Iterate along array to gather sum
        sum += arr[i];
    }
    return sum / size;
}

void printArray(int arr[], int size) {
    if (size == 0) {
        printf("Array is empty.\n"); // Error handling
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); // Print out array elements
    }
    printf("\n");
}

int main() {
    int size;

    // Get the array size from the user
    printf("Enter the number of elements: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid size. Please enter a positive integer.\n");
        return 1;
    }

    int arr[size]; // Declare array dynamically based on user input

    // Get the array elements from the user
    printf("Enter %d elements: ", size);
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input. Please enter integers only.\n");
            return 1;
        }
    }

    printf("Original array: ");
    printArray(arr, size);

    // Reverse the array
    reverseArray(arr, size);
    printf("Reversed array: ");
    printArray(arr, size);

    // Find maximum element
    int max = findMax(arr, size);
    printf("Maximum: %d\n", max);

    // Calculate average
    float avg = calculateAverage(arr, size);
    printf("Average: %.2f\n", avg);

    return 0;
}
