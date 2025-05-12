// krushkal using list 

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    int u, v, weight;
} Edge;

Node* adjList[MAX];
Edge edgeList[MAX];
int parent[MAX];
int n, e, edgeCount = 0;

Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int u, int v, int weight) {
    Node* node = createNode(v, weight);
    node->next = adjList[u];
    adjList[u] = node;

    node = createNode(u, weight); // for undirected graph
    node->next = adjList[v];
    adjList[v] = node;

    edgeList[edgeCount].u = u;
    edgeList[edgeCount].v = v;
    edgeList[edgeCount].weight = weight;
    edgeCount++;
}

void bubbleSortEdges() {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edgeList[j].weight > edgeList[j + 1].weight) {
                Edge temp = edgeList[j];
                edgeList[j] = edgeList[j + 1];
                edgeList[j + 1] = temp;
            }
        }
    }
}

int find(int i) {
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}

int unionSet(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);
    if (rootU != rootV) {
        parent[rootV] = rootU;
        return 1;
    }
    return 0;
}

void printAdjList() {
    for (int i = 0; i < n; i++) {
        printf("%d: ", i);
        Node* temp = adjList[i];
        while (temp) {
            printf("-> %d (%d) ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int u, v, w, i, mstWeight = 0, count = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    for (i = 0; i < n; i++) {
        adjList[i] = NULL;
        parent[i] = i;
    }

    printf("Enter edges (u v weight):\n");
    for (i = 0; i < e; i++) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    printf("\nAdjacency List:\n");
    printAdjList();

    bubbleSortEdges(); 

    printf("\nEdges in MST:\n");
    for (i = 0; i < edgeCount && count < n - 1; i++) {
        u = edgeList[i].u;
        v = edgeList[i].v;
        w = edgeList[i].weight;

        if (unionSet(u, v)) {
            printf("%d - %d -> %d\n", u, v, w);
            mstWeight += w;
            count++;
        }
    }
    printf("Total weight of MST = %d\n", mstWeight);
    return 0;
}
