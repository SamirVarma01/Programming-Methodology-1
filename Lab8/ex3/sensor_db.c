// sensor_db.c
#include "sensor_db.h"
#include <unistd.h>  // For ftruncate

// Open or create a sensor database file
SensorDB* open_sensor_db(const char* filename, const char* mode) {
    FILE* fp = fopen(filename, mode);
    if (!fp) return NULL;
    
    SensorDB* db = malloc(sizeof(SensorDB));
    if (!db) {
        fclose(fp);
        return NULL;
    }
    
    db->file = fp;
    db->record_count = 0;
    
    // If opening in read mode, count existing records
    if (strchr(mode, 'r')) {
        fseek(fp, 0, SEEK_END);
        long file_size = ftell(fp);
        db->record_count = file_size / sizeof(SensorData);
        rewind(fp);
    }
    
    return db;
}

// Close a sensor database and free resources
int close_sensor_db(SensorDB* db) {
    if (!db || !db->file) return -1;
    
    int result = fclose(db->file);
    free(db);
    return result;
}

// Write sensor data to a binary file
int write_sensor_data(const char* filename, SensorData* sensors, int count) {
    if (!filename || !sensors || count <= 0) return -1;
    
    FILE* file = fopen(filename, "wb");
    if (!file) return -1;
    
    size_t written = fwrite(sensors, sizeof(SensorData), count, file);
    fclose(file);
    
    return (written == (size_t)count) ? 0 : -1;
}

// Read all sensor data from a binary file
SensorData* read_sensor_data(const char* filename, int* count) {
    if (!filename || !count) return NULL;
    
    FILE* file = fopen(filename, "rb");
    if (!file) {
        *count = 0;
        return NULL;
    }
    
    // Get file size and calculate record count
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    *count = file_size / sizeof(SensorData);
    rewind(file);
    
    if (*count == 0) {
        fclose(file);
        return NULL;
    }
    
    // Allocate memory for the records
    SensorData* data = (SensorData*)malloc(*count * sizeof(SensorData));
    if (!data) {
        fclose(file);
        *count = 0;
        return NULL;
    }
    
    // Read all records
    size_t read_count = fread(data, sizeof(SensorData), *count, file);
    fclose(file);
    
    if (read_count != (size_t)*count) {
        free(data);
        *count = 0;
        return NULL;
    }
    
    return data;
}

// Read a sensor record at a specific index
int read_sensor_at(const char* filename, int index, SensorData* record) {
    if (!filename || !record || index < 0) return -1;
    
    FILE* file = fopen(filename, "rb");
    if (!file) return -1;
    
    // Get file size and calculate record count
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    int record_count = file_size / sizeof(SensorData);
    
    if (index >= record_count) {
        fclose(file);
        return -1;
    }
    
    // Seek to the record position
    fseek(file, index * sizeof(SensorData), SEEK_SET);
    
    // Read the record
    size_t read_count = fread(record, sizeof(SensorData), 1, file);
    fclose(file);
    
    return (read_count == 1) ? 0 : -1;
}

// Add a sensor reading to the database
int add_sensor_reading(SensorDB* db, const SensorData* reading) {
    if (!db || !db->file || !reading) return -1;
    
    // Seek to end of file for appending
    fseek(db->file, 0, SEEK_END);
    
    // Write the sensor reading to the file
    size_t write_count = fwrite(reading, sizeof(SensorData), 1, db->file);
    if (write_count != 1) return -1;
    
    // Increment record count
    db->record_count++;
    
    // Flush the file to ensure data is written
    fflush(db->file);
    
    return 0;
}

// Add multiple sensor readings to the database
int add_sensor_readings(SensorDB* db, const SensorData* readings, int count) {
    if (!db || !db->file || !readings || count <= 0) return -1;
    
    // Seek to end of file for appending
    fseek(db->file, 0, SEEK_END);
    
    // Write all readings to the file
    size_t write_count = fwrite(readings, sizeof(SensorData), count, db->file);
    if (write_count != (size_t)count) return -1;
    
    // Update record count
    db->record_count += count;
    
    // Flush the file to ensure data is written
    fflush(db->file);
    
    return 0;
}

// Get a sensor reading at a specific index
int get_sensor_reading(SensorDB* db, unsigned int index, SensorData* reading) {
    if (!db || !db->file || !reading || index >= db->record_count) return -1;
    
    // Seek to the specific position
    fseek(db->file, index * sizeof(SensorData), SEEK_SET);
    
    // Read the sensor reading
    size_t read_count = fread(reading, sizeof(SensorData), 1, db->file);
    
    return (read_count == 1) ? 0 : -1;
}

// Get the number of records in the database
int get_record_count(SensorDB* db) {
    if (!db) return -1;
    return db->record_count;
}

// Find sensor readings by sensor ID
SensorData* find_readings_by_sensor(SensorDB* db, int sensor_id, int* count_out) {
    if (!db || !db->file || !count_out) {
        if (count_out) *count_out = 0;
        return NULL;
    }
    
    // Reset count
    *count_out = 0;
    
    // Count matching readings first
    SensorData temp;
    int match_count = 0;
    
    rewind(db->file);
    for (unsigned int i = 0; i < db->record_count; i++) {
        if (fread(&temp, sizeof(SensorData), 1, db->file) != 1) {
            return NULL;
        }
        
        if (temp.id == sensor_id) {
            match_count++;
        }
    }
    
    if (match_count == 0) {
        return NULL;
    }
    
    // Allocate memory for matching readings
    SensorData* results = (SensorData*)malloc(match_count * sizeof(SensorData));
    if (!results) {
        return NULL;
    }
    
    // Read matching readings
    rewind(db->file);
    int result_idx = 0;
    
    for (unsigned int i = 0; i < db->record_count; i++) {
        if (fread(&temp, sizeof(SensorData), 1, db->file) != 1) {
            free(results);
            return NULL;
        }
        
        if (temp.id == sensor_id) {
            results[result_idx++] = temp;
        }
    }
    
    *count_out = match_count;
    return results;
}

// Find sensor readings within a timestamp range
SensorData* find_readings_by_timerange(SensorDB* db, 
                                     unsigned long start_time, 
                                     unsigned long end_time, 
                                     int* count_out) {
    if (!db || !db->file || !count_out || start_time > end_time) {
        if (count_out) *count_out = 0;
        return NULL;
    }
    
    // Reset count
    *count_out = 0;
    
    // Count matching readings first
    SensorData temp;
    int match_count = 0;
    
    rewind(db->file);
    for (unsigned int i = 0; i < db->record_count; i++) {
        if (fread(&temp, sizeof(SensorData), 1, db->file) != 1) {
            return NULL;
        }
        
        if (temp.timestamp >= start_time && temp.timestamp <= end_time) {
            match_count++;
        }
    }
    
    if (match_count == 0) {
        return NULL;
    }
    
    // Allocate memory for matching readings
    SensorData* results = (SensorData*)malloc(match_count * sizeof(SensorData));
    if (!results) {
        return NULL;
    }
    
    // Read matching readings
    rewind(db->file);
    int result_idx = 0;
    
    for (unsigned int i = 0; i < db->record_count; i++) {
        if (fread(&temp, sizeof(SensorData), 1, db->file) != 1) {
            free(results);
            return NULL;
        }
        
        if (temp.timestamp >= start_time && temp.timestamp <= end_time) {
            results[result_idx++] = temp;
        }
    }
    
    *count_out = match_count;
    return results;
}

// Update a sensor reading at a specific index
int update_sensor_reading(SensorDB* db, unsigned int index, const SensorData* reading) {
    if (!db || !db->file || !reading || index >= db->record_count) return -1;
    
    // Seek to the specific position
    fseek(db->file, index * sizeof(SensorData), SEEK_SET);
    
    // Write the updated sensor reading
    size_t write_count = fwrite(reading, sizeof(SensorData), 1, db->file);
    
    // Flush the file to ensure data is written
    fflush(db->file);
    
    return (write_count == 1) ? 0 : -1;
}

// Delete a sensor reading at a specific index
int delete_sensor_reading(SensorDB* db, unsigned int index) {
    if (!db || !db->file || index >= db->record_count) return -1;
    
    // We'll implement deletion by shifting all records after the deleted one
    SensorData* buffer = (SensorData*)malloc((db->record_count - index - 1) * sizeof(SensorData));
    if (!buffer) return -1;
    
    // Read all records after the one to be deleted
    fseek(db->file, (index + 1) * sizeof(SensorData), SEEK_SET);
    size_t read_count = fread(buffer, sizeof(SensorData), db->record_count - index - 1, db->file);
    
    if (read_count != db->record_count - index - 1) {
        free(buffer);
        return -1;
    }
    
    // Write these records back, starting at the position of the deleted record
    fseek(db->file, index * sizeof(SensorData), SEEK_SET);
    size_t write_count = fwrite(buffer, sizeof(SensorData), read_count, db->file);
    
    free(buffer);
    
    if (write_count != read_count) {
        return -1;
    }
    
    // Update record count
    db->record_count--;
    
    // Truncate the file to remove the extra record at the end
    #ifdef _WIN32
    // Windows-specific file truncation
    _chsize(fileno(db->file), db->record_count * sizeof(SensorData));
    #else
    // POSIX file truncation
    ftruncate(fileno(db->file), db->record_count * sizeof(SensorData));
    #endif
    
    // Flush the file to ensure data is written
    fflush(db->file);
    
    return 0;
}

// Calculate statistics for a specific sensor
int calculate_sensor_stats(SensorDB* db, int sensor_id, 
                          float* min_value, float* max_value, float* avg_value) {
    if (!db || !db->file || !min_value || !max_value || !avg_value) return -1;
    
    int count;
    SensorData* readings = find_readings_by_sensor(db, sensor_id, &count);
    
    if (!readings || count == 0) {
        return -1;
    }
    
    // Calculate min, max, and average value
    *min_value = readings[0].value;
    *max_value = readings[0].value;
    float sum = readings[0].value;
    
    for (int i = 1; i < count; i++) {
        if (readings[i].value < *min_value) {
            *min_value = readings[i].value;
        }
        if (readings[i].value > *max_value) {
            *max_value = readings[i].value;
        }
        sum += readings[i].value;
    }
    
    *avg_value = sum / count;
    
    free(readings);
    return 0;
}

int main() {
    // Create test data and run normal tests as you have now
    SensorData sensors[] = {
        {1, "Temperature", 25.5, 1234567890},
        {2, "Humidity", 45.0, 1234567891},
        {3, "Pressure", 1013.25, 1234567892}
    };
    
    // Write data to binary file
    if (write_sensor_data("sensors.bin", sensors, 3) != 0) {
        printf("Failed to write sensor data\n");
        return 1;
    }
    
    // Read and display all records
    int count;
    SensorData* data = read_sensor_data("sensors.bin", &count);
    if (data != NULL) {
        printf("Read %d sensor records:\n", count);
        for (int i = 0; i < count; i++) {
            printf("ID: %d, Type: %s, Value: %.2f, Time: %ld\n",
                  data[i].id, data[i].type, data[i].value, data[i].timestamp);
        }
        free(data);
    }
    
    // Test random access
    SensorData record;
    if (read_sensor_at("sensors.bin", 1, &record) == 0) {
        printf("\nRecord at index 1:\n");
        printf("ID: %d, Type: %s, Value: %.2f, Time: %ld\n",
              record.id, record.type, record.value, record.timestamp);
    }
    
    // =================== ERROR HANDLING TESTS ===================
    printf("\n===== Testing Error Handling =====\n");
    
    // Test 1: Access non-existent file
    printf("\nTest 1: Non-existent file\n");
    SensorDB* db = open_sensor_db("nonexistent.bin", "rb");
    if (db == NULL) {
        printf("✓ Successfully detected non-existent file\n");
    } else {
        printf("✗ Failed to detect non-existent file\n");
        close_sensor_db(db);
    }
    
    // Test 2: Access out-of-bounds record
    printf("\nTest 2: Out-of-bounds record access\n");
    db = open_sensor_db("sensors.bin", "rb");
    if (db != NULL) {
        SensorData out_of_bounds;
        int result = get_sensor_reading(db, 999, &out_of_bounds);
        if (result == -1) {
            printf("✓ Successfully detected out-of-bounds access\n");
        } else {
            printf("✗ Failed to detect out-of-bounds access\n");
        }
        close_sensor_db(db);
    }
    
    // Test 3: Corrupted file (truncated)
    printf("\nTest 3: Truncated file\n");
    FILE* corrupt_file = fopen("corrupted.bin", "wb");
    if (corrupt_file != NULL) {
        // Write partial record (truncated)
        fwrite(sensors, sizeof(SensorData) / 2, 1, corrupt_file);
        fclose(corrupt_file);
        
        // Try to read the corrupted file
        int corrupt_count;
        SensorData* corrupt_data = read_sensor_data("corrupted.bin", &corrupt_count);
        if (corrupt_data == NULL || corrupt_count == 0) {
            printf("✓ Successfully handled truncated file\n");
        } else {
            printf("✗ Failed to detect truncated file (read %d records)\n", corrupt_count);
            free(corrupt_data);
        }
    }
    
    // Test 4: Corrupted file (invalid size)
    printf("\nTest 4: File with invalid size\n");
    corrupt_file = fopen("invalid_size.bin", "wb");
    if (corrupt_file != NULL) {
        // Write odd number of bytes (not multiple of sizeof(SensorData))
        char odd_data[100];
        memset(odd_data, 0xAA, sizeof(odd_data));
        fwrite(odd_data, sizeof(odd_data), 1, corrupt_file);
        fclose(corrupt_file);
        
        // Try to read the file with invalid size
        int invalid_count;
        SensorData* invalid_data = read_sensor_data("invalid_size.bin", &invalid_count);
        printf("Read %d records from file with invalid size\n", invalid_count);
        if (invalid_data != NULL) {
            free(invalid_data);
        }
    }
    
    // Test 5: NULL parameters
    printf("\nTest 5: NULL parameters\n");
    int null_result = write_sensor_data(NULL, sensors, 3);
    if (null_result == -1) {
        printf("✓ write_sensor_data correctly handles NULL filename\n");
    } else {
        printf("✗ write_sensor_data failed to handle NULL filename\n");
    }
    
    null_result = write_sensor_data("sensors.bin", NULL, 3);
    if (null_result == -1) {
        printf("✓ write_sensor_data correctly handles NULL data\n");
    } else {
        printf("✗ write_sensor_data failed to handle NULL data\n");
    }
    
    // Test 6: Delete and update operations
    printf("\nTest 6: Delete and update operations\n");
    db = open_sensor_db("sensors.bin", "rb+");
    if (db != NULL) {
        // Test deleting a record
        int delete_result = delete_sensor_reading(db, 0);
        if (delete_result == 0) {
            printf("✓ Successfully deleted record\n");
            printf("  New record count: %d\n", db->record_count);
            
            // Verify the delete worked by reading first record (should be old record 1)
            SensorData first_record;
            if (get_sensor_reading(db, 0, &first_record) == 0) {
                printf("  First record now: ID %d, Type %s\n", 
                       first_record.id, first_record.type);
            }
        } else {
            printf("✗ Failed to delete record\n");
        }
        
        // Test updating a record
        if (db->record_count > 0) {
            SensorData updated = {99, "Updated", 100.0, 1234567899};
            int update_result = update_sensor_reading(db, 0, &updated);
            if (update_result == 0) {
                printf("✓ Successfully updated record\n");
                
                // Verify the update worked
                SensorData check;
                if (get_sensor_reading(db, 0, &check) == 0) {
                    printf("  Updated record: ID %d, Type %s, Value %.1f\n", 
                           check.id, check.type, check.value);
                }
            } else {
                printf("✗ Failed to update record\n");
            }
        }
        
        close_sensor_db(db);
    }
    
    // Test 7: Finding records with non-existent criteria
    printf("\nTest 7: Searching for non-existent records\n");
    db = open_sensor_db("sensors.bin", "rb");
    if (db != NULL) {
        int search_count;
        SensorData* search_results = find_readings_by_sensor(db, 999, &search_count);
        if (search_results == NULL && search_count == 0) {
            printf("✓ find_readings_by_sensor correctly handles non-existent sensor ID\n");
        } else {
            printf("✗ find_readings_by_sensor failed with non-existent sensor ID\n");
            if (search_results) free(search_results);
        }
        
        search_results = find_readings_by_timerange(db, 9999999999, 9999999999, &search_count);
        if (search_results == NULL && search_count == 0) {
            printf("✓ find_readings_by_timerange correctly handles non-existent time range\n");
        } else {
            printf("✗ find_readings_by_timerange failed with non-existent time range\n");
            if (search_results) free(search_results);
        }
        
        close_sensor_db(db);
    }
    
    return 0;
}