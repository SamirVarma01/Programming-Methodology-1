#ifndef SENSOR_DB_H
#define SENSOR_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a sensor reading
typedef struct {
    int id;                      // Sensor ID
    char type[20];               // Sensor type (e.g., "Temperature", "Humidity")
    float value;                 // Sensor value
    unsigned long timestamp;     // Unix timestamp
} SensorData;

// Structure to represent a database of sensor readings
typedef struct {
    FILE* file;                 // File handle
    unsigned int record_count;  // Number of records in the file
} SensorDB;

// Function prototypes
SensorDB* open_sensor_db(const char* filename, const char* mode);
int close_sensor_db(SensorDB* db);

// Basic file operations
int write_sensor_data(const char* filename, SensorData* sensors, int count);
SensorData* read_sensor_data(const char* filename, int* count);
int read_sensor_at(const char* filename, int index, SensorData* record);

// Additional functions needed for the checkpoints
int add_sensor_reading(SensorDB* db, const SensorData* reading);
int add_sensor_readings(SensorDB* db, const SensorData* readings, int count);
int get_sensor_reading(SensorDB* db, unsigned int index, SensorData* reading);
int get_record_count(SensorDB* db);
SensorData* find_readings_by_sensor(SensorDB* db, int sensor_id, int* count_out);
SensorData* find_readings_by_timerange(SensorDB* db,
                                       unsigned long start_time,
                                       unsigned long end_time,
                                       int* count_out);
int update_sensor_reading(SensorDB* db, unsigned int index, const SensorData* reading);
int delete_sensor_reading(SensorDB* db, unsigned int index);
int calculate_sensor_stats(SensorDB* db, int sensor_id,
                          float* min_value, float* max_value, float* avg_value);

#endif // SENSOR_DB_H