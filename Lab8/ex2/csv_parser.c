#include "csv_parser.h"

// Parse a CSV line into an array of strings
CSVRow parse_csv_line(const char* line) {
    CSVRow row;
    row.fields = NULL;
    row.field_count = 0;
    
    if (line == NULL || *line == '\0') {
        return row;
    }
    
    // Count the number of fields to allocate memory
    int field_count = 1;  // Start with 1 for the first field
    int in_quotes = 0;
    
    for (const char* p = line; *p; p++) {
        if (*p == '"') {
            in_quotes = !in_quotes;
        } else if (*p == ',' && !in_quotes) {
            field_count++;
        }
    }
    
    // Allocate memory for the fields
    row.fields = (char**)malloc(field_count * sizeof(char*));
    if (row.fields == NULL) {
        return row;
    }
    
    // Parse the line into fields
    const char* p = line;
    char* temp = (char*)malloc(strlen(line) + 1);
    if (temp == NULL) {
        free(row.fields);
        row.fields = NULL;
        return row;
    }
    
    int field_idx = 0;
    in_quotes = 0;
    char* temp_ptr = temp;
    
    while (*p) {
        if (*p == '"') {
            in_quotes = !in_quotes;
            p++;  // Skip the quote character
        } else if (*p == ',' && !in_quotes) {
            // End of field
            *temp_ptr = '\0';
            row.fields[field_idx] = strdup(temp);
            field_idx++;
            temp_ptr = temp;
            p++;
        } else {
            *temp_ptr++ = *p++;
        }
    }
    
    // Don't forget the last field
    *temp_ptr = '\0';
    row.fields[field_idx] = strdup(temp);
    field_idx++;
    
    row.field_count = field_idx;
    free(temp);
    
    return row;
}

// Free memory allocated for a CSVRow
void free_csv_row(CSVRow* row) {
    if (row == NULL || row->fields == NULL) return;
    
    for (int i = 0; i < row->field_count; i++) {
        free(row->fields[i]);
    }
    free(row->fields);
    row->fields = NULL;
    row->field_count = 0;
}

// Read a CSV file and parse it into a CSVData structure
CSVData* read_csv_file(const char* filename, int header_row) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }
    
    CSVData* data = (CSVData*)malloc(sizeof(CSVData));
    if (data == NULL) {
        fclose(file);
        return NULL;
    }
    
    data->rows = NULL;
    data->row_count = 0;
    data->header_row = header_row;
    
    // Read file line by line
    char line[1024];  // Assume lines are not longer than 1024 characters
    int capacity = 10;  // Initial capacity
    
    data->rows = (CSVRow*)malloc(capacity * sizeof(CSVRow));
    if (data->rows == NULL) {
        free(data);
        fclose(file);
        return NULL;
    }
    
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character if present
        size_t len = strlen(line);
        if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            // Check for CR+LF (Windows line endings)
            if (len > 1 && line[len - 2] == '\r') {
                line[len - 2] = '\0';
            }
        }
        
        // Parse the line
        CSVRow row = parse_csv_line(line);
        
        // Resize the rows array if needed
        if (data->row_count >= capacity) {
            capacity *= 2;
            CSVRow* new_rows = (CSVRow*)realloc(data->rows, capacity * sizeof(CSVRow));
            if (new_rows == NULL) {
                // Handle allocation failure
                for (int i = 0; i < data->row_count; i++) {
                    free_csv_row(&data->rows[i]);
                }
                free(data->rows);
                free(data);
                fclose(file);
                return NULL;
            }
            data->rows = new_rows;
        }
        
        // Add the row to the data
        data->rows[data->row_count] = row;
        data->row_count++;
    }
    
    fclose(file);
    return data;
}

// Free memory allocated for a CSVData structure
void free_csv_data(CSVData* data) {
    if (data == NULL) return;
    
    for (int i = 0; i < data->row_count; i++) {
        free_csv_row(&data->rows[i]);
    }
    free(data->rows);
    free(data);
}

// Extract a specific column from CSVData as an array of strings
char** extract_column(CSVData* data, int column_index, int* count) {
    if (data == NULL || data->row_count == 0 || column_index < 0) {
        *count = 0;
        return NULL;
    }
    
    // Check if column_index is valid
    if (data->row_count > 0 && column_index >= data->rows[0].field_count) {
        *count = 0;
        return NULL;
    }
    
    // Determine how many rows to process (skip header if present)
    int start_row = data->header_row ? 1 : 0;
    *count = data->row_count - start_row;
    
    if (*count <= 0) {
        *count = 0;
        return NULL;
    }
    
    char** column = (char**)malloc(*count * sizeof(char*));
    if (column == NULL) {
        *count = 0;
        return NULL;
    }
    
    for (int i = 0; i < *count; i++) {
        CSVRow* row = &data->rows[i + start_row];
        if (column_index < row->field_count) {
            column[i] = strdup(row->fields[column_index]);
        } else {
            column[i] = strdup("");  // Empty field for missing columns
        }
    }
    
    return column;
}

// Extract a specific column from CSVData as an array of doubles
double* extract_numeric_column(CSVData* data, int column_index, int* count) {
    char** str_column = extract_column(data, column_index, count);
    if (str_column == NULL) {
        return NULL;
    }
    
    double* numeric_column = (double*)malloc(*count * sizeof(double));
    if (numeric_column == NULL) {
        for (int i = 0; i < *count; i++) {
            free(str_column[i]);
        }
        free(str_column);
        *count = 0;
        return NULL;
    }
    
    for (int i = 0; i < *count; i++) {
        char* endptr;
        numeric_column[i] = strtod(str_column[i], &endptr);
        
        // Check if conversion was successful
        if (*endptr != '\0') {
            // Handle non-numeric data (set to 0)
            numeric_column[i] = 0.0;
        }
        
        free(str_column[i]);
    }
    
    free(str_column);
    return numeric_column;
}

// Compute statistics on a numeric column
int compute_column_stats(CSVData* data, int column_index, 
                         double* min, double* max, double* avg) {
    if (data == NULL || min == NULL || max == NULL || avg == NULL) {
        return -1;
    }
    
    int count;
    double* column = extract_numeric_column(data, column_index, &count);
    
    if (column == NULL || count == 0) {
        return -1;
    }
    
    *min = column[0];
    *max = column[0];
    double sum = 0.0;
    
    for (int i = 0; i < count; i++) {
        if (column[i] < *min) {
            *min = column[i];
        }
        if (column[i] > *max) {
            *max = column[i];
        }
        sum += column[i];
    }
    
    *avg = sum / count;
    free(column);
    
    return 0;
}

int main() {
    // Create a sample CSV file for testing
    FILE* fp = fopen("students.csv", "w");
    if (fp == NULL) {
        perror("Error creating test file");
        return 1;
    }
    
    fprintf(fp, "id,name,age,score\n");
    fprintf(fp, "1,\"Smith, John\",25,95.5\n");
    fprintf(fp, "2,Jane Doe,22,88.0\n");
    fprintf(fp, "3,\"Williams, Robert\",28,76.5\n");
    fprintf(fp, "4,\"Johnson, Emily\",21,92.0\n");
    fprintf(fp, "5,Michael Brown,24,65.5\n");
    fclose(fp);
    
    // Read and parse the CSV file
    CSVData* data = read_csv_file("students.csv", 1);
    if (data == NULL) {
        printf("Failed to read CSV file\n");
        return 1;
    }
    
    // Extract and display the name column
    int count;
    char** names = extract_column(data, 1, &count);
    if (names != NULL) {
        printf("\nStudent names:\n");
        for (int i = 0; i < count; i++) {
            printf("%s\n", names[i]);
        }
        
        // Free the extracted column
        for (int i = 0; i < count; i++) {
            free(names[i]);
        }
        free(names);
    }
    
    // Compute statistics on the score column
    double min, max, avg;
    if (compute_column_stats(data, 3, &min, &max, &avg) == 0) {
        printf("\nScore statistics:\n");
        printf("Min: %.1f\n", min);
        printf("Max: %.1f\n", max);
        printf("Average: %.1f\n", avg);
    }
    
    // Clean up
    free_csv_data(data);
    
    // ===== ERROR HANDLING TESTS =====
    printf("\n=== Testing Error Handling for Malformed CSVs ===\n");
    
    // Test 1: Nonexistent file
    printf("\nTest 1: Nonexistent file\n");
    data = read_csv_file("nonexistent.csv", 1);
    if (data == NULL) {
        printf("✓ Successfully detected missing file\n");
    } else {
        printf("✗ Failed to detect missing file\n");
        free_csv_data(data);
    }
    
    // Test 2: Unclosed quotes
    fp = fopen("malformed1.csv", "w");
    if (fp) {
        fprintf(fp, "id,name,age,score\n");
        fprintf(fp, "1,\"Smith, John,25,95.5\n");  // Missing closing quote
        fclose(fp);
        
        printf("\nTest 2: Unclosed quotes\n");
        data = read_csv_file("malformed1.csv", 1);
        if (data) {
            printf("Parsed with %d rows\n", data->row_count);
            printf("First row has %d fields\n", data->rows[0].field_count);
            if (data->row_count > 1) {
                printf("Second row field content check: %s\n", 
                       data->rows[1].fields[0]);
            }
            free_csv_data(data);
        } else {
            printf("Parser rejected file with unclosed quotes\n");
        }
    }
    
    // Test 3: Inconsistent number of columns
    fp = fopen("malformed2.csv", "w");
    if (fp) {
        fprintf(fp, "id,name,age,score\n");
        fprintf(fp, "1,John,25\n");                // Missing a column
        fprintf(fp, "2,Jane,22,88.0,extra\n");     // Extra column
        fclose(fp);
        
        printf("\nTest 3: Inconsistent number of columns\n");
        data = read_csv_file("malformed2.csv", 1);
        if (data) {
            printf("Parsed with %d rows\n", data->row_count);
            for (int i = 0; i < data->row_count; i++) {
                printf("Row %d has %d fields\n", i, data->rows[i].field_count);
            }
            
            // Test column extraction with inconsistent columns
            int count;
            double* scores = extract_numeric_column(data, 3, &count);
            if (scores) {
                printf("Extracted %d values from score column\n", count);
                free(scores);
            } else {
                printf("Failed to extract score column (expected for incomplete rows)\n");
            }
            
            free_csv_data(data);
        } else {
            printf("Parser rejected file with inconsistent columns\n");
        }
    }
    
    // Test 4: Empty file
    fp = fopen("malformed3.csv", "w");
    fclose(fp);
    
    printf("\nTest 4: Empty file\n");
    data = read_csv_file("malformed3.csv", 1);
    if (data) {
        printf("Parsed empty file with %d rows\n", data->row_count);
        free_csv_data(data);
    } else {
        printf("Parser rejected empty file\n");
    }
    
    // Test 5: Invalid numeric data
    fp = fopen("malformed4.csv", "w");
    if (fp) {
        fprintf(fp, "id,name,age,score\n");
        fprintf(fp, "1,John,twenty-five,not-a-number\n");
        fclose(fp);
        
        printf("\nTest 5: Invalid numeric data\n");
        data = read_csv_file("malformed4.csv", 1);
        if (data) {
            // Test numeric parsing
            double min, max, avg;
            int result = compute_column_stats(data, 3, &min, &max, &avg);
            if (result == 0) {
                printf("Computed stats on non-numeric data: Min=%.1f, Max=%.1f, Avg=%.1f\n", 
                      min, max, avg);
            } else {
                printf("Correctly failed to compute stats on invalid data\n");
            }
            
            // Extract non-numeric column as numbers
            int count;
            double* ages = extract_numeric_column(data, 2, &count);
            if (ages) {
                printf("Converted non-numeric 'age' column: %f\n", ages[0]);
                free(ages);
            } else {
                printf("Failed to extract non-numeric column\n");
            }
            
            free_csv_data(data);
        } else {
            printf("Parser rejected file with invalid numeric data\n");
        }
    }

    return 0;
}