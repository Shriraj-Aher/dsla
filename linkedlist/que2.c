// Write a SortedInsert() function which given a list that is sorted in
// increasing order, and a single node, inserts the node into the correct
// sorted position in the list. While Push() allocates a new node to add to
// the list, SortedInsert() takes an existing node, and just rearranges
// pointers to insert it into the list

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node;


node* createnode(int data){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void sortedinsert(node **head, node *newnode){
    node* Current;

    if(*head == NULL || (*head)->data > newnode->data){
        newnode->next = *head;
        *head = newnode;
    }
    else{
        Current = *head;
        while(Current->next != NULL && Current->next->data < newnode->data){
            Current = Current->next;
        }

        newnode->next = Current->next;
        Current->next = newnode;
    }
}

void PrintList(struct node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main(){

    node* head = NULL;

    sortedinsert(&head, createnode(30));
    sortedinsert(&head, createnode(10));
    sortedinsert(&head, createnode(20));

    PrintList(head);
    return 0;
}