// WAP to implement multiple stack i.e. two stacks using array and
// perform following operations on it. A. PUSH, B. POP, C. StackFull and
// D. StackeEmpty E. Display Stack.


#include <stdio.h>
#include <stdbool.h>

#define MAX 10  // Define the maximum size of the array

int arr[MAX];   // Array to represent both stacks
int top1 = -1;  // Top for stack 1
int top2 = MAX; // Top for stack 2 (starting from the last index)

// Function to check if stack 1 is full
bool isStack1Full() {
    return top1 == top2 - 1;
}

// Function to check if stack 2 is full
bool isStack2Full() {
    return top2 == top1 + 1;
}

// Function to check if stack 1 is empty
bool isStack1Empty() {
    return top1 == -1;
}

// Function to check if stack 2 is empty
bool isStack2Empty() {
    return top2 == MAX;
}

// Function to push an element onto stack 1
void push1(int value) {
    if (isStack1Full()) {
        printf("Stack 1 is full!\n");
    } else {
        arr[++top1] = value;
        printf("Pushed %d onto stack 1.\n", value);
    }
}

// Function to push an element onto stack 2
void push2(int value) {
    if (isStack2Full()) {
        printf("Stack 2 is full!\n");
    } else {
        arr[--top2] = value;
        printf("Pushed %d onto stack 2.\n", value);
    }
}

// Function to pop an element from stack 1
int pop1() {
    if (isStack1Empty()) {
        printf("Stack 1 is empty!\n");
        return -1;
    } else {
        return arr[top1--];
    }
}

// Function to pop an element from stack 2
int pop2() {
    if (isStack2Empty()) {
        printf("Stack 2 is empty!\n");
        return -1;
    } else {
        return arr[top2++];
    }
}

// Function to display stack 1
void displayStack1() {
    if (isStack1Empty()) {
        printf("Stack 1 is empty!\n");
    } else {
        printf("Stack 1: ");
        for (int i = 0; i <= top1; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

// Function to display stack 2
void displayStack2() {
    if (isStack2Empty()) {
        printf("Stack 2 is empty!\n");
    } else {
        printf("Stack 2: ");
        for (int i = MAX - 1; i >= top2; i--) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

int main() {
    // Sample operations
    push1(10);
    push1(20);
    push2(30);
    push2(40);

    displayStack1();
    displayStack2();

    pop1();
    pop2();

    displayStack1();
    displayStack2();

    return 0;
}
