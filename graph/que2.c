// krushkals algorithm using matrix

#include<stdio.h>
int min = 99;
int ne = 1;
int par[10];
int G[10][10];

int Findpar(int);
int Union(int, int);

int main(){
    int n, i, j, minw = 0;
    int a, b, u, v;
    printf("enter the no. of vertices: ");
    scanf("%d", &n);
    
    for(i = 0; i < n; i++)
    par[i] = i;

    printf("enter the adjacency matrix: ");
    for(i = 0; i < n; i++) {
        printf("\nEnter row %d (space-separated): ", i + 1);
        for(j = 0; j < n; j++) {
            scanf("%d", &G[i][j]);
        }
    }
    while(ne < n){
        for(i=0, min=99; i<n; i++){
            for(j=0; j<n; j++){
                if(G[i][j] < min){
                    min = G[i][j];
                    a = u = i;
                    b = v = j;
                }
            }
        }
        u = Findpar(u);
        v = Findpar(v);
        
        if(Union(u,v)){
            minw += min;
            printf("%d edge :- %d - %d -> %d\n", ne, a, b, G[a][b]);
            ne++;
        }
        G[a][b] = G[b][a] = 99;
    }
    printf("MST weight = %d", minw);
}

int Findpar(int i){
    while(i != par[i])
    i = par[i];
    return i;
}

int Union(int i, int j){
    if(i != j){
        par[j] = i;
        return 1;
    }
    return 0;
}
