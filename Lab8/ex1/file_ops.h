#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

FILE* safe_fopen(const char* filename, const char* mode);

int safe_fclose(FILE** fp);

int count_words(const char* filename);

#endif 
