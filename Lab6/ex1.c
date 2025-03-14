#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------ Tokenizer Function ------------------------
int tokenize_string(const char* str, char delimiter, char*** tokens) {
    if (str == NULL || tokens == NULL) {
        return -1;
    }

    int count = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == delimiter) {
            count++;
        }
    }
    count++;

    *tokens = (char**)malloc(count * sizeof(char*));
    if (*tokens == NULL) {
        return -1;
    }

    char* temp_str = (char*)malloc(strlen(str) + 1);
    if (temp_str == NULL) {
        free(*tokens);
        return -1;
    }
    strcpy(temp_str, str);

    size_t original_length = strlen(temp_str);

    int index = 0;
    char* start = temp_str;
    for (size_t i = 0; i <= original_length; i++) {
        if (temp_str[i] == delimiter || temp_str[i] == '\0') {
            temp_str[i] = '\0';
            if (strlen(start) > 0) {
                (*tokens)[index] = (char*)malloc(strlen(start) + 1);
                if ((*tokens)[index] == NULL) {
                    for (int j = 0; j < index; j++) {
                        free((*tokens)[j]);
                    }
                    free(*tokens);
                    free(temp_str);
                    return -1;
                }
                strcpy((*tokens)[index], start);
                index++;
            }
            start = &temp_str[i + 1];
        }
    }

    free(temp_str);
    return index;
}

// ------------------------ Filter Function ------------------------
int filter_strings(char** strings, int count, const char* substring, char*** filtered) {
    if (strings == NULL || filtered == NULL || substring == NULL) {
        return -1;
    }

    int match_count = 0;

    *filtered = (char**)malloc(count * sizeof(char*));
    if (*filtered == NULL) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (strstr(strings[i], substring)) {
            (*filtered)[match_count] = (char*)malloc(strlen(strings[i]) + 1);
            if ((*filtered)[match_count] == NULL) {
                for (int j = 0; j < match_count; j++) {
                    free((*filtered)[j]);
                }
                free(*filtered);
                return -1;
            }
            strcpy((*filtered)[match_count], strings[i]);
            match_count++;
        }
    }

    return match_count;
}

// ------------------------ Join Function ------------------------
char* join_strings(char** input, int count, const char* delimiter) {
    if (input == NULL || delimiter == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    for (int i = 0; i < count; i++) {
        total_length += strlen(input[i]);
    }

    total_length += (count - 1) * strlen(delimiter) + 1;

    char* result = (char*)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    strcpy(result, input[0]);
    for (int i = 1; i < count; i++) {
        strcat(result, delimiter);
        strcat(result, input[i]);
    }

    return result;
}

// ------------------------ Main Function ------------------------
int main() {
    // -------- Tokenizer Example --------
    char input[] = "aaasastsadgakdgehkfgKYWEFGKYWAGFKYAEWGFEYA-KWRGAKWRGKAGRKQ3Grkgrakw3rgagr4";
    char delimiter = '-';
    char** tokens = NULL;

    printf("\n--- Tokenizer ---\n");
    printf("Input String: \"%s\"\n", input);
    printf("Delimiter: '%c'\n", delimiter);

    int token_count = tokenize_string(input, delimiter, &tokens);
    if (token_count == -1) {
        printf("Tokenizer Memory allocation failed\n");
        return 1;
    }

    printf("Output Tokens: [");
    for (int i = 0; i < token_count; i++) {
        printf("\"%s\"", tokens[i]);
        if (i < token_count - 1) {
            printf(", ");
        }
        free(tokens[i]);
    }
    printf("]\nNumber of tokens: %d\n", token_count);
    free(tokens);

    // -------- Filter Example --------
    char* string_array[] = {"apple", "banana", "grape"};
    char** filtered_array = NULL;
    char substring[] = "ou";
    int size = 3;

    printf("\n--- Filter ---\n");
    printf("Input Array: [");
    for (int i = 0; i < size; i++) {
        printf("\"%s\"", string_array[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\nSubstring: \"%s\"\n", substring);

    int filtered_count = filter_strings(string_array, size, substring, &filtered_array);

    printf("Filtered Output: [");
    for (int i = 0; i < filtered_count; i++) {
        printf("\"%s\"", filtered_array[i]);
        if (i < filtered_count - 1) {
            printf(", ");
        }
        free(filtered_array[i]);
    }
    printf("]\nNumber of matches: %d\n", filtered_count);
    free(filtered_array);

    // -------- Join Example --------
    char* words[] = {"Hello", "world", "this", "is", "a", "test"};
    char join_delimiter[] = "-";
    int size2 = 6;

    printf("\n--- Join ---\n");
    printf("Input Array: [");
    for (int i = 0; i < size2; i++) {
        printf("\"%s\"", words[i]);
        if (i < size2-1) {
            printf(", ");
        }
    }
    printf("]\nDelimiter: \"%s\"\n", join_delimiter);

    char* joined_string = join_strings(words, size2, join_delimiter);

    if (joined_string == NULL) {
        printf("Join Memory allocation failed\n");
        return 1;
    }

    printf("Joined Output: \"%s\"\n", joined_string);
    free(joined_string);

    return 0;
}
