#include <stdio.h>
#include "array_ops.h"

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

    // Create a backup copy of the original array
    int originalArr[size];
    for (int i = 0; i < size; i++) {
        originalArr[i] = arr[i]; // Manually copy the original array
    }

    // Print original array
    printf("Original array: ");
    printArray(arr, size);

    // Rotate left by 2 positions
    for (int i = 0; i < size; i++) arr[i] = originalArr[i]; // Reset before rotating
    rotateLeft(arr, size, 2);
    printf("Array after rotating left by 2 positions: ");
    printArray(arr, size);

    // Reverse array
    for (int i = 0; i < size; i++) arr[i] = originalArr[i]; // Reset before reversing
    reverseArray(arr, size);
    printf("Reversed array: ");
    printArray(arr, size);

    // Find an element in the original array
    for (int i = 0; i < size; i++) arr[i] = originalArr[i]; // Reset before searching
    int target;
    printf("Enter an element to find: ");
    if (scanf("%d", &target) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        return 1;
    }

    int index = findElement(arr, size, target);
    if (index != -1) {
        printf("Element %d found at index %d\n", target, index);
    } else {
        printf("Element %d not found\n", target);
    }

    return 0;
}
