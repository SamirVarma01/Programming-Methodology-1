#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int pad_right(char str[MAX_LENGTH], int target_length) {
    int current_length = strlen(str);

    if (target_length >= MAX_LENGTH) {
        target_length = MAX_LENGTH - 1; 
    }

    if (target_length <= current_length) {
        return current_length;
    }

    for (int i = current_length; i < target_length; i++) {
        str[i] = ' ';
    }

    str[target_length] = '\0';

    return target_length;
}

int find_pattern(const char str[MAX_LENGTH], const char pattern[MAX_LENGTH], int positions[MAX_LENGTH]) {
    int str_len = strlen(str);
    int pattern_len = strlen(pattern);
    int count = 0;

    if (pattern_len == 0 || pattern_len > str_len) {
        return 0;
    }

    for (int i = 0; i <= str_len - pattern_len; i++) {
        if (strncmp(&str[i], pattern, pattern_len) == 0) {
            positions[count++] = i; 
        }
    }

    return count; // Return number of occurrences
}

int main() {
    char str[MAX_LENGTH] = "";
    int target_length = 101;

    if (target_length > MAX_LENGTH || target_length < strlen(str)) {
        printf("Cannot perform padding, invalid size.\n");
    } else {
        printf("String Padding Test:\n");
        printf("Original: \"%s\"\n", str);

        int new_length = pad_right(str, target_length);
        
        printf("After padding to %d: \"%s\"\n", target_length, str);
        printf("Length: %d\n\n", new_length);
    }

    const char search_str[MAX_LENGTH] = "";
    const char pattern[MAX_LENGTH] = "b";
    int positions[MAX_LENGTH];

    if (strlen(pattern) == 0 || strlen(pattern) > strlen(search_str) || strlen(search_str) == 0) {
        printf("Cannot perform pattern search, invalid pattern or search string.\n");
    } else {
        printf("Pattern Search Test:\n");
        printf("String: \"%s\"\n", search_str);
        printf("Pattern: \"%s\"\n", pattern);

        int occurrences = find_pattern(search_str, pattern, positions);

        printf("Found %d occurrences at positions: ", occurrences);
        for (int i = 0; i < occurrences; i++) {
            printf("%d", positions[i]);
            if (i < occurrences - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
    return 0;
}