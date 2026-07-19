/*
 * CodeAlpha C Programming Internship - Task 3
 * Student Management System
 *
 * Menu-driven program to Add, Delete, Update, Search, and Display
 * student records. Uses structures + file handling for permanent storage.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "students.dat"
#define NAME_LEN 50

typedef struct {
    int roll;
    char name[NAME_LEN];
    float marks;
} Student;

// Function prototypes
void addStudent(void);
void displayStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);
int getMenuChoice(void);
void clearInputBuffer(void);
int rollExists(int roll);

int main() {
    int choice;

    printf("=================================================\n");
    printf("      STUDENT MANAGEMENT SYSTEM (C)\n");
    printf("=================================================\n");

    do {
        printf("\n--------- MENU ---------\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("-------------------------\n");
        printf("Enter your choice (1-6): ");

        choice = getMenuChoice();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting Student Management System. Goodbye!\n"); break;
            default: printf("Invalid choice! Please select between 1 and 6.\n");
        }

    } while (choice != 6);

    return 0;
}

/* Clears leftover characters (like newline) from stdin */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Safely reads an integer menu choice */
int getMenuChoice(void) {
    int choice;
    while (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return choice;
}

/* Checks whether a roll number already exists in the file */
int rollExists(int roll) {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) return 0;

    Student s;
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

/* Adds a new student record to the file */
void addStudent(void) {
    Student s;
    FILE *fp = fopen(FILENAME, "ab");

    if (fp == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    printf("\n--- Add Student ---\n");
    printf("Enter Roll Number: ");
    while (scanf("%d", &s.roll) != 1) {
        printf("Invalid input. Enter Roll Number: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    if (rollExists(s.roll)) {
        printf("Error: A student with roll number %d already exists.\n", s.roll);
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    fgets(s.name, NAME_LEN, stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // remove trailing newline

    printf("Enter Marks: ");
    while (scanf("%f", &s.marks) != 1) {
        printf("Invalid input. Enter Marks: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("Student record added successfully!\n");
}

/* Displays all student records */
void displayStudents(void) {
    FILE *fp = fopen(FILENAME, "rb");
    Student s;
    int count = 0;

    if (fp == NULL) {
        printf("\nNo records found. The file doesn't exist yet.\n");
        return;
    }

    printf("\n--- All Student Records ---\n");
    printf("%-10s %-30s %-10s\n", "Roll No", "Name", "Marks");
    printf("---------------------------------------------------\n");

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("%-10d %-30s %-10.2f\n", s.roll, s.name, s.marks);
        count++;
    }

    if (count == 0) {
        printf("No student records found.\n");
    }

    fclose(fp);
}

/* Searches for a student by roll number */
void searchStudent(void) {
    FILE *fp = fopen(FILENAME, "rb");
    Student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("\nNo records found. The file doesn't exist yet.\n");
        return;
    }

    printf("\n--- Search Student ---\n");
    printf("Enter Roll Number to search: ");
    while (scanf("%d", &roll) != 1) {
        printf("Invalid input. Enter Roll Number: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("\nStudent Found:\n");
            printf("Roll Number : %d\n", s.roll);
            printf("Name        : %s\n", s.name);
            printf("Marks       : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No student found with roll number %d.\n", roll);
    }

    fclose(fp);
}

/* Updates an existing student's name and/or marks */
void updateStudent(void) {
    FILE *fp = fopen(FILENAME, "rb+");
    Student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("\nNo records found. The file doesn't exist yet.\n");
        return;
    }

    printf("\n--- Update Student ---\n");
    printf("Enter Roll Number to update: ");
    while (scanf("%d", &roll) != 1) {
        printf("Invalid input. Enter Roll Number: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            found = 1;

            printf("Current Name : %s\n", s.name);
            printf("Enter New Name: ");
            fgets(s.name, NAME_LEN, stdin);
            s.name[strcspn(s.name, "\n")] = '\0';

            printf("Current Marks: %.2f\n", s.marks);
            printf("Enter New Marks: ");
            while (scanf("%f", &s.marks) != 1) {
                printf("Invalid input. Enter Marks: ");
                clearInputBuffer();
            }
            clearInputBuffer();

            // Move file pointer back one record and rewrite it
            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);

            printf("Student record updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("No student found with roll number %d.\n", roll);
    }

    fclose(fp);
}

/* Deletes a student record by roll number */
void deleteStudent(void) {
    FILE *fp = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    Student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("\nNo records found. The file doesn't exist yet.\n");
        if (temp) fclose(temp);
        return;
    }

    if (temp == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(fp);
        return;
    }

    printf("\n--- Delete Student ---\n");
    printf("Enter Roll Number to delete: ");
    while (scanf("%d", &roll) != 1) {
        printf("Invalid input. Enter Roll Number: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            found = 1;
            continue; // skip writing this record (i.e., delete it)
        }
        fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found) {
        printf("Student record deleted successfully!\n");
    } else {
        printf("No student found with roll number %d.\n", roll);
    }
}
