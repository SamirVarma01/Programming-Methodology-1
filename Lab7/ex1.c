#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Student structure
typedef struct {
    int id;
    char name[50];
    char major[50];
    float gpa;
} Student;

// Define StudentDB structure
typedef struct {
    Student* students; // Dynamic array of students
    int capacity;      // Maximum capacity
    int count;         // Current number of students
} StudentDB;

// Initialize database
StudentDB* initializeDB(int capacity) {
    if (capacity <= 0 || capacity == NULL) {
        printf("Invalid Capacity");
    }
    StudentDB* db = (StudentDB*)malloc(sizeof(StudentDB));
    if (!db) return NULL; // Memory allocation failure

    db->students = (Student*)malloc(capacity * sizeof(Student));
    if (!db->students) {
        free(db);
        return NULL;
    }

    db->capacity = capacity;
    db->count = 0;
    return db;
}

// Add a student to the database
int addStudent(StudentDB* db, int id, const char* name, const char* major, float gpa) {
    if (db->count >= db->capacity) return 0; // Database full

    Student* newStudent = &db->students[db->count++];
    newStudent->id = id;
    strcpy(newStudent->name, name);
    strcpy(newStudent->major, major);
    newStudent->gpa = gpa;

    return 1; // Success
}

// Find student by ID
Student* findStudentByID(StudentDB* db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == id) {
            return &db->students[i];
        }
    }
    return NULL; // Not found
}

// Remove student by ID
int removeStudent(StudentDB* db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == id) {
            db->students[i] = db->students[db->count - 1]; // Swap with last element
            db->count--;
            return 1; // Success
        }
    }
    return 0; // Student not found
}

// Find students by GPA threshold
Student** findStudentsByGPA(StudentDB* db, float min_gpa, int* count_out) {
    Student** result = (Student**)malloc(db->count * sizeof(Student*));
    int count = 0;
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].gpa >= min_gpa) {
            result[count++] = &db->students[i];
        }
    }
    *count_out = count;
    return result;
}

// Find students by major
Student** findStudentsByMajor(StudentDB* db, const char* major, int* count_out) {
    Student** result = (Student**)malloc(db->count * sizeof(Student*));
    int count = 0;
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->students[i].major, major) == 0) {
            result[count++] = &db->students[i];
        }
    }
    *count_out = count;
    return result;
}

// Sort students by GPA (Descending Order)
void sortStudentsByGPA(StudentDB* db) {
    for (int i = 0; i < db->count - 1; i++) {
        for (int j = i + 1; j < db->count; j++) {
            if (db->students[i].gpa < db->students[j].gpa) {
                Student temp = db->students[i];
                db->students[i] = db->students[j];
                db->students[j] = temp;
            }
        }
    }
}

// Print all student records
void printAllStudents(StudentDB* db) {
    for (int i = 0; i < db->count; i++) {
        printf("ID: %d\nName: %s\nMajor: %s\nGPA: %.2f\n\n",
               db->students[i].id, db->students[i].name, db->students[i].major, db->students[i].gpa);
    }
}

// Free memory allocated for database
void freeStudentDB(StudentDB* db) {
    if (db) {
        free(db->students);
        free(db);
    }
}

int main() {
    StudentDB* db = initializeDB(100);

    addStudent(db, 12345, "John Doe", "Computer Science", 3.75);
    addStudent(db, 67890, "Jane Smith", "Mathematics", 3.95);
    addStudent(db, 11223, "Alice Johnson", "Physics", 3.85);

    printf("All Students:\n");
    printAllStudents(db);

    int count;
    Student** topStudents = findStudentsByGPA(db, 3.8, &count);
    printf("\nStudents with GPA >= 3.8:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d\nName: %s\nMajor: %s\nGPA: %.2f\n\n",
               topStudents[i]->id, topStudents[i]->name, topStudents[i]->major, topStudents[i]->gpa);
    }
    free(topStudents);

    Student** majorStudents = findStudentsByMajor(db, "English", &count);
    printf("\nStudents with Major = English:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d\nName: %s\nMajor: %s\nGPA: %.2f\n\n",
               majorStudents[i]->id, majorStudents[i]->name, majorStudents[i]->major, majorStudents[i]->gpa);
    }
    free(majorStudents);

    printf("\nBefore Removing Student with ID 67890:\n");
    printAllStudents(db);

    removeStudent(db, 67891);
    printf("\nAfter Removing Student with ID 67891:\n");
    printAllStudents(db);

    sortStudentsByGPA(db);
    printf("\nSorted Students by GPA:\n");
    printAllStudents(db);

    freeStudentDB(db);
    return 0;
}
