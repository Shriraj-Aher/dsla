// bfs and dfs traversal using adjacency matrix

#include<stdio.h>
#define N 25

int queue[N];
int front = -1;
int rear = -1;

int stack[N];
int top = -1;

void enque(int x){
    if(rear == N-1)
        return;
    else if(front == -1 && rear == -1){
        front = rear = 0;
        queue[rear] = x;
    }
    else{
        rear++;
        queue[rear] = x;
    }
}

int deque(){
    if(front == -1 && rear == -1)
        return -2;
    else if(front == rear){
        int a = queue[front];
        front = rear = -1;
        return a;
    }
    else{
        int a = queue[front];
        front++;
        return a;
    }
}

int emptyque(){
    if(front == -1 && rear == -1){
        return 1;}
        else{
            return 0;
        }
    }

void push(int x){
    if(top == N-1){
        return;
    }
    top++;
    stack[top] = x;
}

int pop(){
    if(top == -1){
        return -1;
    }
    int x = stack[top];
    top--;
    return x;
}

int emptyst(){
    return top == -1;
}

void BSF(int v, int adjmatrix[v][v]){
    int st, visited[v], i, n;
    for(i=0; i<v; i++){
        visited[i] = 0;
    }
    printf("enter the start vertex for BFS: ");
    scanf("%d", &st);
    enque(st);
    visited[st] = 1;

    printf("BFS traversal: ");
    while (!emptyque())
    {
        n = deque();
        printf("%d ", n);
        for(i=0; i<v; i++){
            if(adjmatrix[n][i] == 1 && visited[i] == 0){
                enque(i);
                visited[i] = 1;
        } 
    } 
}
printf("\n");
}

void DSF(int v, int adjmatrix[v][v]){
    int st;
    int visited[v];

    for(int i = 0; i < v; i++){
        visited[i] = 0;
    }

    printf("enter the start vertex for dfs: ");
    scanf("%d", &st);

    push(st);
    visited[st] = 1;

    printf("DFS traversal: ");

    while(!emptyst()){
        int n = pop();
        printf("%d ", n);

        for(int i=v-1; i>=0; i--){
            if(adjmatrix[n][i] == 1 && visited[i] == 0){
                push(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

int main(){
    int v;
    printf("enter the number of vertices of the graph: ");
    scanf("%d", &v);

    int adjmatrix[v][v];

    printf("enter the elements of the adjacency matrix: ");
    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            scanf("%d", &adjmatrix[i][j]);
        }
    }
    
    BSF(v, adjmatrix);
    DSF(v, adjmatrix);
    return 0;
}
