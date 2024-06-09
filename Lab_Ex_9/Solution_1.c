#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to swap two strings
void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted at index i
void heapify(char *arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && strcmp(arr[left], arr[largest]) > 0)
        largest = left;

    if (right < n && strcmp(arr[right], arr[largest]) > 0)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Main function to perform heap sort
void heapSort(char *arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Heap sort
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Function to print the array
void printArray(char *arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
}

int main() {
    // Test data
    char *A[] = {"#$BiT", "Raj1", "Boy2", "1Kind", "&zebra", "Gate2", "joKe1", "poKer3", "tRicK4", "3Dial", "1RoaD", "QueeN7"};
    int N = sizeof(A) / sizeof(A[0]);

    // Perform heap sort
    heapSort(A, N);

    // Print sorted array
    printArray(A, N);

    return 0;
}