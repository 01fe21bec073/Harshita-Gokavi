#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
    } else {
        if (data < root->data) {
            root->left = insertNode(root->left, data);
        } else if (data > root->data) {
            root->right = insertNode(root->right, data);
        } else {
            printf("Duplicate keys not allowed in BST!\n");
        }
    }
    return root;
}

// Function to store the BST in a file
void storeBST(struct Node* root, FILE* file) {
    if (root == NULL) {
        return;
    }
    // Store the node data in the file
    fprintf(file, "%d ", root->data);
    // Recursively store left and right subtrees
    storeBST(root->left, file);
    storeBST(root->right, file);
}

// Function to load a BST from a file
struct Node* loadBST(FILE* file) {
    int data;
    struct Node* root = NULL;
    while (fscanf(file, "%d", &data) == 1) {
        root = insertNode(root, data);
    }
    return root;
}

// Function to print the BST in inorder traversal
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, data;

    while (1) {
        printf("1. Insert a node\n");
        printf("2. Save the BST to a file\n");
        printf("3. Load the BST from a file\n");
        printf("4. Print the BST (inorder traversal)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                printf("Node inserted successfully.\n");
                break;
            case 2:
                {
                    FILE* file = fopen("bst.txt", "w");
                    if (file == NULL) {
                        printf("Failed to open the file for writing.\n");
                        exit(1);
                    }
                    storeBST(root, file);
                    fclose(file);
                    printf("BST saved to file successfully.\n");
                }
                break;
            case 3:
                {
                    FILE* file = fopen("bst.txt", "r");
                    if (file == NULL) {
                        printf("Failed to open the file for reading.\n");
                        exit(1);
                    }
                    root = loadBST(file);
                    fclose(file);
                    printf("BST loaded from file successfully.\n");
                }
                break;
            case 4:
                printf("BST (inorder traversal): ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
        printf("\n");
    }

    return 0;
}
