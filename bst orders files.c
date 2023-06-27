#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
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

// Function to insert a node into the binary tree
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);

    return root;
}

// Function to perform the preorder traversal and store the nodes in a file
void preorderTraversal(struct Node* root, FILE* fp) {
    if (root == NULL)
        return;

    fprintf(fp, "%d ", root->data);
    preorderTraversal(root->left, fp);
    preorderTraversal(root->right, fp);
}

// Function to perform the inorder traversal and store the nodes in a file
void inorderTraversal(struct Node* root, FILE* fp) {
    if (root == NULL)
        return;

    inorderTraversal(root->left, fp);
    fprintf(fp, "%d ", root->data);
    inorderTraversal(root->right, fp);
}

// Function to perform the postorder traversal and store the nodes in a file
void postorderTraversal(struct Node* root, FILE* fp) {
    if (root == NULL)
        return;

    postorderTraversal(root->left, fp);
    postorderTraversal(root->right, fp);
    fprintf(fp, "%d ", root->data);
}

// Function to print the binary tree in hierarchical tree form
void printTree(struct Node* root, int space) {
    if (root == NULL)
        return;

    space += 4;

    printTree(root->right, space);

    printf("\n");
    for (int i = 4; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    printTree(root->left, space);
}

int main() {
    struct Node* root = NULL;
    int n, data;

    printf("Enter the number of elements to insert in the binary tree: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        root = insertNode(root, data);
    }

    // Open the file in write mode
    FILE* fp = fopen("tree_traversals.txt", "w");
    if (fp == NULL) {
        printf("Failed to create the file!\n");
        exit(1);
    }

    // Perform preorder traversal and store the nodes in the file
    fprintf(fp, "Preorder traversal: ");
    preorderTraversal(root, fp);
    fprintf(fp, "\n");

    // Perform inorder traversal and store the nodes in the file
    fprintf(fp, "Inorder traversal: ");
    inorderTraversal(root, fp);
    fprintf(fp, "\n");

    // Perform postorder traversal and store the nodes in the file
    fprintf(fp, "Postorder traversal: ");
    postorderTraversal(root, fp);
    fprintf(fp, "\n");

    // Close the file
    fclose(fp);

    printf("Binary tree traversals are stored in the file 'tree_traversals.txt'.\n");

    // Display the tree in hierarchical form
    printf("\nBinary Tree (Hierarchical Form):\n");
    printTree(root, 0);

    return 0;
}
