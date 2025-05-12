// Given a list, split it into two sublists — one for the front half, and one
// for the back half. If the number of elements is odd, the extra element
// should go in the front list. So FrontBackSplit() on the list {2, 3, 5, 7, 11}
// should yield the two lists {2, 3, 5} and {7, 11}. Getting this right for all
// the cases is harder than it looks. You should check your solution against
// a few cases (length = 2, length = 3, length=4) to make sure that the list
// gets split correctly near the short­list boundary conditions. If it works
// right for length=4, it probably works right for length=1000. You will
// probably need special case code to deal with the (length <2) cases.


#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;

void insert(node** head, int data){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;

    if(*head == NULL){
        *head = newnode;
        return;
    }

    node* temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = newnode;
}


int main(){
    int n;
    printf("enter the number of elements: ");
    scanf("%d", &n);

    int data;
    node* head = NULL;
    for(int i=0; i<n; i++){
        printf("enter the element %d: ", i+1);
        scanf("%d", &data);
        insert(&head, data);
    }

    node* temp = head;
    
    if(n % 2 == 0){
        printf("\nfirst list : \n");
        node* temp = head;
        int i = 0;
        while (temp != NULL && i < n/2)
        {
            printf("%d ", temp->data);
            temp = temp->next;
            i++;
        }

        printf("\nlist second: \n");
        while(temp != NULL){
            printf("%d ", temp->data);
            temp = temp->next;
        }

    }

    else{
        printf("first list : \n");
        node* temp = head;
        int i = 0;
        while (temp != NULL && i <= (n/2))
        {
            printf("%d ", temp->data);
            temp = temp->next;
            i++;
        }

        printf("\nlist second: \n");
        while(temp != NULL){
            printf("%d ", temp->data);
            temp = temp->next;
        }
        
    }
    return 0;

}




//WAP to perform addition o f two polynomials using singly linked list



