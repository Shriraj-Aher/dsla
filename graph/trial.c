#include<stdio.h>
#include<stdlib.h>

void BFS(int v, int adj[v][v]){
    int visited[v], st;
    for(int i=0; i<v; v++){
        visited[i] = 0;
    }

    printf("enter the start vertex: ");
    scanf("%d", &st);
    enque(st);
    visited[st] = 1;

    while(!emptyque()){
        int x = deque();
        printf("%d ", x);

        for(int j=0; j<v; j++){
            if(adj[n][j] == 1 && visited[j] == 0){
                enque(i);
                visited[i] =1;
            }
        }
    }
    printf("\n");
}

void DFS(int v, int adj[][]){
    int visited[v];
    int st;
    for(int i=0; i<v; i++){
        visited[i] =0;
    }

    printf("enter the start vertex: ");
    scanf("%d", &st);
    push(st);
    visited[st] = 1;

    while(!emptystack()){
        int n = pop();
        printf("%d", n);
        for(int j=0; j<v; j++){
            if(adj[n][j] == 1 && visited[i] == 0){
                push(j);
                visited[j] = 1;
            }
        }
    }
}