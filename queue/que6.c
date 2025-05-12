// Write a Program to implement double ended queue where user can add
// and remove the elements from both front and rear of the queue

#include<stdio.h>
#define max 10
int queue[max];
int front = -1;
int rear = -1;

void enque(int x){
    if(rear == max-1){
        printf("queue is full");
        return;
    }
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
    if(front == -1 || front > rear){
        printf("queue is empty");
        return -1; 
    }
    else{
        int x = queue[front];
        front++;
        return x;
    }
}

void enqueF(int x){
    if(front == 0){
        printf("queue is full");
        return;
    }
    else if(front == -1){
        front = rear = 0;
        queue[front] = x;
    }
    else{
        front--;
        queue[front] = x;
    }
}

int dequeR(){
    if(rear == -1 || front > rear){
        
    }
}
int main(){

}