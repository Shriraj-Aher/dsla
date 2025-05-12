// prims algo using matrix and list 

#include <stdio.h>
#include <stdlib.h>
#define MAX 999

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

int Findvertex(int dist[], int visited[], int v) {
    int min = MAX, index = -1;
    for (int i = 0; i < v; i++) {
        if (visited[i] == 0 && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void DisplayMST(int dist[], int par[], int v) {
    for (int i = 1; i < v; i++) {
        printf("%d - %d => %d\n", par[i], i, dist[i]);
    }
}

void prims_matrix(int v, int G[v][v]) {
    int visited[10] = {0}, par[10], dist[10];
    int i, j, st;

    for (i = 0; i < v; i++) {
        dist[i] = MAX;
        par[i] = -1;
    }

    printf("Enter the start vertex: ");
    scanf("%d", &st);
    dist[st] = 0;

    for (i = 0; i < v - 1; i++) {
        st = Findvertex(dist, visited, v);
        visited[st] = 1;

        for (j = 0; j < v; j++) {
            if (G[st][j] && visited[j] == 0 && G[st][j] < dist[j]) {
                dist[j] = G[st][j];
                par[j] = st;
            }
        }
    }

    DisplayMST(dist, par, v);
}

void prims_list(int v, Node* adjList[]) {
    int visited[10], par[10], dist[10];
    int i, st;

    for (i = 0; i < v; i++) {
        visited[i] = 0;
        dist[i] = MAX;
        par[i] = -1;
    }

    printf("Enter the start vertex: ");
    scanf("%d", &st);
    dist[st] = 0;

    for (i = 0; i < v - 1; i++) {
        st = Findvertex(dist, visited, v);
        visited[st] = 1;

        Node* temp = adjList[st];
        while (temp) {
            int j = temp->vertex;
            int weight = temp->weight;

            if (!visited[j] && weight < dist[j]) {
                dist[j] = weight;
                par[j] = st;
            }
            temp = temp->next;
        }
    }

    DisplayMST(dist, par, v);
}

int main() {
    int v, choice;
    printf("Enter the number of vertices: ");
    scanf("%d", &v);

    printf("Choose representation:\n1. Adjacency Matrix\n2. Adjacency List\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int G[v][v];
        printf("Enter the adjacency matrix:\n");
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                scanf("%d", &G[i][j]);
            }
        }
        prims_matrix(v, G);
    } else if (choice == 2) {
        Node* adjList[v];
        for (int i = 0; i < v; i++) {
            adjList[i] = NULL;
        }

        int edges, u, w, wt;
        printf("Enter the number of edges: ");
        scanf("%d", &edges);

        printf("Enter edges in the format (u v weight):\n");
        for (int i = 0; i < edges; i++) {
            scanf("%d %d %d", &u, &w, &wt);
            Node* node1 = createNode(w, wt);
            node1->next = adjList[u];
            adjList[u] = node1;

            Node* node2 = createNode(u, wt);
            node2->next = adjList[w];
            adjList[w] = node2;
        }

        prims_list(v, adjList);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}

