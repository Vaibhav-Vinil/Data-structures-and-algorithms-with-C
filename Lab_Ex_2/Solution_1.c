#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5

struct Student {
    char id[14];
    char name[50];
    char dob[20];
    double cgpa;
};

struct Queue {
    struct Student data[CAPACITY];
    int first;
    int last;
};

void enqueue(struct Queue*, struct Student);
void dequeue(struct Queue*);
void display(struct Queue*);

int main() {
    struct Student student;
    struct Queue queue;
    queue.first = queue.last = -1;
    FILE *file = fopen("studentin.dat","r");
    while (fscanf(file,"%s %s %s %lf", student.id, student.name, student.dob, &student.cgpa) == 4) {
        enqueue(&queue, student);
    }
    fclose(file);

    display(&queue);
    printf("displaying &queue ie of type struct Queue*");

    while(queue.first < (queue.last) % CAPACITY) {
        dequeue(&queue);
    }
}

void enqueue(struct Queue *queue, struct Student student) {
    if ( queue->first == (queue->last + 1) % CAPACITY) {
        printf("Queue Overflow\n");
        return;
    }
    queue->last = (queue->last + 1) % CAPACITY;
    queue->data[queue->last] = student;
}

void dequeue(struct Queue *queue) {
    if (queue->first == -1 && queue->last == -1) {
        printf("Queue Underflow\n");
        return;
    }
    printf("Dequeued Record: ID: %s, Name: %s, DOB: %s, CGPA: %.2f\n" ,queue->data[queue->first].id, queue->data[queue->first].name, queue->data[queue->first].dob, queue->data[queue->first].cgpa);
    queue->first = (queue->first + 1) % CAPACITY;
}

void display(struct Queue *queue) {
    FILE *file = fopen("studentout.dat","w");

    printf("Student Records:\n");
    fprintf(file, "Student Records in FIFO order:\n");
    for (int i = queue->first; i <= queue->last; ++i) {
        printf("ID: %s, Name: %s, DOB: %s, CGPA: %.2f\n", queue->data[i].id, queue->data[i].name, queue->data[i].dob, queue->data[i].cgpa);
        fprintf(file, "ID: %s, Name: %s, DOB: %s, CGPA: %.2f\n", queue->data[i].id, queue->data[i].name, queue->data[i].dob, queue->data[i].cgpa);
    }

    fclose(file);

    printf("Students With CGPA Less Than 9:\n");

    for (int i = queue->first; i <= queue->last; ++i) {
        if (queue->data[i].cgpa < 9.0) 
            printf("%s\n", queue->data[i].name);
    }
}
