#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"
#define TEMP_FILE "temp.txt"

// Student structure
typedef struct {
    int roll;
    char name[50];
    int age;
    float gpa;
} Student;

// Function prototypes
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting program...\n"); exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

// Add student
void addStudent() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        perror("File opening failed");
        return;
    }

    Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll); getchar();
    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("Student added successfully!\n");
}

// View all students
void viewStudents() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    Student s;
    printf("\n%-10s %-20s %-5s %-5s\n", "Roll", "Name", "Age", "GPA");
    printf("------------------------------------------------\n");
    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("%-10d %-20s %-5d %-5.2f\n", s.roll, s.name, s.age, s.gpa);
    }

    fclose(fp);
}

// Search student
void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    int roll;
    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll == roll) {
            printf("Record found:\n");
            printf("Roll: %d\nName: %s\nAge: %d\nGPA: %.2f\n", s.roll, s.name, s.age, s.gpa);
            found = 1;
            break;
        }
    }

    if (!found) printf("No student with roll %d found.\n", roll);

    fclose(fp);
}

// Update student
void updateStudent() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    int roll;
    printf("Enter roll number to update: ");
    scanf("%d", &roll); getchar();

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter new name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';
            printf("Enter new age: ");
            scanf("%d", &s.age);
            printf("Enter new GPA: ");
            scanf("%f", &s.gpa);

            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            printf("Record updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) printf("No student with roll %d found.\n", roll);

    fclose(fp);
}

// Delete student
void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    FILE *temp = fopen(TEMP_FILE, "wb");
    if (!temp) {
        perror("Temp file opening failed");
        fclose(fp);
        return;
    }

    int roll;
    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            continue; // skip writing this record
        }
        fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) printf("Record deleted successfully!\n");
    else printf("No student with roll %d found.\n", roll);
}