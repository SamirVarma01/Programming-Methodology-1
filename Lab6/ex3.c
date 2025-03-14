#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for string transformation types
#define TRANSFORM_UPPERCASE 0
#define TRANSFORM_LOWERCASE 1
#define TRANSFORM_REVERSE 2

// ------------------------ Sort Strings ------------------------
void sort_strings(char** strings, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(strings[j], strings[j + 1]) > 0) {
                char* temp = strings[j];
                strings[j] = strings[j + 1];
                strings[j + 1] = temp;
            }
        }
    }
}

// ------------------------ Remove Duplicates ------------------------
int remove_duplicates(char** strings, int count) {
    if (count == 0) return 0;

    int unique_count = 0;

    for (int i = 0; i < count; i++) {
        int is_duplicate = 0;

        for (int j = 0; j < unique_count; j++) {
            if (strcmp(strings[i], strings[j]) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            strings[unique_count++] = strings[i];
        }
    }

    return unique_count;
}

// ------------------------ Transform Strings ------------------------
char** transform_strings(char** strings, int count, int transform_type) {
    char** transformed = (char**)malloc(count * sizeof(char*));
    if (transformed == NULL) return NULL;

    for (int i = 0; i < count; i++) {
        transformed[i] = (char*)malloc(strlen(strings[i]) + 1);
        if (transformed[i] == NULL) {
            for (int j = 0; j < i; j++) free(transformed[j]);
            free(transformed);
            return NULL;
        }

        if (transform_type == TRANSFORM_UPPERCASE) {
            for (int j = 0; j < strlen(strings[i]); j++) {
                if (strings[i][j] >= 'a' && strings[i][j] <= 'z') {
                    transformed[i][j] = strings[i][j] - ('a' - 'A');
                } else {
                    transformed[i][j] = strings[i][j];
                }
            }
        } else if (transform_type == TRANSFORM_LOWERCASE) {
            for (int j = 0; j < strlen(strings[i]); j++) {
                if (strings[i][j] >= 'A' && strings[i][j] <= 'Z') {
                    transformed[i][j] = strings[i][j] + ('a' - 'A');
                } else {
                    transformed[i][j] = strings[i][j];
                }
            }
        } else if (transform_type == TRANSFORM_REVERSE) {
            int len = strlen(strings[i]);
            for (int j = 0; j < len; j++) {
                transformed[i][j] = strings[i][len - j - 1];
            }
        }

        transformed[i][strlen(strings[i])] = '\0';
    }

    return transformed;
}

void free_string_array(char** strings, int count) {
    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

void print_string_array(char** strings, int count) {
    printf("[");
    for (int i = 0; i < count; i++) {
        printf("\"%s\"", strings[i]);
        if (i < count - 1) printf(", ");
    }
    printf("]\n");
}

// ------------------------ Main Function ------------------------
int main() {
    // -------- Sort Example --------
    printf("\n--- Sort Strings ---\n");
    char* words1[] = {"Hellojhfhjsgfkagfhkjaegwfghjagfkjsdgkhsagfkafa", "p"};
    int count1 = sizeof(words1) / sizeof(words1[0]);

    printf("Input: ");
    print_string_array(words1, count1);

    sort_strings(words1, count1);

    printf("Sorted Output: ");
    print_string_array(words1, count1);

    // -------- Remove Duplicates Example --------
    printf("\n--- Remove Duplicates ---\n");
    char* words2[] = {"Hellojhfhjsgfkagfhkjaegwfghjagfkjsdgkhsagfkafa"};
    int count2 = sizeof(words2) / sizeof(words2[0]);

    printf("Input: ");
    print_string_array(words2, count2);

    int new_size = remove_duplicates(words2, count2);

    printf("Output: ");
    print_string_array(words2, new_size);
    printf("New size: %d\n", new_size);

    // -------- Transform Example --------
    printf("\n--- Transform Strings ---\n");
    char* words3[] = {"Hellojhfhjsgfkagfhkjaegwfghjagfkjsdgkhsagfkafa"};;
    int count3 = sizeof(words3) / sizeof(words3[0]);

    printf("Input Array: ");
    print_string_array(words3, count3);

    // Uppercase Transformation
    char** upper_transformed = transform_strings(words3, count3, TRANSFORM_UPPERCASE);
    printf("Transformation: Uppercase\nOutput Array: ");
    print_string_array(upper_transformed, count3);
    free_string_array(upper_transformed, count3);

    // Reverse Transformation
    char** reverse_transformed = transform_strings(words3, count3, TRANSFORM_REVERSE);
    printf("Transformation: Reverse\nOutput Array: ");
    print_string_array(reverse_transformed, count3);
    free_string_array(reverse_transformed, count3);

    return 0;
}
