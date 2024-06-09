#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 14

// Structure to represent a student record
struct Student {
    char name[MAX_NAME_LENGTH];
    char id[MAX_ID_LENGTH];
    double cgpa;
    struct Student *next;
};

// Function prototypes
struct Student* insert(struct Student *head, int position, char name[], char id[], double cgpa);
int find(struct Student *head, char name[]);
struct Student* delete(struct Student *head, char name[]);
struct Student* get(struct Student *head, int position);
void display(struct Student *head);
int size(struct Student *head);
int isEmpty(struct Student *head);

int main() {
    struct Student *head = NULL;

    while (1) {
        printf("\nLinked List Operations:\n");
        printf("1. Add a student record\n");
        printf("2. Find a student record by name\n");
        printf("3. Delete a student record\n");
        printf("4. Display the list\n");
        printf("5. Check if the list is empty\n");
        printf("6. Get the size of the list\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[MAX_NAME_LENGTH];
                char id[MAX_ID_LENGTH];
                double cgpa;
                printf("Enter student name: ");
                scanf("%s", name);
                printf("Enter ID: ");
                scanf("%s", id);
                printf("Enter CGPA: ");
                scanf("%lf", &cgpa);
                head = insert(head, size(head) + 1, name, id, cgpa);
                break;
            }
            case 2: {
                char name[MAX_NAME_LENGTH];
                printf("Enter the name to search: ");
                scanf("%s", name);
                int position = find(head, name);
                if (position != -1) {
                    printf("Student %s found at position %d\n", name, position);
                } else {
                    printf("Student %s not found\n", name);
                }
                break;
            }
            case 3: {
                char name[MAX_NAME_LENGTH];
                printf("Enter the name to delete: ");
                scanf("%s", name);
                head = delete(head, name);
                if (head != NULL) {
                    printf("Student %s deleted successfully\n", name);
                } else {
                    printf("Student %s not found in the list\n", name);
                }
                break;
            }
            case 4:
                display(head);
                break;
            case 5:
                if (isEmpty(head)) {
                    printf("The list is empty\n");
                } else {
                    printf("The list is not empty\n");
                }
                break;
            case 6:
                printf("The size of the list is: %d\n", size(head));
                break;
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

// Function to insert a student record after a specified position
struct Student* insert(struct Student *head, int position, char name[], char id[], double cgpa) {
    struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newStudent->name, name);
    strcpy(newStudent->id, id);
    newStudent->cgpa = cgpa;
    newStudent->next = NULL;

    if (position == 1 || head == NULL) {
        newStudent->next = head;
        head = newStudent;
    } else {
        struct Student *temp = head;
        for (int i = 1; i < position - 1 && temp->next != NULL; ++i) {
            temp = temp->next;
        }
        newStudent->next = temp->next;
        temp->next = newStudent;
    }
    return head;
}

// Function to find a student record by name
int find(struct Student *head, char name[]) {
    int position = 1;
    struct Student *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return position;
        }
        temp = temp->next;
        position++;
    }
    return -1;
}

// Function to delete a student record
struct Student* delete(struct Student *head, char name[]) {
    struct Student *temp = head;
    struct Student *prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return head;
    }

    if (prev != NULL) {
        prev->next = temp->next;
    } else {
        head = temp->next;
    }

    free(temp);
    return head;
}

// Function to display all student records in the list
void display(struct Student *head) {
    printf("Student Records:\n");
    int position = 1;
    while (head != NULL) {
        printf("%d. Name: %s, ID: %s, CGPA: %.2lf\n", position, head->name, head->id, head->cgpa);
        head = head->next;
        position++;
    }
}

// Function to return the total number of students in the list
int size(struct Student *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Function to check if the list is empty
int isEmpty(struct Student *head) {
    return head == NULL;
}
