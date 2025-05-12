#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

struct Node {
    int dest;
    int weight;
    struct Node* next;
};

struct Node* adjList[MAX];

void addEdge(int u, int v, int w) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = v;
    newNode->weight = w;
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

int minDistance(int dist[], int visited[], int V) {
    int min = INT_MAX, index = -1;
    for (int i = 0; i < V; i++)
        if (!visited[i] && dist[i] < min)
            min = dist[i], index = i;
    return index;
}

void dijkstra(int V, int src) {
    int dist[MAX], visited[MAX];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        if (u == -1) break;
        visited[u] = 1;

        struct Node* temp = adjList[u];
        while (temp != NULL) {
            int v = temp->dest, w = temp->weight;
            if (!visited[v] && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
            temp = temp->next;
        }
    }

    printf("Vertex\tDistance from Source %d\n", src);
    for (int i = 0; i < V; i++)
        printf("%d\t\t%d\n", i, dist[i]);
}

int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < V; i++)
        adjList[i] = NULL;

    printf("Enter edges as: src dest weight\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        
    }

    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);

    dijkstra(V, source);

    return 0;
}
