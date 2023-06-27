#include <stdio.h>
#include <stdlib.h>

// Structure for queue node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Structure for queue
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create a new queue node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue an element
void enqueue(Queue* queue, int data) {
    Node* newNode = createNode(data);
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("%d enqueued to the queue.\n", data);
}

// Function to dequeue an element
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        exit(1);
    }
    Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    free(temp);
    return data;
}

// Function to display the queue
void displayQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n\n");
        printf("Enter the queue values in file input.txt and save it.\n");
        return;
    }
    Node* temp = queue->front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    // Open the input file
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    Queue* queue = createQueue();

    int value;
    while (fscanf(file, "%d", &value) == 1)
        {
        enqueue(queue, value);
    }

    fclose(file);

    displayQueue(queue);

    // Perform queue operations
    while (!isEmpty(queue)) {
        int data = dequeue(queue);
        printf("%d dequeued from the queue.\n", data);
    }

    return 0;
}
