// An operating system assigns job to print queues based on the number of
// pages to be printed (1 to 50 pages). You may assume that the system
// printers are able to print 10 page per minute. Smaller print jobs are
// printed before larger print jobs and print jobs are processed from a
// single print queue implemented as a priority queue). The system
// administrators would like to compare the time required to process a set
// of print jobs using 1, 2, or 3 system printers. Write a program which
// simulates processing 100 print jobs of varying lengths using either 1, 2,
// or 3 printers. Assume that a print request is made every minute and that
// the number of pages to print varies from 1 to 50 pages. To be fair, you
// will need to process the same set of print jobs each time you add a
// printer.The output from your program should indicate the order in which
// the jobs were received, the order in which they were printed, and the
// time required to process the set of print jobs. If more than one printer is
// being used, indicate which printer each job was printed on

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_JOBS 100
#define MAX_PAGES 50
#define PRINT_SPEED 10 // pages per minute
#define MAX_PRINTERS 3

typedef struct {
    int id;
    int pages;
    int arrivalTime;
    int startTime;
    int finishTime;
    int printerID;
} Job;

// Priority Queue (min-heap based on pages)
void swap(Job *a, Job *b) {
    Job temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Job heap[], int n, int i) {
    int smallest = i;
    int l = 2*i + 1, r = 2*i + 2;
    if (l < n && heap[l].pages < heap[smallest].pages)
        smallest = l;
    if (r < n && heap[r].pages < heap[smallest].pages)
        smallest = r;
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, n, smallest);
    }
}

void buildMinHeap(Job heap[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(heap, n, i);
}

Job extractMin(Job heap[], int *n) {
    Job min = heap[0];
    heap[0] = heap[--(*n)];
    heapify(heap, *n, 0);
    return min;
}

// Simulate print job processing
void simulate(Job jobs[], int numPrinters) {
    int time = 0, jobsPrinted = 0;
    int heapSize = NUM_JOBS;
    Job queue[NUM_JOBS];
    for (int i = 0; i < NUM_JOBS; i++) queue[i] = jobs[i];
    buildMinHeap(queue, heapSize);

    int printerAvailableTime[MAX_PRINTERS] = {0};
    Job printedJobs[NUM_JOBS];

    printf("\n--- Simulation with %d printer(s) ---\n", numPrinters);

    while (jobsPrinted < NUM_JOBS) {
        for (int p = 0; p < numPrinters && heapSize > 0; p++) {
            if (printerAvailableTime[p] <= time) {
                Job job = extractMin(queue, &heapSize);
                job.startTime = time;
                int printTime = (job.pages + PRINT_SPEED - 1) / PRINT_SPEED;
                job.finishTime = time + printTime;
                job.printerID = p + 1;
                printerAvailableTime[p] = job.finishTime;
                printedJobs[jobsPrinted++] = job;
            }
        }
        time++;
    }

    // Output
    printf("ID | Pages | Arrival | Start | Finish | Printer\n");
    for (int i = 0; i < NUM_JOBS; i++) {
        printf("%3d | %5d | %7d | %5d | %6d |   %d\n",
            printedJobs[i].id, printedJobs[i].pages, printedJobs[i].arrivalTime,
            printedJobs[i].startTime, printedJobs[i].finishTime,
            printedJobs[i].printerID);
    }

    int totalTime = 0;
    for (int i = 0; i < MAX_PRINTERS; i++)
        if (i < numPrinters && printerAvailableTime[i] > totalTime)
            totalTime = printerAvailableTime[i];

    printf("Total time to print all jobs: %d minutes\n", totalTime);
}

int main() {
    srand(42); // consistent results
    Job jobs[NUM_JOBS];

    // Generate 100 jobs: 1 job per minute, pages from 1–50
    for (int i = 0; i < NUM_JOBS; i++) {
        jobs[i].id = i + 1;
        jobs[i].pages = (rand() % MAX_PAGES) + 1;
        jobs[i].arrivalTime = i;
    }

    printf("--- Job Generation Order ---\n");
    printf("ID | Pages | Arrival\n");
    for (int i = 0; i < NUM_JOBS; i++)
        printf("%3d | %5d | %7d\n", jobs[i].id, jobs[i].pages, jobs[i].arrivalTime);

    // Simulate with 1, 2, and 3 printers
    for (int p = 1; p <= 3; p++)
        simulate(jobs, p);

    return 0;
}
