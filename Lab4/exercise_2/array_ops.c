#include <stdio.h>

// Function to reverse the array
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

// Function to find an element in the array
int findElement(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // Return the index where target is found
        }
    }
    return -1; // Target not found
}

// Function to rotate the array left by given positions
void rotateLeft(int arr[], int size, int positions) {
    positions = positions % size; // Normalize positions if greater than size

    for (int i = 0; i < positions; i++) {
        int temp = arr[0];
        for (int j = 0; j < size - 1; j++) {
            arr[j] = arr[j + 1]; // Shift elements left
        }
        arr[size - 1] = temp; // Move first element to the end
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
