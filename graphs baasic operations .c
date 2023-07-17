//graphs operations
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Function to read the graph from the input file
void readGraph(int graph[MAX_VERTICES][MAX_VERTICES], int* N, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d", N);

    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *N; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);
}

// Function to display the adjacency matrix representation of the graph
void displayGraph(int graph[MAX_VERTICES][MAX_VERTICES], int N) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Function to calculate the degree of each vertex
void calculateDegrees(int graph[MAX_VERTICES][MAX_VERTICES], int N, int degrees[MAX_VERTICES]) {
    for (int i = 0; i < N; i++) {
        degrees[i] = 0;
        for (int j = 0; j < N; j++) {
            if (graph[i][j] == 1) {
                degrees[i]++;
            }
        }
    }
}

// Function to write the degrees to the output file
void writeDegreesToFile(int degrees[MAX_VERTICES], int N, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    fprintf(file, "Degrees:\n");
    for (int i = 0; i < N; i++) {
        fprintf(file, "Vertex %d: %d\n", i + 1, degrees[i]);
    }

    fclose(file);
}

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int degrees[MAX_VERTICES];
    int N;

    readGraph(graph, &N, "input.txt");
    displayGraph(graph, N);
    calculateDegrees(graph, N, degrees);
    writeDegreesToFile(degrees, N, "output.txt");

    return 0;
}
