// Array is given of size 'n'. We need to divide this array in 'm' numbers,
// where 2 < m < n. After division each subarray is treated as a stack. If a
// one stack becomes full we should utilize the space of its next adjacent
// stack. Write a program to simulate above situation.
#include <stdio.h>
#define N 20
#define M 4
#define SIZE (N / M)

typedef struct {
    int top;
    int start;
    int end;
} stack;

int arr[N];
stack st[M];

void initStacks() {
    for (int i = 0; i < M; i++) {
        st[i].start = i * SIZE;
        st[i].end = (i + 1) * SIZE - 1;
        st[i].top = st[i].start - 1;
    }
}

void push(int stackNum, int value) {
    if (stackNum < 0 || stackNum >= M) {
        printf("Invalid stack number!\n");
        return;
    }

    stack *s = &st[stackNum];

    if (s->top == s->end) {
        // Try to shift next stack
        if (stackNum < M - 1 && st[stackNum + 1].top > st[stackNum + 1].start - 1) {
            // Shift next stacks one step right
            for (int j = M - 1; j > stackNum; j--) {
                if (st[j].end + 1 >= N) {
                    printf("Cannot expand stack %d, no space available\n", stackNum);
                    return;
                }
                for (int k = st[j].top; k >= st[j].start; k--) {
                    arr[k + 1] = arr[k];
                }
                st[j].start++;
                st[j].end++;
                st[j].top++;
            }
            s->end++;
        } else {
            printf("Stack %d is full and cannot expand\n", stackNum);
            return;
        }
    }

    arr[++(s->top)] = value;
    printf("Pushed %d to stack %d\n", value, stackNum);
}

int pop(int stackNum) {
    if (stackNum < 0 || stackNum >= M) {
        printf("Invalid stack number!\n");
        return -1;
    }

    stack *s = &st[stackNum];
    if (s->top < s->start) {
        printf("Stack %d is empty!\n", stackNum);
        return -1;
    }

    int val = arr[s->top--];
    printf("Popped %d from stack %d\n", val, stackNum);
    return val;
}

void displayStacks() {
    for (int i = 0; i < M; i++) {
        printf("Stack %d: ", i);
        for (int j = st[i].start; j <= st[i].top; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
}

int main() {
    initStacks();

    push(0, 10);
    push(0, 20);
    push(0, 30);
    push(0, 40);
    push(0, 50);  // Expands into stack 1
    push(0, 60);  // Expands again if possible

    push(1, 100);
    push(1, 110);

    pop(0);
    push(1, 120);

    displayStacks();

    return 0;
}
