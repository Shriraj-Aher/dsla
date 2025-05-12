// bfs and dfs using list

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct node {
    int vertex;
    struct node* next;
};

struct node* A[MAX];

int queue[MAX], front = -1, rear = -1;

void Enque(int x) {
    if (rear == MAX - 1) return;
    if (front == -1 && rear == -1) front = rear = 0;
    else rear++;
    queue[rear] = x;
}

int Deque() {
    if (front == -1 && rear == -1) return -1;
    int val = queue[front];
    if (front == rear) front = rear = -1;
    else front++;
    return val;
}

int EmptyQ() {
    return front == -1;
}

int stack[MAX], top = -1;

void push(int x) {
    if (top == MAX - 1) return;
    stack[++top] = x;
}

int pop() {
    if (top == -1) return -1;
    return stack[top--];
}

int emptyst() {
    return top == -1;
}

void init(struct node* A[], int n) {
    for (int i = 0; i < n; i++)
        A[i] = NULL;
}

void addEdge(int v1, int v2) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->vertex = v2;
    newNode->next = A[v1];
    A[v1] = newNode;

    newNode = (struct node*)malloc(sizeof(struct node));
    newNode->vertex = v1;
    newNode->next = A[v2];
    A[v2] = newNode;
}

void create(struct node* A[], int edges) {
    int v1, v2;
    for (int i = 0; i < edges; i++) {
        printf("Enter edge (v1 v2): ");
        scanf("%d%d", &v1, &v2);
        addEdge(v1, v2);
    }
}

void BFS(struct node* A[], int v) {
    int visited[MAX] = {0}, st, n;
    struct node* p;

    printf("Enter the start vertex for BFS: ");
    scanf("%d", &st);
    Enque(st);
    visited[st] = 1;

    printf("BFS traversal: ");
    while (!EmptyQ()) {
        n = Deque();
        printf("%d ", n);
        p = A[n];
        while (p != NULL) {
            if (!visited[p->vertex]) {
                Enque(p->vertex);
                visited[p->vertex] = 1;
            }
            p = p->next;
        }
    }
    printf("\n");
}

void DFS(struct node* A[], int v) {
    int visited[MAX] = {0}, st;
    struct node* p;

    printf("Enter the start vertex for DFS: ");
    scanf("%d", &st);
    push(st);
    visited[st] = 1;

    printf("DFS traversal: ");
    printf("%d ", st);

    while (!emptyst()) {
        int found = 0;
        p = A[stack[top]];
        while (p != NULL) {
            if (!visited[p->vertex]) {
                push(p->vertex);
                visited[p->vertex] = 1;
                printf("%d ", p->vertex);
                found = 1;
                break;
            }
            p = p->next;
        }
        if (!found)
            pop();
    }
    printf("\n");
}

int main() {
    int n, e;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &e);

    init(A, n);
    create(A, e);

    BFS(A, n);
    DFS(A, n);

    return 0;
}
