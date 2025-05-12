// bubble sort using doubly linked list

#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Insert node at the end
void append(Node** headRef, int data) {
    Node* newNode = createNode(data);
    Node* temp = *headRef;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

// Function to print list
void printList(Node* head) {
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Bubble sort for doubly linked list (by swapping data)
void bubbleSort(Node* head) {
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                // Swap data
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;  // Optimization: Last node is now in correct place
    } while (swapped);
}

// Example usage
int main() {
    Node* head = NULL;

    append(&head, 40);
    append(&head, 10);
    append(&head, 30);
    append(&head, 20);

    printf("Original list:\n");
    printList(head);

    bubbleSort(head);

    printf("Sorted list:\n");
    printList(head);

    return 0;
}
