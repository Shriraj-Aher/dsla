// Array is given of size 'n'. We need to divide this array in 'm' numbers.
// After division each subarray is treated as a queue. If a one queue
// becomes full we should utilize the space of its next adjecent queue. Write a program to simulate above situation.

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int start;
    int end;
    int size;
} Queue;

int array[MAX];     // Shared array
Queue queues[MAX];  // Queue metadata

int n, m, partSize;

void initializeQueues(int totalSize, int numQueues) {
    n = totalSize;
    m = numQueues;
    partSize = n / m;

    for (int i = 0; i < m; i++) {
        queues[i].start = i * partSize;
        queues[i].end = queues[i].start - 1;
        queues[i].size = 0;
    }
}

int insert(int queueNum, int value) {
    int i = queueNum;

    while (i < m) {
        if (queues[i].end + 1 < ((i + 1) * partSize)) {
            queues[i].end++;
            array[queues[i].end] = value;
            queues[i].size++;
            printf("Inserted %d into Queue %d\n", value, i);
            return 1;
        }
        i++;
    }

    printf("Overflow! Could not insert %d\n", value);
    return 0;
}

void display() {
    printf("\n--- Queue Contents ---\n");
    for (int i = 0; i < m; i++) {
        printf("Queue %d: ", i);
        for (int j = queues[i].start; j <= queues[i].end; j++) {
            printf("%d ", array[j]);
        }
        printf("\n");
    }
}

int main() {
    int totalSize, numQueues;
    printf("Enter total array size (n): ");
    scanf("%d", &totalSize);
    printf("Enter number of queues (m): ");
    scanf("%d", &numQueues);

    if (totalSize > MAX || totalSize % numQueues != 0) {
        printf("Invalid input. Ensure n <= %d and n %% m == 0\n", MAX);
        return 1;
    }

    initializeQueues(totalSize, numQueues);

    int choice, qnum, val;
    while (1) {
        printf("\n1. Insert\n2. Display\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter queue number (0 to %d): ", numQueues - 1);
                scanf("%d", &qnum);
                if (qnum < 0 || qnum >= numQueues) {
                    printf("Invalid queue number!\n");
                    break;
                }
                printf("Enter value: ");
                scanf("%d", &val);
                insert(qnum, val);
                break;
            case 2:
                display();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
