#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a CSV row
typedef struct {
    char** fields;      // Array of strings for each field
    int field_count;    // Number of fields in the row
} CSVRow;

// Structure to represent a CSV file
typedef struct {
    CSVRow* rows;       // Array of CSV rows
    int row_count;      // Number of rows
    int header_row;     // Whether the first row is a header (0 or 1)
} CSVData;

// Function prototypes
CSVRow parse_csv_line(const char* line);
void free_csv_row(CSVRow* row);
CSVData* read_csv_file(const char* filename, int header_row);
void free_csv_data(CSVData* data);
char** extract_column(CSVData* data, int column_index, int* count);
double* extract_numeric_column(CSVData* data, int column_index, int* count);
int compute_column_stats(CSVData* data, int column_index, 
                         double* min, double* max, double* avg);

#endif // CSV_PARSER_H