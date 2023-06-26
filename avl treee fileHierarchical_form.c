//Hierarchical display
#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
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
    newNode->height = 1;
    return newNode;
}

// Function to calculate the height of a node
int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to update the height of a node
void updateHeight(struct Node* node) {
    if (node == NULL)
        return;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Function to get the balance factor of a node
int getBalanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to perform right rotation
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform left rotation
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to insert a node into the AVL tree
struct Node* insertNode(struct Node* node, int data) {
    // Perform the normal BST insertion
    if (node == NULL)
        return createNode(data);
    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else // Duplicate keys not allowed in AVL tree
        return node;

    // Update the height of the ancestor node
    updateHeight(node);

    // Perform AVL balancing if required
    int balanceFactor = getBalanceFactor(node);

    // Left Left Case
    if (balanceFactor > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balanceFactor < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balanceFactor > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balanceFactor < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to perform a hierarchical traversal (preorder)
void hierarchicalTraversal(struct Node* root, int level, FILE* outputFile) {
    if (root != NULL) {
        fprintf(outputFile, "%*s", level * 4, ""); // Indentation based on the level
        fprintf(outputFile, "%d\n", root->data);
        hierarchicalTraversal(root->left, level + 1, outputFile); // Recursive call for left subtree
        hierarchicalTraversal(root->right, level + 1, outputFile); // Recursive call for right subtree
    }
}

int main() {
    struct Node* root = NULL;
    int numNodes, data;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter %d values to insert:\n", numNodes);
    for (int i = 0; i < numNodes; i++) {
        scanf("%d", &data);
        root = insertNode(root, data);
    }

    // Open the output file for writing
    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Failed to open the output file.\n");
        return 1;
    }

    printf("AVL tree created successfully.\n");

    // Perform hierarchical traversal and write to the output file
    fprintf(outputFile, "Hierarchical traversal of the AVL tree:\n");
    hierarchicalTraversal(root, 0, outputFile);

    // Close the output file
    fclose(outputFile);

    return 0;
}
