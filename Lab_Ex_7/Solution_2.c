#include <stdio.h>
#include <stdlib.h>

typedef struct node_T {
  void *data;
  struct node_T *next;
} node_T;

typedef struct queue_T {
  node_T *front; 
  node_T *rear; 
} queue_T;



// Function to initialize an empty queue (allocate memory)
queue_T* init_queue(void) {
  queue_T *queue = (queue_T *)calloc(1, sizeof(queue_T));
 
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}



void enqueue(queue_T *queue, void *element) {
  node_T *node = (node_T *)calloc(1, sizeof(node_T));
  
  node->data = element;
  node->next = NULL;

  // Handle empty queue case (both front and rear point to the new node)
  if (queue->front == NULL) {
    queue->front = queue->rear = node;
    return;
  }

  // Non-empty queue: add to the rear
  queue->rear->next = node;
  queue->rear = node;
}

// Function to dequeue an element from the queue
void* dequeue(queue_T *queue) {
  if (queue_is_empty(queue)) {
    // Handle underflow (optional: print message, return NULL)
    return NULL;
  }

  node_T *temp = queue->front;
  void *element = temp->data;

  // Update front pointer
  queue->front = queue->front->next;

  // Handle queue becoming empty after dequeue
  if (queue->front == NULL) {
    queue->rear = NULL; // Set both front and rear to NULL for an empty queue
  }

  free(temp);
  return element;
}

// Function to check if the queue is empty
int queue_is_empty(queue_T *queue) {
  return (queue->front == NULL);
}

// Optional function to display the contents of the queue (for debugging)
void display_queue(queue_T *queue) {
  node_T *temp = queue->front;
  printf("Queue: ");
  while (temp != NULL) {
    printf("%d ", *(int *)(temp->data));
    temp = temp->next;
  }
  printf("\n");
}

// Function to test the queue functionalities (similar to stack_test)
// You can modify this function to test enqueue and dequeue operations
void queue_test(queue_T *queue) {
  int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (int i = 0; i < 10; i++) {
    enqueue(queue, &arr[i]);
  }

  display_queue(queue);
  printf(queue_is_empty(queue) ? "Empty\n" : "Not Empty\n");

  printf("Dequeuing the Queue\n");
  for (int i = 0; i < 10; i++) {
    int *p = dequeue(queue);
    if (p != NULL) { // Check for underflow handling
      printf("Dequeued %d\n", *p);
    }
  }

  printf(queue_is_empty(queue) ? "Empty\n" : "Not Empty\n");
}

int main() {
  queue_T *queue = init_queue();
  if (queue == NULL) {
    // Handle memory allocation failure (optional)
    return 1;
  }
  queue_test(queue);
  free(queue);

  return 0;
}