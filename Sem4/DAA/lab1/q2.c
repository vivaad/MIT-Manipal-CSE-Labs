#include <stdio.h>
#include <stdlib.h>

// Define the maximum number of vertices in the graph
#define MAX_VERTICES 10

// Function to display the adjacency matrix
void displayAdjMatrix(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int i, j;
    printf("Adjacency Matrix:\n");
    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Define a structure for adjacency list nodes
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// Define a structure for an adjacency list
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// Define a structure for the graph
typedef struct Graph {
    int vertices;
    AdjList* array;
} Graph;

// Function to create a new adjacency list node
AdjListNode* createAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with the given number of vertices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;

    // Create an array of adjacency lists
    graph->array = (AdjList*)malloc(vertices * sizeof(AdjList));

    // Initialize each adjacency list as empty
    for (int i = 0; i < vertices; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    AdjListNode* newNode = createAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since the graph is undirected, add an edge from dest to src
    newNode = createAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to display the adjacency list
void displayAdjList(Graph* graph) {
    int v;
    printf("Adjacency List:\n");
    for (v = 0; v < graph->vertices; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("Vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int main() {
    int vertices = 5;

    // Adjacency Matrix
    int adjMatrix[MAX_VERTICES][MAX_VERTICES] = {0};
    adjMatrix[0][1] = 1;
    adjMatrix[0][4] = 1;
    adjMatrix[1][2] = 1;
    adjMatrix[1][3] = 1;
    adjMatrix[1][4] = 1;
    adjMatrix[2][3] = 1;
    adjMatrix[3][4] = 1;

    displayAdjMatrix(adjMatrix, vertices);

    // Adjacency List
    Graph* graph = createGraph(vertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    displayAdjList(graph);

    return 0;
}

