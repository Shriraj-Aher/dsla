#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int size;
    int id;     // Original partition ID (block number)
} Partition;

void printMemoryState(Partition partitions[], int n) {
    printf("\nCurrent Memory State:\n");
    for (int i = 0; i < n; i++) {
        printf("Partition %d [%d KB]\n", partitions[i].id, partitions[i].size);
    }
    printf("\n");
}

void resetPartitions(Partition dest[], Partition src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void firstFit(int processes[], int m, Partition original[], int n) {
    printf("\nFIRST FIT\n");
    Partition partitions[MAX];
    resetPartitions(partitions, original, n);

    for (int i = 0; i < m; i++) {
        int allocated = 0;
        for (int j = 0; j < n; j++) {
            if (partitions[j].size >= processes[i]) {
                printf("Process %d (%d KB) allocated to Partition %d (Block %d)\n",
                       i, processes[i], partitions[j].id, j);
                partitions[j].size -= processes[i];
                allocated = 1;
                break;
            }
        }
        if (!allocated) {
            printf("Process %d (%d KB) cannot be allocated\n", i, processes[i]);
        }
    }
    printMemoryState(partitions, n);
}

void nextFit(int processes[], int m, Partition original[], int n) {
    printf("\nNEXT FIT\n");
    Partition partitions[MAX];
    resetPartitions(partitions, original, n);

    int lastPos = 0;
    for (int i = 0; i < m; i++) {
        int allocated = 0, j = lastPos, count = 0;
        while (count < n) {
            if (partitions[j].size >= processes[i]) {
                printf("Process %d (%d KB) allocated to Partition %d (Block %d)\n",
                       i, processes[i], partitions[j].id, j);
                partitions[j].size -= processes[i];
                lastPos = j;
                allocated = 1;
                break;
            }
            j = (j + 1) % n;
            count++;
        }
        if (!allocated) {
            printf("Process %d (%d KB) cannot be allocated\n", i, processes[i]);
        }
    }
    printMemoryState(partitions, n);
}

void bestFit(int processes[], int m, Partition original[], int n) {
    printf("\nBEST FIT\n");
    Partition partitions[MAX];
    resetPartitions(partitions, original, n);

    for (int i = 0; i < m; i++) {
        int bestIndex = -1;
        for (int j = 0; j < n; j++) {
            if (partitions[j].size >= processes[i]) {
                if (bestIndex == -1 || partitions[j].size < partitions[bestIndex].size)
                    bestIndex = j;
            }
        }

        if (bestIndex != -1) {
            printf("Process %d (%d KB) allocated to Partition %d (Block %d)\n",
                   i, processes[i], partitions[bestIndex].id, bestIndex);
            partitions[bestIndex].size -= processes[i];
        } else {
            printf("Process %d (%d KB) cannot be allocated\n", i, processes[i]);
        }
    }
    printMemoryState(partitions, n);
}

void worstFit(int processes[], int m, Partition original[], int n) {
    printf("\nWORST FIT\n");
    Partition partitions[MAX];
    resetPartitions(partitions, original, n);

    for (int i = 0; i < m; i++) {
        int worstIndex = -1;
        for (int j = 0; j < n; j++) {
            if (partitions[j].size >= processes[i]) {
                if (worstIndex == -1 || partitions[j].size > partitions[worstIndex].size)
                    worstIndex = j;
            }
        }

        if (worstIndex != -1) {
            printf("Process %d (%d KB) allocated to Partition %d (Block %d)\n",
                   i, processes[i], partitions[worstIndex].id, worstIndex);
            partitions[worstIndex].size -= processes[i];
        } else {
            printf("Process %d (%d KB) cannot be allocated\n", i, processes[i]);
        }
    }
    printMemoryState(partitions, n);
}

int main() {
    int n, m, processes[MAX];
    Partition partitions[MAX], original[MAX];

    printf("Enter number of memory partitions: ");
    scanf("%d", &n);
    printf("Enter sizes of %d partitions (in KB):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &original[i].size);
        original[i].id = i; // Assign block number
    }

    printf("Enter number of processes: ");
    scanf("%d", &m);
    printf("Enter sizes of %d processes (in KB):\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &processes[i]);
    }

    firstFit(processes, m, original, n);
    nextFit(processes, m, original, n);
    bestFit(processes, m, original, n);
    worstFit(processes, m, original, n);

    return 0;
}
