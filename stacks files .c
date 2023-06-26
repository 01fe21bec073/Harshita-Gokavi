#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure for stack
struct Stack {
    int data[MAX_SIZE];
    int top;
};

// Function to initialize the stack
void initialize(struct Stack* stack) {
    stack->top = -1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return (stack->top == -1);
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return (stack->top == MAX_SIZE - 1);
}

// Function to push an element onto the stack
void push(struct Stack* stack, int element) {
    if (isFull(stack)) {
        printf("Stack is full. Cannot push element.\n");
        return;
    }

    stack->data[++stack->top] = element;
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop element.\n");
        return -1;
    }

    return stack->data[stack->top--];
}

// Function to display the elements of the stack
void displayStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack elements:\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->data[i]);
    }
}

int main() {
    struct Stack stack;
    initialize(&stack);

    int choice, element;

    FILE* file = fopen("stacks.txt", "a+");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    while (1) {
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display Stack\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to push: ");
                scanf("%d", &element);
                push(&stack, element);
                fprintf(file, "Pushed: %d\n", element);
                break;
            case 2:
                element = pop(&stack);
                if (element != -1) {
                    printf("Popped: %d\n", element);
                    fprintf(file, "Popped: %d\n", element);
                }
                break;
            case 3:
                displayStack(&stack);
                break;
            case 4:
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
    }

    return 0;
}
