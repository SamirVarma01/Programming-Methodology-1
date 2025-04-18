// file_ops.c
#include "file_ops.h"
#include <ctype.h>  // For isspace()

// Safely open a file with error reporting
FILE* safe_fopen(const char* filename, const char* mode) {
    FILE* fp = fopen(filename, mode);
    
    if (fp == NULL) {
        // Get the error message
        char error_message[100];
        strerror_r(errno, error_message, sizeof(error_message));
        
        // Print error message with filename and mode
        printf("Error opening file '%s' in mode '%s': %s\n", 
               filename, mode, error_message);
    }
    
    return fp;
}

// Safely close a file and set the pointer to NULL
int safe_fclose(FILE** fp) {
    if (fp == NULL || *fp == NULL) {
        return -1;
    }
    
    int result = fclose(*fp);
    if (result == 0) {
        *fp = NULL;
    }
    
    return result;
}

// Count words in a file (like 'wc -w' command)
int count_words(const char* filename) {
    FILE* fp = safe_fopen(filename, "r");
    if (fp == NULL) {
        return -1;  // Return error code if file couldn't be opened
    }
    
    int word_count = 0;
    int in_word = 0;  // Flag to track if we're currently in a word
    int ch;
    
    // Read the file character by character
    while ((ch = fgetc(fp)) != EOF) {
        // Check if the character is a whitespace
        if (isspace(ch)) {
            // If we were in a word, we just finished one
            if (in_word) {
                in_word = 0;
            }
        } else {
            // If we weren't in a word, we just started one
            if (!in_word) {
                in_word = 1;
                word_count++;
            }
        }
    }
    
    // Check for read errors
    if (ferror(fp)) {
        printf("Error reading file '%s'\n", filename);
        safe_fclose(&fp);
        return -1;
    }
    
    safe_fclose(&fp);
    return word_count;
}

// Function to compare our word count with the Unix wc -w command
int compare_with_wc(const char* filename) {
    // Get word count using our implementation
    int our_count = count_words(filename);
    if (our_count < 0) {
        printf("Our implementation failed to count words in '%s'\n", filename);
        return -1;
    }
    
    // Get word count using wc -w
    char command[256];
    snprintf(command, sizeof(command), "wc -w %s", filename);
    
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        printf("Failed to run wc command\n");
        return -1;
    }
    
    int wc_count;
    char output[256];
    
    if (fgets(output, sizeof(output), pipe) != NULL) {
        // wc output format is: "   123 filename"
        sscanf(output, "%d", &wc_count);
    } else {
        printf("Failed to read wc command output\n");
        pclose(pipe);
        return -1;
    }
    
    pclose(pipe);
    
    // Compare the results
    printf("File: %s\n", filename);
    printf("Our count: %d\n", our_count);
    printf("wc -w count: %d\n", wc_count);
    printf("Difference: %d\n", our_count - wc_count);
    
    return (our_count == wc_count) ? 0 : 1;
}

// Main function as specified
int main() {
    // Create a test file
    FILE* fp = safe_fopen("test.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "This is a test file.\n");
        fprintf(fp, "It has multiple words on multiple lines.\n");
        fprintf(fp, "We will count these words.\n");
        safe_fclose(&fp);
    }
    
    // Count words in the file
    int words = count_words("test.txt");
    if (words >= 0) {
        printf("Number of words: %d\n", words);
    }
    
    // Test error handling
    words = count_words("nonexistent.txt");
    if (words < 0) {
        printf("Successfully detected non-existent file\n");
    }
    
    // Add the comparison with wc command
    printf("\n=== Comparing with wc -w command ===\n");
    compare_with_wc("test.txt");
    
    return 0;
}