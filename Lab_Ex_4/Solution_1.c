#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int arr[], int size, int target) {
for (int i = 0; i < size; i++) {
if (arr[i] == target) {
return i;
}
}
return -1;
}

int binarySearch(int arr[], int low, int high, int x) {
if (high >= low) {
int mid = low + (high - low) / 2;

if (arr[mid] == x)
    return mid;
if (arr[mid] > x)
    return binarySearch(arr, low, mid - 1, x);
return binarySearch(arr, mid + 1, high, x);


}
return -1;
}

int compareIntegers(const void *a, const void *b) {
return (*(int *)a - *(int *)b);
}

int main() {
FILE *testcasefile;
FILE *searchfile;
int index;

testcasefile = fopen("./testCaseSize.txt", "r");
searchfile = fopen("./searchTestCase.txt", "r");

if (testcasefile == NULL || searchfile == NULL) {
printf("Error opening files.\n");
return 1;
}

printf("Enter the index of the number: ");
scanf("%d", &index);

int numbertosearch;
for (int i = 0; i < index + 1; i++) {
fscanf(testcasefile, "%d", &numbertosearch);
if (i == index) {
break;
}
}

int searcharray[983040];
for (int i = 0; i < 983040; i++) {
fscanf(searchfile, "%d", &searcharray[i]);
}

FILE *bsearchresults;
FILE *lsearchresults;

clock_t start_time, end_time;
double time_taken;

bsearchresults = fopen("./binarySearchResults.txt", "a");
lsearchresults = fopen("./linearSearchResults.txt", "a");

start_time = clock();
int linearIndex = linearSearch(searcharray, 983040, numbertosearch);
end_time = clock();

if (linearIndex != -1) {
fprintf(lsearchresults, "%d %d %f\n", numbertosearch, linearIndex, (((double)(end_time - start_time)) / CLOCKS_PER_SEC));
} else {

}

qsort(searcharray, 983040, sizeof(int), compareIntegers);

start_time = clock();
int binaryIndex = binarySearch(searcharray, 0, 983039, numbertosearch);
end_time = clock();

if (binaryIndex != -1) {
fprintf(bsearchresults, "%d %d %f\n", numbertosearch, binaryIndex, (((double)(end_time - start_time)) / CLOCKS_PER_SEC));
} else {

}

fclose(testcasefile);
fclose(searchfile);
fclose(bsearchresults);
fclose(lsearchresults);

return 0;
}
