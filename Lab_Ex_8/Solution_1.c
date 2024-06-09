#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
char name[20];
char ipaddress[20];
};

struct list {
struct node node;
struct list *next;
};

struct list *compression_map[17];

int find_hashcode(char string1[20]) {
int sum = 0;
for (int i = 0; string1[i] != '\0'; i++) {
int c = string1[i];
sum += (c * 33); // Assuming power function is not available
}
return sum;
}

void insert(char string1[20], char string2[20]) {
int h_of_x = find_hashcode(string1) % 17;

if (compression_map[h_of_x] == NULL) {
struct list *start = (struct list *)malloc(sizeof(struct list));
strcpy(start->node.name, string1);
strcpy(start->node.ipaddress, string2);
start->next = NULL;
compression_map[h_of_x] = start;
} else {
struct list *temp = (struct list *)malloc(sizeof(struct list));
strcpy(temp->node.name, string1);
strcpy(temp->node.ipaddress, string2);
temp->next = NULL;
struct list *p = compression_map[h_of_x];
while (p->next != NULL) {
p = p->next;
}
p->next = temp;
}
}

struct list *find(char string1[20]) {
int h_of_x = find_hashcode(string1) % 17;
struct list *start = compression_map[h_of_x];
struct list *p = start;
while (p != NULL) {
if (strcmp(p->node.name, string1) == 0) {
printf("Element found at address %p\n", (void *)p);
return p;
}
p = p->next;
}
printf("Element DOES NOT EXIST\n");
return NULL;
}

void display() {
for (int i = 0; i < 17; i++) {
struct list *p = compression_map[i];
if (p == NULL) {
continue;
}
printf("Hash value %d:\n", i);
while (p != NULL) {
printf("Name: %s, IP: %s\n", p->node.name, p->node.ipaddress);
p = p->next;
}
}
}

int main() {
int choice;
char string1[20];
char string2[20];

while (1) {
printf("\n1. Insert value\n");
printf("2. Find value\n");
printf("3. Display\n");
printf("4. Exit\n");
printf("Enter Your choice: ");
scanf("%d", &choice);

switch (choice) {
case 1:
printf("Enter domain: ");
scanf("%s", string1);
printf("Enter IP address: ");
scanf("%s", string2);
insert(string1, string2);
break;
case 2:
printf("Enter domain: ");
scanf("%s", string1);
find(string1);
break;
case 3:
display();
break;
case 4:
exit(0);
default:
printf("Invalid choice!\n");
}
}

return 0;
}
