#include <stdio.h>
#define max_size 5

void reverse_array(int arr[max_size], int size) {
    int *left = arr;
    int *right = arr + (size - 1);

    while (left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

int count_occurrences(int arr[max_size], int size, int target) {
    int frequency = 0;
    int *left = arr;
    const int *right = arr + size;

    while (left < right) {
        if (*left == target) {
            frequency++;
        }
        left++;
    }

    return frequency;
}

void rotate_matrix(int size, int matrix [size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size / 2; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[i][size - 1 - j];
            matrix[i][size - 1 - j] = temp;
        }
    }
}

void find_bounds(int arr[max_size], int size, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    int *pMin = arr;
    int *pMax = arr;

    for (pMin = arr; pMin < arr + size; pMin++) {
        if (*pMin < *min) {
            *min = *pMin;
        }
    }
    for (pMax = arr; pMax < arr + size; pMax++) {
        if (*pMax > *max) {
            *max = *pMax;
        }
    }
}

int main() {
    const int size = -1;
    if (size > max_size || size <= 0) {
        printf("Invalid size!");
        return 0;
    } else {
        int arr[] = {1, 2, 3, 4, 5};
        const int length = sizeof(arr) / sizeof(arr[0]);
        int matrix[length][length] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
        int target = 2;
        int min, max;
        printf("Original Array: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }

        reverse_array(arr, size);
        printf("\nReversed Array: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }

        printf("\nOriginal Matrix:\n");
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    printf("%d ", matrix[i][j]);
                }
                printf("\n");
            }

        rotate_matrix(size, matrix);
        printf("Rotated Matrix:\n");
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    printf("%d ", matrix[i][j]);
                }
                printf("\n");
            }

        int frequency = count_occurrences(arr, size, target);
        printf("\nTarget = %d, Frequency = %d", target, frequency);

        find_bounds(arr, size, &min, &max);
        printf("\nMax: %d, Min: %d", max, min);
    }
}