#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Student {
    char id[14];
    char name[50];
    int year;
    double cgpa;
} STUDENT;

void merge(STUDENT *arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    STUDENT *L = (STUDENT*)malloc(n1 * sizeof(STUDENT));
    STUDENT *R = (STUDENT*)malloc(n2 * sizeof(STUDENT));
    
    for (int i = 0; i < n1; i++) 
        L[i] = arr[left + i];
    
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (strcmp(L[i].name, R[j].name) <= 0)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    
    while (i < n1)
        arr[k++] = L[i++];
    
    while (j < n2)
        arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void mergeSort(STUDENT *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

int main() {
    FILE *file = fopen("studentin.dat", "r");
    if (file == NULL) {
        printf("Error opening file");
        return 0;
    }
    
    int size = 10; // Initial size of the array
    int index = 0;
    STUDENT *arr = (STUDENT*)malloc(size * sizeof(STUDENT)); // Allocate memory
    
    if (arr == NULL) {
        printf("Memory allocation failed");
        return 0;
    }
    
    STUDENT student;
    while (fscanf(file, "%s %s %d %lf", student.id, student.name, &student.year, &student.cgpa) == 4) {
        if (index >= size) { // Check if more memory is needed
            size *= 2; // Double the size
            arr = (STUDENT*)realloc(arr, size * sizeof(STUDENT)); // Reallocate memory
            
            if (arr == NULL) {
                printf("Memory allocation failed");
                return 0;
            }
        }
        arr[index++] = student;
    }
    fclose(file);
    
    clock_t start = clock();
    mergeSort(arr, 0, index - 1);
    clock_t end = clock();
    
    printf("Sort Time: %.9lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    for (int i = 0; i < index; i++) {
        printf("%d. ID: %s   NAME: %s   Year: %d   CGPA: %.2f\n", i + 1, arr[i].id, arr[i].name, arr[i].year, arr[i].cgpa);
    }
    
    free(arr);
    return 0;
}
