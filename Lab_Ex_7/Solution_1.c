#include <stdio.h>
#include <stdlib.h>

typedef struct node_T {
  struct node_T *data;
  struct node_T *next;
} node_T;

// Define the structure for the stack itself
typedef struct stack_T {
  node_T *top;
} stack_T;





// Function to initialize an empty stack (allocate memory)
stack_T* init_stack(void) {
  stack_T* stack = (stack_T *)calloc(1, sizeof(stack_T));
   stack->top = NULL;
  return stack;
}



// Function to push an element onto the stack
void push(stack_T *stack, void *element) {
  node_T *node = (node_T *)calloc(1, sizeof(node_T));
  if (node == NULL) {
    // Handle memory allocation failure (optional)
    return;
  }
  node->data = element;
  node->next = stack->top;
  stack->top = node;
}
// Function to check if the stack is empty
int stack_is_empty(stack_T *stack) {
  return (stack->top == NULL);
}

// Function to pop an element from the stack
void* pop(stack_T *stack) {
  if (stack_is_empty(stack)) {
    // Handle underflow (optional: print message, return NULL)
    return NULL;
  }
  node_T *temp = stack->top;
  void *element = temp->data;
  stack->top = stack->top->next;
  free(temp);
  return element;
}



// Function to display the contents of the stack 
void display_stack(stack_T *stack) {
  node_T *temp = stack->top;
  printf("Stack: ");
  while (temp != NULL) {
    printf("%d ", *(int *)(temp->data));
    temp = temp->next;
  }
  printf("\n");
}

// Function to test the stack functionalities
void stack_test(stack_T *stack) {
  int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (int i = 0; i < 10; i++) {
    push(stack, &arr[i]);
  }

  display_stack(stack);
  printf(stack_is_empty(stack) ? "Empty\n" : "Not Empty\n");

  printf("Popping the Stack\n");
  for (int i = 0; i < 10; i++) {
    int *p = pop(stack);
    if (p != NULL) { // Check for underflow handling
      printf("Popped %d\n", *p);
    }
  }

  printf(stack_is_empty(stack) ? "Empty\n" : "Not Empty\n");
}

int main() {
  stack_T *stack = init_stack();
  if (stack == NULL) {
    // Handle memory allocation failure (optional: print message, exit)
    return 1;
  }
  stack_test(stack);
  free(stack);


  return 0;
}