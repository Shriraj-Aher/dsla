// dikshitras algo using matrix

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define MAX 100

int minDistance(int dist[], int visited[], int V) {
    int min = INT_MAX, index = -1;
    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] < min)
            min = dist[v], index = v;
    return index;
}

void dijkstra(int graph[MAX][MAX], int V, int src) {
    int dist[MAX], visited[MAX];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, visited[i] = 0;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        if (u == -1) break; 
        visited[u] = 1;

        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
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
    int graph[MAX][MAX] = {0};

    printf("Enter edges as: src dest weight\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
    }

    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);

    dijkstra(graph, V, source);
    return 0;
}

