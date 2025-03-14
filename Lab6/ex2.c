#include <stdio.h>
#include <stdlib.h>

// ------------------------ Create 2D Array ------------------------
int** create_2d_array(int rows, int cols, int init_value) {
    int** array = (int**)malloc(rows * sizeof(int*));
    if (array == NULL) {
        return NULL; 
    }

    for (int i = 0; i < rows; i++) {
        array[i] = (int*)malloc(cols * sizeof(int));
        if (array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }

        for (int j = 0; j < cols; j++) {
            array[i][j] = init_value;
        }
    }
    return array;
}

// ------------------------ Free 2D Array ------------------------
void free_2d_array(int** array, int rows) {
    if (array == NULL) return; 

    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

// ------------------------ Resize 2D Array ------------------------
int** resize_2d_array(int** array, int old_rows, int old_cols, 
                      int new_rows, int new_cols, int fill_value) {
    int** new_array = create_2d_array(new_rows, new_cols, fill_value);

    if (new_array == NULL) {
        return NULL; 
    }

    for (int i = 0; i < old_rows && i < new_rows; i++) {
        for (int j = 0; j < old_cols && j < new_cols; j++) {
            new_array[i][j] = array[i][j];
        }
    }

    free_2d_array(array, old_rows);

    return new_array;
}

// ------------------------ Print 2D Array ------------------------
void print_2d_array(int** array, int rows, int cols) {
    if (array == NULL) {
        printf("Array is NULL\n");
        return;
    }

    for (int i = 0; i < rows; i++) {
        printf("[");
        for (int j = 0; j < cols; j++) {
            printf("%d", array[i][j]);
            if (j < cols - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

// ------------------------ Main Function ------------------------
int main() {
    // -------- Create Array Example --------
    int rows = 3, cols = 4, init_value = 0;
    if (rows == NULL || cols == NULL) {
        printf("Null Inputs, Failed to create array.");
        return 0;
    };
    printf("\n--- Create 2D Array ---\n");
    printf("Input: rows = %d, cols = %d, init_value = %d\n", rows, cols, init_value);
    int** array = create_2d_array(rows, cols, init_value);
    if (array == NULL) {
        printf("Failed to allocate memory for 2D array.\n");
        return 1;
    }

    printf("Output: A %dx%d array initialized with %d\n", rows, cols, init_value);
    print_2d_array(array, rows, cols);

    // -------- Resize Array Example --------
    int new_rows = 4, new_cols = 5, fill_value = 9;
    printf("\n--- Resize 2D Array ---\n");
    printf("Resizing array to %dx%d with fill value %d\n", new_rows, new_cols, fill_value);
    array = resize_2d_array(array, rows, cols, new_rows, new_cols, fill_value);

    if (array == NULL) {
        printf("Failed to allocate memory for resized array.\n");
        return 1;
    }

    printf("Output: Resized Array\n");
    print_2d_array(array, new_rows, new_cols);

    // -------- Free Array --------
    printf("\n--- Free 2D Array ---\n");
    free_2d_array(array, new_rows);
    printf("Array successfully deallocated.\n");

    return 0;
}
