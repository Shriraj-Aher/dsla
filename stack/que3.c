// WAP to implement multiple stack i.e. More than two stacks using array
// and perform following operations on it. A. PUSH, B. POP, C. StackFull
// D. StackeEmpty E. Display Stack

#include <stdio.h>

#define MAX 100
#define MAX_STACKS 10  // Set a maximum limit for number of stacks

int arr[MAX];
int top[MAX_STACKS];
int numStacks, sizePerStack;

void initStacks(int n, int totalSize) {
    numStacks = n;
    sizePerStack = totalSize / n;

    for (int i = 0; i < numStacks; i++) {
        top[i] = i * sizePerStack - 1;  // Initialize each top
    }
}

int isFull(int sn) {
    return top[sn] == ((sn + 1) * sizePerStack - 1);
}

int isEmpty(int sn) {
    return top[sn] == (sn * sizePerStack - 1);
}

void push(int sn, int value) {
    if (isFull(sn)) {
        printf("Stack %d is FULL!\n", sn);
        return;
    }
    top[sn]++;
    arr[top[sn]] = value;
    printf("Pushed %d to Stack %d\n", value, sn);
}

void pop(int sn) {
    if (isEmpty(sn)) {
        printf("Stack %d is EMPTY!\n", sn);
        return;
    }
    int popped = arr[top[sn]];
    top[sn]--;
    printf("Popped %d from Stack %d\n", popped, sn);
}

void display(int sn) {
    if (isEmpty(sn)) {
        printf("Stack %d is EMPTY!\n", sn);
        return;
    }
    printf("Stack %d contents: ", sn);
    for (int i = sn * sizePerStack; i <= top[sn]; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int totalSize, stacks;

    printf("Enter total size of array: ");
    scanf("%d", &totalSize);

    printf("Enter number of stacks: ");
    scanf("%d", &stacks);

    if (totalSize > MAX || stacks > MAX_STACKS || totalSize < stacks) {
        printf("Invalid configuration!\n");
        return 0;
    }

    initStacks(stacks, totalSize);

    int choice, sn, val;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. PUSH\n2. POP\n3. Check StackFull\n4. Check StackEmpty\n5. Display Stack\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter stack number (0 to %d): ", stacks - 1);
                scanf("%d", &sn);
                printf("Enter value to push: ");
                scanf("%d", &val);
                push(sn, val);
                break;

            case 2:
                printf("Enter stack number (0 to %d): ", stacks - 1);
                scanf("%d", &sn);
                pop(sn);
                break;

            case 3:
                printf("Enter stack number (0 to %d): ", stacks - 1);
                scanf("%d", &sn);
                if (isFull(sn))
                    printf("Stack %d is FULL.\n", sn);
                else
                    printf("Stack %d is NOT FULL.\n", sn);
                break;

            case 4:
                printf("Enter stack number (0 to %d): ", stacks - 1);
                scanf("%d", &sn);
                if (isEmpty(sn))
                    printf("Stack %d is EMPTY.\n", sn);
                else
                    printf("Stack %d is NOT EMPTY.\n", sn);
                break;

            case 5:
                printf("Enter stack number (0 to %d): ", stacks - 1);
                scanf("%d", &sn);
                display(sn);
                break;

            case 6:
                printf("Exiting.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
