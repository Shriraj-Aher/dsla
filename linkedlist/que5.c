// Implement ADD and DELETE operations of QUEUE on Doubly linked
// lists

#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* front = NULL;
Node* rear = NULL;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Add to queue (enqueue)
void enqueue(int data) {
    Node* newNode = createNode(data);
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        newNode->prev = rear;
        rear = newNode;
    }
    printf("Enqueued: %d\n", data);
}

// Delete from queue (dequeue)
void dequeue() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    Node* temp = front;
    printf("Dequeued: %d\n", temp->data);
    front = front->next;
    if (front != NULL)
        front->prev = NULL;
    else
        rear = NULL;  // Queue became empty
    free(temp);
}

// Print queue
void display() {
    Node* temp = front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Example usage
int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();

    dequeue();
    display();

    dequeue();
    display();

    return 0;
}
