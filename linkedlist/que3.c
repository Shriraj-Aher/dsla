// Write a RemoveDuplicates() function which takes a list sorted in
// increasing order and deletes any duplicate nodes from the list. Ideally,
// the list should only be traversed once.


#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;

node* createnode(int data){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void insertnode(node **head, int data){
    node* newnode = createnode(data);

    if(*head == NULL){
        *head = newnode;
    }
    else{
        node* current = *head;
        while(current->next != NULL){
            current = current->next;
        }

        current->next = newnode;
    }
}

void removeDuplicates(node* head){

    node* Current = head;
    while(Current != NULL && Current->next != NULL){
        if(Current->data == Current->next->data){
            node* temp = Current->next;
            Current->next = Current->next->next;
            free(temp);
        }
        else{
            Current = Current->next;
        }

    }
}

void print(node* head){
    while(head != NULL){
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(){
    node* head = NULL;

    insertnode(&head, 10);
    insertnode(&head, 20);
    insertnode(&head, 20);
    insertnode(&head, 30);
    insertnode(&head, 40);
    insertnode(&head, 40);

    printf("original list: \n");
    print(head);

    removeDuplicates(head);

    printf("list after removing duplicates: \n");
    print(head);
    return 0;


}