#include <stdio.h>
#include <stdlib.h>

// Dynamic array structure
typedef struct {
    int* data;        // Pointer to the data array
    int size;         // Current number of elements
    int capacity;     // Maximum capacity
} DynamicArray;

// Create and initialize a dynamic array
DynamicArray* createArray(int initialCapacity) {
    if (initialCapacity <= 0) return NULL; // Invalid capacity check

    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (!arr) return NULL; // Allocation failure

    arr->data = (int*)malloc(initialCapacity * sizeof(int));
    if (!arr->data) {
        free(arr);
        return NULL;
    }

    arr->size = 0;
    arr->capacity = initialCapacity;
    return arr;
}

// Free memory allocated for the dynamic array
void destroyArray(DynamicArray* arr) {
    if (!arr) return; // NULL pointer check

    free(arr->data);
    free(arr);
}

// Resize array to new capacity
int resizeArray(DynamicArray* arr, int newCapacity) {
    if (!arr || newCapacity <= 0) return 0; // NULL pointer or invalid capacity check

    if (newCapacity < arr->size) {
        arr->size = newCapacity; // Shrink the size to fit the new capacity
    }

    int* temp = (int*)realloc(arr->data, newCapacity * sizeof(int));
    if (!temp) return 0; // Allocation failure

    arr->data = temp;
    arr->capacity = newCapacity;
    return 1; // Success
}

// Add an element to the end of the array
int pushBack(DynamicArray* arr, int value) {
    if (!arr) return 0; // NULL pointer check

    if (arr->size >= arr->capacity) {
        if (!resizeArray(arr, arr->capacity * 2)) return 0; // Resize failed
    }
    arr->data[arr->size++] = value;
    return 1; // Success
}

// Get element at specified index
int getAt(DynamicArray* arr, int index) {
    if (!arr || index < 0 || index >= arr->size) return -1; // NULL pointer or out of bounds
    return arr->data[index];
}

// Set element at specified index
int setAt(DynamicArray* arr, int index, int value) {
    if (!arr || index < 0 || index >= arr->size) return 0; // NULL pointer or out of bounds
    arr->data[index] = value;
    return 1; // Success
}

// Insert element at specific index
int insertAt(DynamicArray* arr, int index, int value) {
    if (!arr || index < 0 || index > arr->size) return 0; // NULL pointer or out of bounds

    if (arr->size >= arr->capacity) {
        if (!resizeArray(arr, arr->capacity * 2)) return 0; // Resize failed
    }

    for (int i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[index] = value;
    arr->size++;
    return 1; // Success
}

// Remove element at specified index
int removeAt(DynamicArray* arr, int index) {
    if (!arr || index < 0 || index >= arr->size) return 0; // NULL pointer or out of bounds

    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
    return 1; // Success
}

// Find the first occurrence of a value
int find(DynamicArray* arr, int value) {
    if (!arr) return -1; // NULL pointer check

    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == value) return i;
    }
    return -1; // Not found
}

// Clear the array
void clear(DynamicArray* arr) {
    if (!arr) return; // NULL pointer check

    arr->size = 0;
}

// Check if the array is empty
int isEmpty(DynamicArray* arr) {
    if (!arr) return 1; // NULL pointer check
    return arr->size == 0;
}

// Get the size of the array
int size(DynamicArray* arr) {
    if (!arr) return -1; // NULL pointer check
    return arr->size;
}

// Get the capacity of the array
int capacity(DynamicArray* arr) {
    if (!arr) return -1; // NULL pointer check
    return arr->capacity;
}

// Print array contents
void printArray(DynamicArray* arr) {
    if (!arr) {
        printf("Invalid array.\n");
        return;
    }

    printf("Dynamic Array:\n");
    printf("Data: [");
    for (int i = 0; i < arr->size; i++) {
        printf("%d%s", arr->data[i], i == arr->size - 1 ? "" : ", ");
    }
    printf("]\nSize: %d\nCapacity: %d\n\n", arr->size, arr->capacity);
}

int main() {
    DynamicArray* arr = createArray(-2);  

    printArray(arr);

    pushBack(arr, 1);
    pushBack(arr, 1);
    pushBack(arr, 1);
    printArray(arr);

    int atIndex = getAt(arr, 2);
    printf("At Index 2: %d\n", atIndex);

    clear(arr);
    printf("\nAfter clearing the array:\n");
    printArray(arr);

    destroyArray(arr);
    return 0;
}